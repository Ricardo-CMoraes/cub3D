#include "parser.h"
#include <stdlib.h>

void	free_map_data(t_map_data *data)
{
	int	i;

	if (!data)
		return ;
	free(data->no_texture);
	free(data->so_texture);
	free(data->we_texture);
	free(data->ea_texture);
	i = 0;
	if (data->map_grid)
	{
		while (i < data->map_height)
		{
			free(data->map_grid[i]);
			i++;
		}
		free(data->map_grid);
	}
	free(data);
}

/* TODO: Joao — validate map is fully enclosed by walls */
