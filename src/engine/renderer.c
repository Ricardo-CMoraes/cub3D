/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <rida-cos@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 23:27:03 by rida-cos          #+#    #+#             */
/*   Updated: 2026/07/26 23:27:08 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** put_pixel — write a colour to (x, y) in the MLX image buffer.
** Bounds-checked to avoid buffer overruns.
*/
void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
** get_tex_color — sample ARGB pixel from a loaded texture at (tex_x, tex_y).
*/
static int	get_tex_color(t_tex *tex, int tex_x, int tex_y)
{
	char	*pixel;

	pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

/*
** draw_tex_column — draw a single vertical textured wall strip for column x.
** Calculates the U coordinate (tex_x) and iterates over the projected height
** sampling V coordinates (tex_pos) from the source texture.
*/
void	draw_tex_column(t_game *game, t_ray *ray, int x)
{
	t_tex	*tex;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;

	tex = &game->textures[ray->tex_idx];
	tex_x = (int)(ray->wall_x * tex->width);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	step = 1.0 * tex->height / ray->line_h;
	tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_h / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		put_pixel(&game->mlx, x, y,
			get_tex_color(tex, tex_x, (int)tex_pos % tex->height));
		tex_pos += step;
		y++;
	}
}

/*
** draw_floor_ceiling — fill the top half with ceiling colour and the bottom
** half with floor colour using the RGB values from the parsed map.
*/
static void	draw_floor_ceiling(t_game *game, int fc, int cc)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(&game->mlx, x, y, cc);
			x++;
		}
		y++;
	}
	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(&game->mlx, x, y, fc);
			x++;
		}
		y++;
	}
}

/*
** render_frame — MLX loop hook: draw ceiling/floor, cast rays, flush buffer.
*/
int	render_frame(t_game *game)
{
	int	fc;
	int	cc;

	fc = game->map->floor_color.hex;
	cc = game->map->ceiling_color.hex;
	process_movement(game);
	draw_floor_ceiling(game, fc, cc);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx.mlx,
		game->mlx.win, game->mlx.img, 0, 0);
	return (0);
}
