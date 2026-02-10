/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:30:46 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/10 15:58:34 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	parse(char **map)
{
	if (!check_chars(map))
	{
		printf("Error: Invalid characters in the map.\n");
		return (0);
	}
	else
		return (1);
}