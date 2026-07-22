#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>

# include "mlx.h"
# include "libft.h"
# include "parser.h"
# include "keycodes.h"

/* Window configuration */
# define WIN_WIDTH	1280
# define WIN_HEIGHT	720
# define WIN_TITLE	"cub3D"

/* Movement and rotation speed */
# define MOVE_SPEED	0.05
# define ROT_SPEED	0.03

/* Texture slot indices */
# define TEX_NO		0
# define TEX_SO		1
# define TEX_WE		2
# define TEX_EA		3
# define TEX_COUNT	4

/*
** t_tex — one loaded texture (image handle + dimensions)
*/
typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_tex;

/*
** t_player — player position and direction vectors
*/
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

/*
** t_mlx — MLX handle, window and screen buffer
*/
typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx;

/*
** t_game — central game state (passed to all engine functions)
*/
typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	t_tex		textures[TEX_COUNT];
	t_map_data	*map;
}	t_game;

/*
** t_ray — per-column raycasting intermediate data
*/
typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	int		step_y;
	int		side;
	double	wall_dist;
	int		line_h;
	int		draw_start;
	int		draw_end;
	int		tex_idx;
	double	wall_x;
}	t_ray;

/* --- Prototypes --- */

/* src/main.c */
void	init_game(t_game *game, t_map_data *map);
void	cleanup_game(t_game *game);
void	error_exit(t_game *game, const char *msg);

/* src/engine/raycasting.c */
void	cast_rays(t_game *game);

/* src/engine/renderer.c */
int		render_frame(t_game *game);
void	put_pixel(t_mlx *mlx, int x, int y, int color);
void	draw_tex_column(t_game *game, t_ray *ray, int x);

/* src/engine/textures.c */
int		load_textures(t_game *game);

/* src/player/init_player.c */
void	init_player(t_game *game);

/* src/player/movement.c */
int		handle_keypress(int keycode, t_game *game);
int		handle_close(t_game *game);

/* src/player/collision.c */
int		is_wall(t_game *game, double x, double y);

/* src/utils/error.c */
void	ft_error(const char *msg);

/* src/utils/memory.c */
void	free_textures(t_game *game);

#endif
