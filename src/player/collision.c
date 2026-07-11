#include "cub3d.h"

int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map->map_width)
		return (1);
	if (map_y < 0 || map_y >= game->map->map_height)
		return (1);
	return (game->map->map_grid[map_y][map_x] == '1');
}
