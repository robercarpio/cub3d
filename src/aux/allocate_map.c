/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:30:39 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/01/16 17:38:29 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char    **allocate_map(char **map)
{
    char    **arr;
    int     height;
    int     i;

    height = map_height(map);
    arr = (char **)malloc((height+1)*sizeof(char *));
    i = -1;
    while(map[++i])
        arr[i] = map[i];
    arr[height] = NULL;
    return (arr);
}