/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:38:17 by tchaloei          #+#    #+#             */
/*   Updated: 2024/08/28 16:23:22 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_col(char *text, t_fdf *fdf)
{
	char	**text2;
	int		i;

	text2 = ft_split(text, ' ');
	i = 0;
	while (text2[i])
	{
		if (ft_atoi(text2[i]) == 0 && text2[i][0] != '0')
		{
			free_split(text2);
			free_split(fdf->map);
			msg_file("Wrong data.\n");
		}
		i++;
	}
	free_split(text2);
	return (i);
}

void	get_row_col(t_fdf *fdf)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	fdf->col = 0;
	while (fdf->map[i])
	{
		count = 0;
		if (i == 0)
			fdf->col = count_col(fdf->map[i], fdf);
		count = count_col(fdf->map[i], fdf);
		if (count != fdf->col)
			j++;
		i++;
	}
	fdf->row = i;
	if (j > 0)
	{
		free_split(fdf->map);
		msg_file("Found wrong line length. Exiting.\n");
	}
}

void	read_map(t_fdf *fdf, char *file)
{
	char	*buffer;

	fdf->fd = open(file, O_RDONLY);
	if (fdf->fd < 0)
		msg_file("Permission denied. / No file.\n");
	buffer = get_next_line(fdf->fd);
	fdf->read = get_next_line(fdf->fd);
	fdf->row = 1;
	while (fdf->read)
	{
		fdf->temp = buffer;
		buffer = ft_strjoin(buffer, fdf->read);
		free(fdf->temp);
		free(fdf->read);
		fdf->read = get_next_line(fdf->fd);
		fdf->row++;
	}
	close(fdf->fd);
	if (!buffer)
		msg_file("No data found.\n");
	fdf->map = ft_split(buffer, '\n');
	free(buffer);
}
