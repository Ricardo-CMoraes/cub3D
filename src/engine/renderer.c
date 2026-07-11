#include "cub3d.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

int	render_frame(t_game *game)
{
	cast_rays(game);
	mlx_put_image_to_window(game->mlx.mlx,
		game->mlx.win, game->mlx.img, 0, 0);
	return (0);
}
