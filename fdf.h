/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:36:32 by tchaloei          #+#    #+#             */
/*   Updated: 2024/08/28 14:39:53 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <MLX42/MLX42.h>
# include <unistd.h>
# include <math.h>
# include "libft.h"

# define BUFFER_SIZE 10000
# define WIDTH 1280
# define HEIGHT 950
# define DEGREE 0.523599
# define WARNING_COLOR 11468800
# define ALPHA 255

typedef struct s_point
{
	float			x;
	float			y;
	float			z;
	long			color;
}		t_point;

typedef struct s_fdf
{
	int			col;
	int			row;
	int			fd;
	float		dot_x;
	float		dot_y;
	float		xin;
	float		yin;
	float		dx;
	float		dy;
	float		steps;
	float		ratio;
	char		*read;
	char		*temp;
	char		**map;
	t_point		**point;
	mlx_t		*mlx;
	mlx_image_t	*img;
}		t_fdf;

/*-------check_file_msg-------*/
void	check_file(int ac, char *filename);
void	msg_file(char *msg);
/*-------get_next_line-------*/
char	*get_next_line(int fd);
/*-------utils-------*/
void	get_memory(t_fdf *fdf);
long	ft_atoh(char *str);
/*-------build_grid-------*/
void	paint_grid(t_fdf *grid, int x, int y, long color);
void	formula_dda(t_point *start, t_point *stop, t_fdf *grid);
void	dda_algorithm(t_point start, t_point stop, t_fdf *grid);
void	build_grid(t_fdf *grid);
/*-------start_grid-------*/
int		count_col(char *text, t_fdf *fdf);
void	get_row_col(t_fdf *fdf);
void	read_map(t_fdf *fdf, char *file);
/*-------set_up_color-------*/
long	set_color(char **set);
void	find_color(t_fdf *nbr);
/*-------ft_free-------*/
void	free_split(char **str);
void	free_struct(t_point **point);
void	keyhook(mlx_key_data_t keydata, void *param);
void	turn_off_win(t_fdf *mlx);

#endif