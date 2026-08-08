/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <rida-cos@student.42.ft>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 21:48:18 by rida-cos          #+#    #+#             */
/*   Updated: 2026/07/26 21:35:42 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** ft_error — write error message to stderr.
*/
void	ft_error(const char *msg)
{
	write(2, "Error\n", 6);
	if (msg && *msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
}

/*
** error_exit — prints error, cleans up and exits with status 1.
*/
void	error_exit(t_game *game, const char *msg)
{
	ft_error(msg);
	if (game)
		cleanup_game(game);
	exit(1);
}
