#include "cub3d.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		cleanup_game(game);
		exit(0);
	}
	/* TODO: implement WASD movement and arrow key rotation */
	(void)game;
	return (0);
}
