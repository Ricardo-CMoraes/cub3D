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

#include "parser.h"

static const char	*g_parse_error = "invalid map file";

const char	*get_parse_error(void)
{
	return (g_parse_error);
}

static int	is_cub_file(const char *file_path)
{
	int	len;

	len = ft_strlen(file_path);
	return (len > 4 && !ft_strncmp(file_path + len - 4, ".cub", 5));
}

static int	is_blank_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

static void	remove_line_end(char *line)
{
	int	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		line[--len] = '\0';
}

static int	read_line(t_map_data *data, char *line, int *map_started)
{
	char	*trimmed;
	int		ok;

	if (*map_started)
	{
		if (is_blank_line(line) || !is_map_line(line))
		{
			g_parse_error = "empty or invalid line inside map";
			return (0);
		}
		remove_line_end(line);
		ok = add_map_line(data, line);
		if (!ok)
			g_parse_error = "memory allocation failed while reading map";
		return (ok);
	}
	if (is_blank_line(line))
		return (1);
	if (is_map_line(line))
	{
		*map_started = 1;
		remove_line_end(line);
		ok = add_map_line(data, line);
		if (!ok)
			g_parse_error = "memory allocation failed while reading map";
		return (ok);
	}
	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
	{
		g_parse_error = "memory allocation failed while reading configuration";
		return (0);
	}
	ok = parse_config_line(data, trimmed);
	free(trimmed);
	if (!ok)
		g_parse_error = "invalid, duplicate, or inaccessible configuration";
	return (ok);
}

t_map_data	*parse_cub_file(const char *file_path)
{
	t_map_data	*data;
	char		*line;
	int			fd;
	int			map_started;

	g_parse_error = "invalid map file";
	if (!is_cub_file(file_path))
	{
		g_parse_error = "file must have .cub extension";
		return (NULL);
	}
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		g_parse_error = "could not open map file";
		return (NULL);
	}
	data = ft_calloc(1, sizeof(*data));
	if (!data)
	{
		g_parse_error = "memory allocation failed";
		return (close(fd), NULL);
	}
	data->floor_color.hex = -1;
	data->ceiling_color.hex = -1;
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!read_line(data, line, &map_started))
		{
			free(line);
			close(fd);
			free_map_data(data);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!map_started)
	{
		g_parse_error = "map is missing";
		return (free_map_data(data), NULL);
	}
	if (!validate_map(data))
	{
		g_parse_error = "map is invalid, open, or missing configuration";
		return (free_map_data(data), NULL);
	}
	return (data);
}
