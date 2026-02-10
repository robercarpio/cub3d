/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:03:07 by rcarpio-cye       #+#    #+#             */
/*   Updated: 2026/02/10 15:57:57 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void print_map(t_map map)
{
	int i;
	
	i = 0;
	while (map.map[i])
	{
		printf("%s", map.map[i]);
		i++;
	}
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s",arr[i]);
		i++;
	}
}

void	play (char *route)
{
	if (!cub_file(route))
		printf("Error!\nInvalid map file\nUsage: ./cub3d <map.cub>\n");	
	else
		parse(file_to_arr(route));
}

