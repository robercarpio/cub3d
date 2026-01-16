/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:32:29 by rcarpio-          #+#    #+#             */
/*   Updated: 2026/01/15 13:10:41 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// char	*ft_strchr(char *s, int c)
// {
// 	int				b;
// 	unsigned char	ch;

// 	if (!s)
// 		return (NULL);
// 	ch = c;
// 	b = 0;
// 	while (*s && b != 1)
// 	{
// 		if (*s != ch)
// 			s++;
// 		else
// 			b = 1;
// 	}
// 	if (!*s && ch != '\0')
// 		return (0);
// 	return ((char *)s);
// }

// char	*ft_strdup(char *s)
// {
// 	char	*str;
// 	size_t	len;
// 	size_t	i;

// 	if (!s)
// 		return (NULL);
// 	len = ft_strlen(s);
// 	str = malloc(len + 1);
// 	if (str != NULL)
// 	{
// 		i = 0;
// 		while (i < len)
// 		{
// 			str[i] = s[i];
// 			i++;
// 		}
// 		str[i] = '\0';
// 		return (str);
// 	}
// 	else
// 		return (NULL);
// }

int	ft_indexof(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	char	*substr;
// 	size_t	len_s;

// 	if (!s)
// 		return (NULL);
// 	len_s = ft_strlen(s);
// 	if (start >= len_s)
// 	{
// 		return (ft_strdup(""));
// 	}
// 	if (len > len_s - start)
// 		len = len_s - start;
// 	substr = (char *)malloc(len + 1);
// 	if (!substr)
// 		return (0);
// 	ft_strlcpy(substr, s + start, len + 1);
// 	return (substr);
// }

// size_t	ft_strlcpy(char *dst, char *src, size_t size)
// {
// 	size_t	i;
// 	size_t	r;

// 	if (!dst || !src)
// 		return (0);
// 	i = 0;
// 	r = 0;
// 	while (src[r] != '\0')
// 	{
// 		r++;
// 	}
// 	if (size == 0)
// 		return (r);
// 	if (size > 0)
// 	{
// 		while (i < size - 1 && src[i] != '\0')
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 		dst[i] = '\0';
// 	}
// 	return (r);
// }
