/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skabny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:26:49 by skabny            #+#    #+#             */
/*   Updated: 2025/11/15 09:46:59 by skabny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_join(int fd, char *stash)
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

char	*get_line(char *stash)
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
		line[i] = '\n';
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
		return (free(stash),NULL);
	while (stash[i])
		new_line[j++] = stash[i++];
	new_line[j] = '\0';
	free(stash);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_join(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line(stash);
	if (!line)
		return (free(stash), NULL);
	stash = update_line(stash);
	if (!stash)
	{
		stash = NULL;
	}
	return (line);
}
