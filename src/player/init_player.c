#include "cub3d.h"

static void	set_player_dir(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

/*
** init_player — set starting position, direction and camera plane
** from the parsed map data (player_start_x/y and player_dir).
*/
void	init_player(t_game *game)
{
	game->player.pos_x = game->map->player_start_x + 0.5;
	game->player.pos_y = game->map->player_start_y + 0.5;
	set_player_dir(&game->player, game->map->player_dir);
}
