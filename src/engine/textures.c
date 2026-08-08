/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <rida-cos@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 23:15:10 by rida-cos          #+#    #+#             */
/*   Updated: 2026/07/26 23:15:12 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** load_one_tex — load a single XPM file into MLX and populate t_tex fields.
** Returns 1 on success, 0 on failure (file not found or mlx error).
*/
static int	load_one_tex(t_game *game, int idx, char *path)
{
	t_tex	*t;

	t = &game->textures[idx];
	t->img = mlx_xpm_file_to_image(game->mlx.mlx, path,
			&t->width, &t->height);
	if (!t->img)
		return (0);
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->line_len, &t->endian);
	return (1);
}

/*
** load_textures — load all four wall textures (NO, SO, WE, EA) from the
** paths stored in t_map_data. Returns 1 on success, 0 if any fails.
*/
int	load_textures(t_game *game)
{
	if (!load_one_tex(game, TEX_NO, game->map->no_texture))
		return (0);
	if (!load_one_tex(game, TEX_SO, game->map->so_texture))
		return (0);
	if (!load_one_tex(game, TEX_WE, game->map->we_texture))
		return (0);
	if (!load_one_tex(game, TEX_EA, game->map->ea_texture))
		return (0);
	return (1);
}

/*
** set_ray_texture — select the correct texture based on the wall hit.
*/
void	set_ray_texture(t_ray *ray)
{
	if (ray->side == 0 && ray->step_x > 0)
		ray->tex_idx = TEX_EA;
	else if (ray->side == 0 && ray->step_x < 0)
		ray->tex_idx = TEX_WE;
	else if (ray->side == 1 && ray->step_y > 0)
		ray->tex_idx = TEX_SO;
	else if (ray->side == 1 && ray->step_y < 0)
		ray->tex_idx = TEX_NO;
}
