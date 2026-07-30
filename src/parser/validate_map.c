/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 10:00:00 by jnovais           #+#    #+#             */
/*   Updated: 2026/07/29 22:15:32 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_map.h"

static int	is_player(char tile)
{
	return (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W');
}

static int	count_player(t_map_data *data, int x, int y)
{
	if (!is_player(data->map_grid[y][x]))
		return (0);
	data->player_start_x = x;
	data->player_start_y = y;
	data->player_dir = data->map_grid[y][x];
	return (1);
}

int	validate_tiles(t_map_data *data)
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
			players += count_player(data, x, y);
			x++;
		}
		y++;
	}
	return (players == 1);
}

static int	is_open(t_map_data *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map_width || y >= data->map_height)
		return (1);
	return (data->map_grid[y][x] == ' ');
}

int	validate_walls(t_map_data *data)
{
	int		x;
	int		y;
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
