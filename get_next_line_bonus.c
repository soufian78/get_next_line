/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skabny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:27:32 by skabny            #+#    #+#             */
/*   Updated: 2025/11/12 20:57:19 by skabny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_join(char	*stash, int fd)
{
	int	rd;

	char *(buff), *(tmp);
	if (!stash)
		stash = ft_strdup("");
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	rd = 1;
	while (rd > 0 && !ft_strchr(stash, '\n'))
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
			return (free(stash), free(buff), NULL);
		buff[rd] = '\0';
		tmp = ft_strjoin(stash, buff);
		free(stash);
		stash = tmp;
		if (!stash)
			return (free(buff), NULL);
	}
	if (rd == 0 && stash[0] == '\0')
		return (free(stash), free(buff), (NULL));
	free(buff);
	return (stash);
}

char	*get_line(char	*stash)
{
	int		i;
	char	*line;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_line(char *stash)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	new_line = malloc(ft_strlen(stash + i) + 1);
	if (!new_line)
	{
		free(stash);
		return (NULL);
	}
	while (stash[i])
		new_line[j++] = stash[i++];
	new_line[j] = '\0';
	free(stash);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_join(stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	line = get_line(stash[fd]);
	if (!line)
		return (free(stash[fd]), NULL);
	stash[fd] = update_line(stash[fd]);
	if (!stash[fd])
		stash[fd] = NULL;
	return (line);
}
