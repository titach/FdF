/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:37:17 by tchaloei          #+#    #+#             */
/*   Updated: 2024/08/28 14:37:38 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*clean_the_stash(char *str)
{
	char	*stash;
	size_t	i;
	size_t	j;

	if (!*str)
		return (free(str), NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	stash = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!stash)
		return (NULL);
	j = i;
	while (str[i])
	{
		stash[i - j] = str[i];
		i++;
	}
	stash[i - j] = '\0';
	if (!*stash)
		return (free(str), free(stash), NULL);
	free(str);
	return (stash);
}

static char	*get_the_line(char *str)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!*str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*free_stash(char *line, char *stash)
{
	free(line);
	free(stash);
	return (NULL);
}

static char	*read_line(int fd, char *line, char *stash)
{
	char	*temp;
	int		read_b;

	read_b = 1;
	if (!stash)
		stash = ft_strdup("");
	temp = NULL;
	while (read_b != 0)
	{
		read_b = read(fd, line, BUFFER_SIZE);
		if (read_b == -1)
		{
			stash = free_stash(line, stash);
			return (NULL);
		}
		line[read_b] = '\0';
		temp = stash;
		stash = ft_strjoin(stash, line);
		free(temp);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	stash = read_line(fd, line, stash);
	free(line);
	line = get_the_line(stash);
	stash = clean_the_stash(stash);
	return (line);
}
