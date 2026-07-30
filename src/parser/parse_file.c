/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 09:20:00 by jnovais           #+#    #+#             */
/*   Updated: 2026/07/16 23:00:54 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_map.h"

static int	is_cub_file(const char *file_path)
{
	int	len;

	len = ft_strlen(file_path);
	return (len > 4 && !ft_strncmp(file_path + len - 4, ".cub", 5));
}

static t_map_data	*open_map_file(const char *file_path, int *fd,
		const char **error)
{
	t_map_data	*data;

	if (!is_cub_file(file_path))
	{
		*error = "file must have .cub extension";
		return (NULL);
	}
	*fd = open(file_path, O_RDONLY);
	if (*fd < 0)
	{
		*error = "could not open map file";
		return (NULL);
	}
	data = ft_calloc(1, sizeof(*data));
	if (!data)
	{
		*error = "memory allocation failed";
		return (close(*fd), NULL);
	}
	data->floor_color.hex = -1;
	data->ceiling_color.hex = -1;
	return (data);
}

static int	close_read_error(int fd, char *line)
{
	free(line);
	close(fd);
	return (0);
}

static int	read_cub_content(int fd, t_map_data *data, const char **error)
{
	char	*line;
	int		map_started;

	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!read_file_line(data, line, &map_started, error))
			return (close_read_error(fd, line));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!map_started)
	{
		*error = "map is missing";
		return (0);
	}
	return (1);
}

t_map_data	*parse_cub_file(const char *file_path, const char **error)
{
	t_map_data	*data;
	int			fd;

	*error = "invalid map file";
	data = open_map_file(file_path, &fd, error);
	if (!data)
		return (NULL);
	if (!read_cub_content(fd, data, error))
	{
		return (free_map_data(data), NULL);
	}
	if (!validate_map(data))
	{
		*error = "map is invalid, open, or missing configuration";
		return (free_map_data(data), NULL);
	}
	return (data);
}
