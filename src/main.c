#include "cub3d.h"

/*
** validate_extension — returns 1 if filename ends with .cub, 0 otherwise.
*/
static int	validate_extension(const char *file)
{
	int	len;

	len = (int)strlen(file);
	if (len < 5)
		return (0);
	return (strcmp(file + len - 4, ".cub") == 0);
}

/*
** error_exit — prints error, cleans up and exits with status 1.
*/
void	error_exit(t_game *game, const char *msg)
{
	ft_error(msg);
	if (game)
		cleanup_game(game);
	exit(1);
}

/*
** init_game — initialise MLX, window and screen buffer.
*/
void	init_game(t_game *game, t_map_data *map)
{
	game->map = map;
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
		error_exit(game, "mlx_init failed");
	game->mlx.win = mlx_new_window(game->mlx.mlx,
			WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!game->mlx.win)
		error_exit(game, "mlx_new_window failed");
	game->mlx.img = mlx_new_image(game->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->mlx.img)
		error_exit(game, "mlx_new_image failed");
	game->mlx.addr = mlx_get_data_addr(game->mlx.img,
			&game->mlx.bpp, &game->mlx.line_len, &game->mlx.endian);
}

/*
** cleanup_game — free all game resources in order.
*/
void	cleanup_game(t_game *game)
{
	free_textures(game);
	if (game->map)
		free_map_data(game->map);
	if (game->mlx.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.img);
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_map_data	*map;

	if (argc != 2)
	{
		ft_error("Usage: ./cub3D <map.cub>");
		return (1);
	}
	if (!validate_extension(argv[1]))
	{
		ft_error("Error: file must have .cub extension");
		return (1);
	}
	map = parse_cub_file(argv[1]);
	if (!map)
	{
		ft_error("Error: failed to parse map file");
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	init_game(&game, map);
	if (!load_textures(&game))
		error_exit(&game, "Error: failed to load textures");
	mlx_hook(game.mlx.win, 2, 1L << 0, handle_keypress, &game);
	mlx_loop_hook(game.mlx.mlx, render_frame, &game);
	mlx_loop(game.mlx.mlx);
	cleanup_game(&game);
	return (0);
}
