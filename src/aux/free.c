/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:52:15 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/24 11:25:18 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void free_data(t_data **data)
{
    if (!data || !*data)
        return;

    free((*data)->mlx);
    free((*data)->win);
    free((*data)->keys);
    free_arr((*data)->map->map);
    free((*data)->map);
    free((*data)->img.img);
    free((*data)->img.frame);
    free((*data)->img.addr);
    free((*data)->textures.celling);
    free((*data)->textures.floor);
    free((*data)->textures.paths);
    free((*data)->textures.images);
    free(*data);
}
