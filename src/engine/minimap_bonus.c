/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 00:00:00 by rida-cos          #+#    #+#             */
/*   Updated: 2026/08/12 19:27:52 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_minimap_tile(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	start_x = MM_OFFSET_X + (x * MM_TILE_SIZE);
	start_y = MM_OFFSET_Y + (y * MM_TILE_SIZE);
	j = 0;
	while (j < MM_TILE_SIZE)
	{
		i = 0;
		while (i < MM_TILE_SIZE)
		{
			put_pixel(&game->mlx, start_x + i, start_y + j, color);
			i++;
		}
		j++;
	}
}

static void	draw_player_marker(t_game *game)
{
	int	px;
	int	py;
	int	i;
	int	j;

	px = MM_OFFSET_X + (int)(game->player.pos_x * MM_TILE_SIZE);
	py = MM_OFFSET_Y + (int)(game->player.pos_y * MM_TILE_SIZE);
	j = -1;
	while (j <= 1)
	{
		i = -1;
		while (i <= 1)
		{
			put_pixel(&game->mlx, px + i, py + j, MM_PLAYER_COLOR);
			i++;
		}
		j++;
	}
}

static void	draw_minimap_line(t_game *game, t_line l, int color)
{
	double	dx;
	double	dy;
	double	steps;
	int		i;

	dx = l.x1 - l.x0;
	dy = l.y1 - l.y0;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	i = 0;
	while (i <= steps)
	{
		put_pixel(&game->mlx, (int)l.x0, (int)l.y0, color);
		l.x0 += dx / steps;
		l.y0 += dy / steps;
		i++;
	}
}

static void	draw_player_fov(t_game *game)
{
	t_line	l;
	double	px;
	double	py;
	double	len;

	px = MM_OFFSET_X + (game->player.pos_x * MM_TILE_SIZE);
	py = MM_OFFSET_Y + (game->player.pos_y * MM_TILE_SIZE);
	len = 3.0 * MM_TILE_SIZE;
	l.x0 = px;
	l.y0 = py;
	l.x1 = px + (game->player.dir_x - game->player.plane_x) * len;
	l.y1 = py + (game->player.dir_y - game->player.plane_y) * len;
	draw_minimap_line(game, l, MM_FOV_COLOR);
	l.x1 = px + (game->player.dir_x + game->player.plane_x) * len;
	l.y1 = py + (game->player.dir_y + game->player.plane_y) * len;
	draw_minimap_line(game, l, MM_FOV_COLOR);
}

void	render_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->map_height)
	{
		x = 0;
		while (x < game->map->map_width)
		{
			if (game->map->map_grid[y][x] == '1')
				draw_minimap_tile(game, x, y, MM_WALL_COLOR);
			else if (game->map->map_grid[y][x] == '0' ||
				ft_strchr("NSEW", game->map->map_grid[y][x]))
				draw_minimap_tile(game, x, y, MM_EMPTY_COLOR);
			x++;
		}
		y++;
	}
	draw_player_fov(game);
	draw_player_marker(game);
}
