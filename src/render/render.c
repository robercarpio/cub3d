/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-cyepes <rcarpio-cyepes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:23:18 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/20 14:16:24 by rcarpio-cye      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	draw_stripe_loop(t_stripe s, t_data *data, int x, t_dda_data *ray)
{
	while (s.y <= ray->draw_end)
	{
		s.tex_y = (int)s.tex_pos & (TEX_HEIGHT - 1);
		s.tex_pos += s.step;
		s.frame[s.y * data->width + x] = s.tex_pixels[s.tex_y * TEX_WIDTH + s.tex_x];
		s.y++;
	}
}

static void	draw_stripe(t_data *data, int x, t_dda_data *ray, t_img *tex)
{
	t_stripe	s;

	s.frame = (unsigned int *)data->img.addr;
	s.tex_pixels = (unsigned int *)tex->addr;
	if (ray->side == 0)
		s.wall_x = data->player.y + ray->perpWallDist * ray->rayDirY;
	else
		s.wall_x = data->player.x + ray->perpWallDist * ray->rayDirX;
	
	s.wall_x -= floor(s.wall_x);
	s.tex_x = (int)(s.wall_x * (double)TEX_WIDTH);
	if ((ray->side == 0 && ray->rayDirX > 0) || (ray->side == 1 && ray->rayDirY < 0))
		s.tex_x = TEX_WIDTH - s.tex_x - 1;
	if (s.tex_x < 0)
		s.tex_x = 0;
	if (s.tex_x >= TEX_WIDTH)
		s.tex_x = TEX_WIDTH - 1;
	s.step = 1.0 * TEX_HEIGHT / ray->line_height;
	s.tex_pos = (ray->draw_start - data->height / 2 + ray->line_height / 2) * s.step;
	s.y = ray->draw_start;
	
	draw_stripe_loop(s, data, x, ray);
}

static t_img	*choose_texture(t_data *data, t_dda_data *ray)
{
	if (ray->hit_type == 'D')
		return (&data->textures.images[TEX_DOOR]);
	if (ray->side == 0)
	{
		if (ray->rayDirX > 0)
			return (&data->textures.images[TEX_EAST]);
		else
			return (&data->textures.images[TEX_WEST]);
	}
	else
	{
		if (ray->rayDirY > 0)
			return (&data->textures.images[TEX_SOUTH]);
		else
			return (&data->textures.images[TEX_NORTH]);
	}
}

int	ft_render_frame(t_data *data)
{
	int		x;
	t_img	*tex;

	if (!data)
		return (-1);
	draw_floor_ceiling(data);
	x = 0;
	while (x < data->width)
	{
		raycast_single_column(data, x);
		tex = choose_texture(data, &data->dda);
		draw_stripe(data, x, &data->dda, tex);
		x++;
	}
	draw_minimap(data);
	draw_minimap_border(data);
	draw_minimap_player(data);
	if (data->show_bigmap)
		draw_bigmap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}
