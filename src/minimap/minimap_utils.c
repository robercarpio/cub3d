/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 11:21:27 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/26 11:32:07 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	check_if_wall(t_data *data, int map_x, int map_y, int *color)
{
	if (map_y >= 0 && map_y < data->map->m_height
		&& map_x >= 0 && data->map->map[map_y]
		&& map_x < (int)ft_strlen(data->map->map[map_y]))
	{
		if (data->map->map[map_y][map_x] == '1')
			*color = 0xFFFFFF;
	}
}
