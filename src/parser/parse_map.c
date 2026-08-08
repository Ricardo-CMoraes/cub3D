/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 08:50:00 by jnovais           #+#    #+#             */
/*   Updated: 2026/07/16 23:01:01 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_map.h"

int	map_height(char **map)
{
	int	height;

	height = 0;
	while (map && map[height])
		height++;
	return (height);
}

void	free_map_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid && grid[i])
		free(grid[i++]);
	free(grid);
}

int	add_map_line(t_map_data *data, char *line)
{
	char	**new_grid;
	int		height;

	height = map_height(data->map_grid);
	new_grid = malloc(sizeof(char *) * (height + 2));
	if (!new_grid)
		return (0);
	if (height)
		ft_memcpy(new_grid, data->map_grid, sizeof(char *) * height);
	new_grid[height] = ft_strdup(line);
	new_grid[height + 1] = NULL;
	free(data->map_grid);
	if (!new_grid[height])
		return (free(new_grid), 0);
	data->map_grid = new_grid;
	return (1);
}

int	is_map_line(char *line)
{
	int	has_tile;

	has_tile = 0;
	while (*line && *line != '\n' && *line != '\r')
	{
		if (*line != ' ' && *line != '\t' && *line != '0' && *line != '1'
			&& *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
			return (0);
		if (*line != ' ' && *line != '\t')
			has_tile = 1;
		line++;
	}
	return (has_tile);
}

void	free_map_data(t_map_data *data)
{
	if (!data)
		return ;
	free(data->no_texture);
	free(data->so_texture);
	free(data->we_texture);
	free(data->ea_texture);
	free_map_grid(data->map_grid);
	free(data);
}
