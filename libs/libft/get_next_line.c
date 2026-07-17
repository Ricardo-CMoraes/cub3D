/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 21:22:48 by jnovais           #+#    #+#             */
/*   Updated: 2025/10/13 21:22:48 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_join_and_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

static char	*next_line(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (line == NULL)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

static char	*get_line(char *list)
{
	char	*next_str;
	int		i;

	i = 0;
	if (!list[i])
		return (NULL);
	while (list[i] && list[i] != '\n')
		i++;
	next_str = ft_calloc(i + 2, sizeof(char));
	if (next_str == NULL)
		return (NULL);
	i = 0;
	while (list[i] && list[i] != '\n')
	{
		next_str[i] = list[i];
		i++;
	}
	if (list[i] && list[i] == '\n')
		next_str[i++] = '\n';
	return (next_str);
}

static char	*read_all(char *list, int fd)
{
	char	*buf;
	int		char_read;

	if (!list)
		list = ft_calloc(1, 1);
	if (list && ft_strchr(list, '\n'))
		return (list);
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	char_read = 1;
	while (char_read > 0)
	{
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read < 0)
		{
			free(buf);
			free(list);
			return (NULL);
		}
		buf[char_read] = 0;
		list = ft_join_and_free(list, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (list);
}

char	*get_next_line(int fd)
{
	static char	*list;
	char		*line_current;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	list = read_all(list, fd);
	if (!list)
		return (NULL);
	line_current = get_line(list);
	list = next_line(list);
	return (line_current);
}
