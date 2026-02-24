/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:13:56 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/22 09:52:32 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *s)
{
	int	length;
	int	x;

	x = 0;
	length = 0;
	while (s[x])
	{
		x++;
		length++;
	}
	return (length);
}
