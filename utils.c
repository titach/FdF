/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:59:56 by tchaloei          #+#    #+#             */
/*   Updated: 2024/08/28 14:59:58 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

long	ft_atoh(char *str)
{
	int		i;
	long	color;

	i = 0;
	color = 0;
	if (str[i] == '-' || str[i] == '+')
		return (WARNING_COLOR);
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = i + 2;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			color = (color * 16) + (str[i] - '0');
		else if (str[i] >= 'a' && str[i] <= 'f')
			color = (color * 16) + (str[i] - 'a' + 10);
		else if (str[i] >= 'A' && str[i] <= 'F')
			color = (color * 16) + (str[i] - 'A' + 10);
		i++;
	}
	return (color);
}

void	get_memory(t_fdf *fdf)
{
	int	i;

	fdf->point = malloc(sizeof(t_point *) * (fdf->row + 1));
	if (!fdf->point)
	{
		free_split(fdf->map);
		msg_file("memmory is not allocted.\n");
	}
	i = 0;
	while (i < fdf->row)
	{
		fdf->point[i] = malloc(sizeof(t_point) * (fdf->col));
		if (!fdf->point[i])
		{
			free_struct(fdf->point);
			free_split(fdf->map);
			msg_file("memmory is not allocted.\n");
		}
		i++;
	}
	fdf->point[i] = NULL;
}
