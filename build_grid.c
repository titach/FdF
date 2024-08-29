/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:35:27 by tchaloei          #+#    #+#             */
/*   Updated: 2024/08/28 14:40:30 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	paint_grid(t_fdf *grid, int x, int y, long color)
{
	int	range_wide;
	int	range_high;

	range_wide = grid->img->width;
	range_high = grid->img->height;
	if ((x >= 0 && x < range_wide) && (y >= 0 && y < range_high))
		mlx_put_pixel(grid->img, x, y, (color << 8) + ALPHA);
}

void	formula_dda(t_point *start, t_point *stop, t_fdf *grid)
{
	grid->dx = stop->x - start->x;
	grid->dy = stop->y - start->y;
	if (fabsf(grid->dx) > fabsf(grid->dy))
		grid->steps = fabsf(grid->dx);
	else
		grid->steps = fabsf(grid->dy);
	grid->xin = grid->dx / grid->steps;
	grid->yin = grid->dy / grid->steps;
	grid->dot_x = start->x;
	grid->dot_y = start->y;
}

void	dda_algorithm(t_point start, t_point stop, t_fdf *grid)
{
	int	i;
	int	offset;

	formula_dda(&start, &stop, grid);
	i = 0;
	offset = 200;
	while (i < grid->steps)
	{
		grid->dot_x = grid->dot_x + grid->xin;
		grid->dot_y = grid->dot_y + grid->yin;
		paint_grid(grid, (grid->dot_x + (float)(WIDTH / 2)) - \
		((float)(grid->col / 2) * (grid->ratio * 0.5)) + offset, \
		(grid->dot_y + (float)(HEIGHT / 2)) - ((float)(grid->row / 2) * \
		(grid->ratio * 0.5)), start.color);
		i++;
	}
}

void	build_grid(t_fdf *grid)
{
	int	i;
	int	j;

	i = 0;
	while (i < grid->row)
	{
		j = 0;
		while (j < grid->col)
		{
			if (i < grid->row - 1)
				dda_algorithm(grid->point[i][j], grid->point[i + 1][j], grid);
			if (j < grid->col - 1)
				dda_algorithm(grid->point[i][j], grid->point[i][j + 1], grid);
			j++;
		}
		i++;
	}
}
