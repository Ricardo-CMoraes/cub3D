/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rida-cos <rida-cos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 21:48:18 by rida-cos          #+#    #+#             */
/*   Updated: 2026/07/22 21:48:20 by rida-cos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** ft_error — write error message to stderr.
*/
void	ft_error(const char *msg)
{
	write(2, msg, strlen(msg));
	write(2, "\n", 1);
}
