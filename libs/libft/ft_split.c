/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovais <jnovais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:06:18 by jnovais           #+#    #+#             */
/*   Updated: 2025/08/05 20:16:33 by jnovais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	next;

	i = 0;
	next = 0;
	while (*str)
	{
		if (*str != c && next == 0)
		{
			next = 1;
			i++;
		}
		else if (*str == c)
			next = 0;
		str++;
	}
	return (i);
}

static char	*word_sep(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static char	**free_split(char **split, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static char	**make_split(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;
	ssize_t	start_w;

	i = 0;
	j = 0;
	start_w = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start_w < 0)
			start_w = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start_w >= 0)
		{
			split[j] = word_sep(s, start_w, i);
			if (!split[j])
			{
				return (free_split(split, j));
			}
			j++;
			start_w = -1;
		}
		i++;
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	make_split(split, s, c);
	return (split);
}
