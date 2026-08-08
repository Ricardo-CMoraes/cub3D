/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 21:55:28 by jnovais           #+#    #+#             */
/*   Updated: 2026/07/29 21:55:28 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** validate_extension — returns 1 if filename ends with .cub, 0 otherwise.
*/
static int	validate_extension(const char *file)
{
	int	len;
	int	cmp_result;

	len = (int)ft_strlen(file);
	if (len < 5)
		return (0);
	cmp_result = ft_strncmp(file + len - 4, ".cub", 4);
	return (cmp_result == 0);
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
	init_player(game);
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
	const char	*parse_error;

	if (argc != 2)
		error_exit(NULL, "Usage: ./cub3D <map.cub>");
	if (!validate_extension(argv[1]))
		error_exit(NULL, "file must have .cub extension");
	map = parse_cub_file(argv[1], &parse_error);
	if (!map)
		error_exit(NULL, parse_error);
	ft_memset(&game, 0, sizeof(t_game));
	init_game(&game, map);
	if (!load_textures(&game))
		error_exit(&game, "failed to load textures");
	mlx_hook(game.mlx.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, handle_keyrelease, &game);
	mlx_hook(game.mlx.win, 17, 0, handle_close, &game);
	mlx_loop_hook(game.mlx.mlx, render_frame, &game);
	mlx_loop(game.mlx.mlx);
	cleanup_game(&game);
	return (0);
}
