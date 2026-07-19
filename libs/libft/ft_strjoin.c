/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:48:01 by jnovais           #+#    #+#             */
/*   Updated: 2025/08/01 20:48:23 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	x;
	char			*dest;

	if (!s1 || !s2)
		return (0);
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	x = 0;
	while (s1[i])
		dest[x++] = s1[i++];
	i = 0;
	while (s2[i])
		dest[x++] = s2[i++];
	dest[x] = '\0';
	return (dest);
}
