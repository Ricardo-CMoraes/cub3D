/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:07:17 by jnovais           #+#    #+#             */
/*   Updated: 2025/07/28 19:08:06 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	pos;

	if (little[0] == '\0')
		return ((char *)big);
	pos = 0;
	while (big[pos] && pos < len)
	{
		if (big[pos] == little[0])
		{
			i = 1;
			while (little[i] && (pos + i) < len && big[pos + i] == little[i])
				i++;
			if (little[i] == '\0')
				return ((char *) big + pos);
		}
		pos++;
	}
	return (0);
}
