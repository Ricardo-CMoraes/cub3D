/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 10:00:00 by jnovais           #+#    #+#             */
/*   Updated: 2026/08/12 19:27:34 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_map.h"

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

static int	read_map_line(t_map_data *data, char *line, const char **error)
{
	if (is_blank_line(line) || !is_map_line(line))
	{
		*error = "empty or invalid line inside map";
		return (0);
	}
	remove_line_end(line);
	if (!add_map_line(data, line))
	{
		*error = "memory allocation failed while reading map";
		return (0);
	}
	return (1);
}

static int	read_config_line(t_map_data *data, char *line, int *map_started,
		const char **error)
{
	char	*trimmed;
	int		ok;

	if (is_blank_line(line))
		return (1);
	if (is_map_line(line))
	{
		*map_started = 1;
		return (read_map_line(data, line, error));
	}
	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
	{
		*error = "memory allocation failed while reading configuration";
		return (0);
	}
	ok = parse_config_line(data, trimmed);
	free(trimmed);
	if (!ok)
		*error = "invalid, duplicate, or inaccessible configuration";
	return (ok);
}

int	read_file_line(t_map_data *data, char *line, int *map_started,
		const char **error)
{
	if (*map_started)
		return (read_map_line(data, line, error));
	return (read_config_line(data, line, map_started, error));
}
