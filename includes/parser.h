/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 10:30:00 by jnovais          #+#    #+#             */
/*   Updated: 2026/07/16 10:00:00 by jnovais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	hex;
}t_color;

typedef struct s_map_data
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	t_color	floor_color;
	t_color	ceiling_color;
	char	**map_grid;
	int		map_width;
	int		map_height;
	int		player_start_x;
	int		player_start_y;
	char	player_dir;
}t_map_data;

t_map_data	*parse_cub_file(const char *file_path);
void		free_map_data(t_map_data *data);
int			parse_config_line(t_map_data *data, char *line);
int			is_map_line(char *line);
int			add_map_line(t_map_data *data, char *line);
int			validate_map(t_map_data *data);

#endif
