#include "cub3d.h"

/*
** move_player — translate the player by (move_x, move_y), applying
** per-axis collision detection against the map grid.
*/
static void	move_player(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + move_x;
	new_y = game->player.pos_y + move_y;
	if (!is_wall(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_wall(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/*
** rotate_player — rotate direction vector and camera plane by angle (radians)
** using a 2D rotation matrix.
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
** handle_close — MLX hook for the window close button (event 17).
*/
int	handle_close(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

/*
** handle_keypress — dispatch key events: ESC quits, WASD moves,
** LEFT/RIGHT arrow keys rotate the player.
*/
int	handle_keypress(int keycode, t_game *game)
{
	double	spd;

	spd = MOVE_SPEED;
	if (keycode == KEY_ESC)
	{
		cleanup_game(game);
		exit(0);
	}
	if (keycode == KEY_W)
		move_player(game, game->player.dir_x * spd, game->player.dir_y * spd);
	if (keycode == KEY_S)
		move_player(game, -game->player.dir_x * spd, -game->player.dir_y * spd);
	if (keycode == KEY_A)
		move_player(game, game->player.dir_y * spd, -game->player.dir_x * spd);
	if (keycode == KEY_D)
		move_player(game, -game->player.dir_y * spd, game->player.dir_x * spd);
	if (keycode == KEY_LEFT)
		rotate_player(game, -ROT_SPEED);
	if (keycode == KEY_RIGHT)
		rotate_player(game, ROT_SPEED);
	return (0);
}
