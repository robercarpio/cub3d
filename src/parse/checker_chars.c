/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 13:58:54 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/11 11:39:32 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int only_chars_allow(char *str, char *allow)
{
	int	i;
	int	b;

	while (*str)
	{
		b = 0;
		i = 0;
		while (allow[i] && b != 1)
		{
			if (*str == allow[i] || *str == '\n')
				b = 1;
			i++;
		}
		if (b == 0)
			return (0);
		str++;
	}
	return (b);
}

int check_chars(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		if (!only_chars_allow(map[i], "01NSEW "))
			return (0);
		i++;
	}
	return (1);
}
