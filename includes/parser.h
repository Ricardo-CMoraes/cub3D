#ifndef PARSER_H
# define PARSER_H

/* RGB color structure */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	hex;
}	t_color;

/*
** Contract: Parser <-> Engine
** The parser populates this struct and hands it to the graphic engine.
** The engine must NOT write to this struct directly.
** Memory is managed by: parse_cub_file() and free_map_data().
*/
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
}	t_map_data;

/* Parser public API */
t_map_data	*parse_cub_file(const char *file_path);
void		free_map_data(t_map_data *data);

#endif
