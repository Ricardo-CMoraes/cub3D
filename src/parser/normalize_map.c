/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 10:00:00 by jnovais           #+#    #+#             */
/*   Updated: 2026/07/29 10:00:00 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_map.h"

static void	set_map_dimensions(t_map_data *data)
{
	int	y;
	int	len;

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
}

static char	**create_normalized_grid(t_map_data *data)
{
	char	**grid;
	int		y;

	grid = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!grid)
		return (NULL);
	y = 0;
	while (y < data->map_height)
	{
		grid[y] = ft_calloc(data->map_width + 1, sizeof(char));
		if (!grid[y])
			return (free_map_grid(grid), NULL);
		ft_memset(grid[y], ' ', data->map_width);
		ft_memcpy(grid[y], data->map_grid[y], ft_strlen(data->map_grid[y]));
		y++;
	}
	return (grid);
}

int	normalize_map(t_map_data *data)
{
	char	**grid;

	set_map_dimensions(data);
	grid = create_normalized_grid(data);
	if (!grid)
		return (0);
	free_map_grid(data->map_grid);
	data->map_grid = grid;
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
