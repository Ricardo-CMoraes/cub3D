/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:04:35 by jnovais           #+#    #+#             */
/*   Updated: 2025/08/05 20:29:53 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calculate_size(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	else if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long		num;
	char		*dest;
	ssize_t		size;

	num = n;
	size = calculate_size(num);
	dest = malloc (sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = '\0';
	if (num == 0)
		dest[0] = '0';
	if (num < 0)
		num *= -1;
	while (num)
	{
		dest[--size] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		dest[0] = '-';
	return (dest);
}
