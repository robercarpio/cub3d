/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:30:46 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/17 09:29:52 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	parse(t_data data)
{
	if (!check_chars(data.map->map))
	{
		printf("Error: Invalid characters in the map.\n");	
		return (0);
	}
	else
	{
		if (closed_map(data))
			printf("bien\n");
		else
		{
			printf("mal\n");
			return (0);
		}
	}
	return (1);
}