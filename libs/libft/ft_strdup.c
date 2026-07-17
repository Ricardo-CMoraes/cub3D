/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:22:18 by jnovais           #+#    #+#             */
/*   Updated: 2025/07/28 19:40:48 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dest;

	i = 0;
	dest = malloc (sizeof(char) * (ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	while (*s)
		dest[i++] = *s++;
	dest[i] = '\0';
	return (dest);
}
