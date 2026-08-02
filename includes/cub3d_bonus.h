/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <rida-cos@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 00:00:00 by rida-cos          #+#    #+#             */
/*   Updated: 2026/08/02 00:00:00 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"

/* Minimap definitions */
# define MM_TILE_SIZE		8
# define MM_OFFSET_X		10
# define MM_OFFSET_Y		10

/* Minimap colours */
# define MM_WALL_COLOR		0x00FFFFFF	/* White */
# define MM_EMPTY_COLOR		0x00000000	/* Black */
# define MM_PLAYER_COLOR	0x00FF0000	/* Red */
# define MM_FOV_COLOR		0x00FFFF00	/* Yellow */

typedef struct s_line
{
	double	x0;
	double	y0;
	double	x1;
	double	y1;
}	t_line;

/* src/engine/minimap_bonus.c */
void	render_minimap(t_game *game);
void	draw_minimap_tile(t_game *game, int x, int y, int color);

#endif
