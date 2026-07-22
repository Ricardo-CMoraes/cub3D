/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:10:00 by jnovais           #+#    #+#             */
/*   Updated: 2026/07/16 23:00:46 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static int	set_texture(char **texture, char *value)
{
	int	fd;

	while (is_space(*value))
		value++;
	if (!*value || *texture)
		return (0);
	fd = open(value, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	*texture = ft_strdup(value);
	return (*texture != NULL);
}

static int	read_component(char **value, int *component)
{
	int	number;

	while (is_space(**value))
		(*value)++;
	if (**value < '0' || **value > '9')
		return (0);
	number = 0;
	while (**value >= '0' && **value <= '9')
	{
		number = number * 10 + (**value - '0');
		if (number > 255)
			return (0);
		(*value)++;
	}
	*component = number;
	return (1);
}

static int	set_color(t_color *color, char *value)
{
	int	index;
	int	component[3];

	if (color->hex != -1)
		return (0);
	index = 0;
	while (index < 3)
	{
		if (!read_component(&value, &component[index]))
			return (0);
		while (is_space(*value))
			value++;
		if (index++ < 2 && *value++ != ',')
			return (0);
	}
	while (is_space(*value))
		value++;
	if (*value)
		return (0);
	color->r = component[0];
	color->g = component[1];
	color->b = component[2];
	color->hex = (color->r << 16) + (color->g << 8) + color->b;
	return (1);
}

int	parse_config_line(t_map_data *data, char *line)
{
	if (!ft_strncmp(line, "NO", 2) && is_space(line[2]))
		return (set_texture(&data->no_texture, line + 2));
	if (!ft_strncmp(line, "SO", 2) && is_space(line[2]))
		return (set_texture(&data->so_texture, line + 2));
	if (!ft_strncmp(line, "WE", 2) && is_space(line[2]))
		return (set_texture(&data->we_texture, line + 2));
	if (!ft_strncmp(line, "EA", 2) && is_space(line[2]))
		return (set_texture(&data->ea_texture, line + 2));
	if (line[0] == 'F' && is_space(line[1]))
		return (set_color(&data->floor_color, line + 1));
	if (line[0] == 'C' && is_space(line[1]))
		return (set_color(&data->ceiling_color, line + 1));
	return (0);
}
