/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:36:24 by tchaloei          #+#    #+#             */
/*   Updated: 2024/08/28 14:40:43 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_struct(t_point **point)
{
	int	i;

	i = 0;
	while (point[i])
	{
		free(point[i]);
		i++;
	}
	free(point);
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		turn_off_win(param);
}

void	turn_off_win(t_fdf *mlx)
{
	mlx_terminate(mlx->mlx);
	free_split(mlx->map);
	free_struct(mlx->point);
	exit(EXIT_SUCCESS);
}
