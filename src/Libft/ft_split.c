/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:46:48 by mamaratr          #+#    #+#             */
/*   Updated: 2026/01/18 15:19:34 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int		x;
	int		count;

	x = 0;
	count = 0;
	while (s && s[x])
	{
		if (s[x] != c)
		{
			count++;
			while (s[x] != c && s[x])
				x++;
		}
		else
			x++;
	}
	return (count);
}

static char	**ft_free(char **strs, int x)
{
	while (x >= 0)
		free(strs[x--]);
	free(strs);
	return (NULL);
}

static size_t	ft_word_len(char const *s, char c)
{
	size_t	x;

	x = 0;
	while (s[x] && s[x] != c)
		x++;
	return (x);
}

char	**ft_split(char *s, char c)
{
	char	**strs;
	int		x;
	int		len;

	x = 0;
	strs = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!strs)
		return (NULL);
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		len = ft_word_len(s, c);
		if (len)
		{
			strs[x] = ft_substr(s, 0, len);
			if (!strs[x])
				return (ft_free(strs, x));
			x++;
		}
		s += len;
	}
	strs[x] = NULL;
	return (strs);
}
