/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <rida-cos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 21:44:45 by rida-cos          #+#    #+#             */
/*   Updated: 2026/07/22 21:44:47 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** move_player — translate the player by (dx, dy) with per-axis
** collision detection so the player slides along walls.
*/
static void	move_player(t_game *game, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = game->player.pos_x + dx;
	ny = game->player.pos_y + dy;
	if (!is_wall(game, nx, game->player.pos_y))
		game->player.pos_x = nx;
	if (!is_wall(game, game->player.pos_x, ny))
		game->player.pos_y = ny;
}

/*
** rotate_player — rotate the direction vector and camera plane by
** angle (radians) using a 2D rotation matrix.
*/
static void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = old_dir_x * cos(angle) - game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y * cos(angle);
	game->player.plane_x = old_plane_x * cos(angle) - game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y * cos(angle);
}

/*
** process_movement — called every frame from the render loop.
** Reads the key-state array and applies movement / rotation.
** This allows smooth, continuous motion while a key is held.
*/
void	process_movement(t_game *game)
{
	double	spd;

	spd = MOVE_SPEED;
	if (game->keys[KEY_IDX_FWD])
		move_player(game, game->player.dir_x * spd, game->player.dir_y * spd);
	if (game->keys[KEY_IDX_BACK])
		move_player(game, -game->player.dir_x * spd, -game->player.dir_y * spd);
	if (game->keys[KEY_IDX_LEFT])
		move_player(game, game->player.dir_y * spd, -game->player.dir_x * spd);
	if (game->keys[KEY_IDX_RIGHT])
		move_player(game, -game->player.dir_y * spd, game->player.dir_x * spd);
	if (game->keys[KEY_IDX_RLEFT])
		rotate_player(game, -ROT_SPEED);
	if (game->keys[KEY_IDX_RRIGHT])
		rotate_player(game, ROT_SPEED);
}
