/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:03:07 by rcarpio-cye       #+#    #+#             */
/*   Updated: 2026/02/05 14:08:11 by rcarpio-mam      ###   ########.fr       */
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

int	play (char *route)
{
	char	**arr;

	arr = file_to_arr(route);
	if (!arr)
		return (0);
	t_map map = init_map(arr);
	print_arr(expand_map(map));
	// print_map(map);
	// printf("\n");
	// printf("HEIGHT %d \n",map.m_height);
	// printf("WIDTH %d \n",map.m_width);
	return (1);	
}
