/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:38:08 by tchaloei          #+#    #+#             */
/*   Updated: 2024/08/28 14:39:07 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

long	set_color(char **set)
{
	long	color;

	color = 0;
	if (set[1])
		color = ft_atoh(set[1]);
	else
	{
		if (ft_atoi(set[0]) != 0)
			color = 0x81FFE7;
		else
			color = 0xE95C00;
	}
	return (color);
}

void	find_color(t_fdf *fdf)
{
	char	**find;
	char	**text;
	int		i;
	int		j;

	i = 0;
	find = NULL;
	text = NULL;
	while (fdf->map[i])
	{
		find = ft_split(fdf->map[i], ' ');
		j = 0;
		while (find[j])
		{
			text = ft_split(find[j], ',');
			fdf->point[i][j].color = set_color(text);
			free_split(text);
			j++;
		}
		free_split(find);
		i++;
	}
}
