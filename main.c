/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:37:51 by tchaloei          #+#    #+#             */
/*   Updated: 2024/08/28 16:39:09 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	adjust_z(t_fdf *fdf, int i, int j, char **result)
{
	if (fdf->row < 50 && fdf->col < 50)
	{
		fdf->point[i][j].z = (float)ft_atoi(result[j]) * 10;
		if ((float)ft_atoi(result[j]) * 10 >= 300)
			fdf->point[i][j].z = 300;
	}
	else
	{
		fdf->point[i][j].z = (float)ft_atoi(result[j]);
		if ((float)ft_atoi(result[j]) >= 300)
			fdf->point[i][j].z = 300;
	}
	if (fdf->point[i][j].z <= -200)
		fdf->point[i][j].z = -200;
}

void	find_coordinates(t_fdf *fdf)
{
	char	**result;
	int		i;
	int		j;

	get_memory(fdf);
	i = 0;
	while (i < fdf->row)
	{
		result = ft_split(fdf->map[i], ' ');
		j = 0;
		while (j < fdf->col)
		{
			fdf->point[i][j].x = 0;
			fdf->point[i][j].y = 0;
			fdf->point[i][j].x = (float)j * fdf->ratio * 0.7;
			fdf->point[i][j].y = (float)i * fdf->ratio * 0.7;
			adjust_z(fdf, i, j, result);
			j++;
		}
		i++;
		free_split(result);
	}
}

void	isometric_point(t_fdf *dot)
{
	int		i;
	int		j;
	float	x;
	float	y;

	i = 0;
	while (i < dot->row)
	{
		j = 0;
		while (j < dot->col)
		{
			x = dot->point[i][j].x;
			y = dot->point[i][j].y;
			dot->point[i][j].x = (x - y) * cos(DEGREE);
			dot->point[i][j].y = ((x + y) * sin(DEGREE) - dot->point[i][j].z);
			j++;
		}
		i++;
	}
}

void	make_wireframe(t_fdf *fdf, char *file)
{
	read_map(fdf, file);
	get_row_col(fdf);
	if (fdf->row > 500)
	{
		free_split(fdf->map);
		msg_file("Map size is bigger than 500 x 500.\n");
	}
	get_row_col(fdf);
	if (fdf->col == 0)
	{
		free_split(fdf->map);
		msg_file("No data found.\n");
	}
	if (fdf->col > 500)
	{
		free_split(fdf->map);
		msg_file("Map size is bigger than 500 x 500.\n");
	}
	fdf->ratio = (WIDTH / (cos(DEGREE) * (fdf->row + fdf->col)));
	find_coordinates(fdf);
	find_color(fdf);
	isometric_point(fdf);
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	check_file(ac, av[1]);
	make_wireframe(&fdf, av[1]);
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "FdF", false);
	if (!fdf.mlx)
		exit(EXIT_FAILURE);
	fdf.img = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	build_grid(&fdf);
	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
	mlx_key_hook(fdf.mlx, &keyhook, &fdf);
	mlx_loop(fdf.mlx);
	turn_off_win(&fdf);
}
