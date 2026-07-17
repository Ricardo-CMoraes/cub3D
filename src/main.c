/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 11:45:00 by jnovais           #+#    #+#             */
/*   Updated: 2026/07/16 23:00:38 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map_data	*map;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <map.cub>\n", 31);
		return (1);
	}
	map = parse_cub_file(argv[1]);
	if (!map)
	{
		write(2, "Error\nInvalid .cub file\n", 25);
		return (1);
	}
	write(1, "Map parsed and validated successfully.\n", 39);
	free_map_data(map);
	return (0);
}
