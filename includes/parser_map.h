/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 10:00:00 by jnovais           #+#    #+#             */
/*   Updated: 2026/08/08 09:32:27 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_MAP_H
# define PARSER_MAP_H

# include "parser.h"

int		map_height(char **map);
void	free_map_grid(char **grid);
int		normalize_map(t_map_data *data);
int		validate_tiles(t_map_data *data);
int		validate_walls(t_map_data *data);
int		read_file_line(t_map_data *data, char *line, int *map_started,
			const char **error);

#endif
