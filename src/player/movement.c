#include "cub3d.h"

/*
** get_key_idx — map a hardware keycode to a KEY_IDX_* slot (0-5).
** Returns -1 for any key we do not track in the state array.
*/
static int	get_key_idx(int keycode)
{
	if (keycode == KEY_W)
		return (KEY_IDX_FWD);
	if (keycode == KEY_A)
		return (KEY_IDX_LEFT);
	if (keycode == KEY_S)
		return (KEY_IDX_BACK);
	if (keycode == KEY_D)
		return (KEY_IDX_RIGHT);
	if (keycode == KEY_LEFT)
		return (KEY_IDX_RLEFT);
	if (keycode == KEY_RIGHT)
		return (KEY_IDX_RRIGHT);
	return (-1);
}

/*
** handle_keypress — ESC quits immediately; all other tracked keys
** are marked active in the key-state array for the render loop.
*/
int	handle_keypress(int keycode, t_game *game)
{
	int	idx;

	if (keycode == KEY_ESC)
	{
		cleanup_game(game);
		exit(0);
	}
	idx = get_key_idx(keycode);
	if (idx >= 0)
		game->keys[idx] = 1;
	return (0);
}

/*
** handle_keyrelease — clear the key-state slot so the render loop
** stops processing that key on the next frame.
*/
int	handle_keyrelease(int keycode, t_game *game)
{
	int	idx;

	idx = get_key_idx(keycode);
	if (idx >= 0)
		game->keys[idx] = 0;
	return (0);
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
