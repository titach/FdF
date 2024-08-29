/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:36:08 by tchaloei          #+#    #+#             */
/*   Updated: 2024/08/28 16:42:57 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_file(int ac, char *filename)
{
	char	file[5];
	int		i;
	int		j;

	if (ac != 2)
		msg_file("Usage: ./fdf A file in format *.fdf\n");
	i = 0;
	while (filename[i + 1])
		i++;
	file[4] = '\0';
	j = 3;
	while (j >= 0)
	{
		file[j] = filename[i];
		j--;
		i--;
	}
	if (ft_strncmp(file, ".fdf", ft_strlen(file)) != 0)
		msg_file("Usage: ./fdf A file in format *.fdf\n");
	if (ft_strncmp(filename, "fdf", ft_strlen(file)) == 0)
		msg_file("Usage: ./fdf A file in format *.fdf\n");
}

void	msg_file(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}
