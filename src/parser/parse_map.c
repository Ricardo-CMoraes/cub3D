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

#include "parser.h"

static int	map_height(char **map)
{
	int	height;

	height = 0;
	while (map && map[height])
		height++;
	return (height);
}

static void	free_grid(char **grid)
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

static int	normalize_map(t_map_data *data)
{
	char	**grid;
	int		y;
	int		len;

	data->map_height = map_height(data->map_grid);
	data->map_width = 0;
	y = 0;
	while (y < data->map_height)
	{
		len = ft_strlen(data->map_grid[y]);
		if (len > data->map_width)
			data->map_width = len;
		y++;
	}
	grid = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!grid)
		return (0);
	y = 0;
	while (y < data->map_height)
	{
		grid[y] = malloc(data->map_width + 1);
		if (!grid[y])
			return (free_grid(grid), 0);
		ft_memset(grid[y], ' ', data->map_width);
		ft_memcpy(grid[y], data->map_grid[y], ft_strlen(data->map_grid[y]));
		grid[y++][data->map_width] = '\0';
	}
	free_grid(data->map_grid);
	data->map_grid = grid;
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

static int	is_player(char tile)
{
	return (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W');
}

static int	is_open(t_map_data *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map_width || y >= data->map_height)
		return (1);
	return (data->map_grid[y][x] == ' ');
}

static int	validate_tiles(t_map_data *data)
{
	int	x;
	int	y;
	int	players;

	players = 0;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (!ft_strchr(" 01NSEW", data->map_grid[y][x]))
				return (0);
			if (is_player(data->map_grid[y][x]))
			{
				data->player_start_x = x;
				data->player_start_y = y;
				data->player_dir = data->map_grid[y][x];
				players++;
			}
			x++;
		}
		y++;
	}
	return (players == 1);
}

static int	validate_walls(t_map_data *data)
{
	int	x;
	int	y;
	char	tile;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			tile = data->map_grid[y][x];
			if ((tile == '0' || is_player(tile)) && (is_open(data, x - 1, y)
					|| is_open(data, x + 1, y) || is_open(data, x, y - 1)
					|| is_open(data, x, y + 1)))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_map(t_map_data *data)
{
	if (!data->no_texture || !data->so_texture || !data->we_texture
		|| !data->ea_texture || data->floor_color.hex < 0
		|| data->ceiling_color.hex < 0 || !normalize_map(data))
		return (0);
	return (validate_tiles(data) && validate_walls(data));
}

void	free_map_data(t_map_data *data)
{
	if (!data)
		return ;
	free(data->no_texture);
	free(data->so_texture);
	free(data->we_texture);
	free(data->ea_texture);
	free_grid(data->map_grid);
	free(data);
}
