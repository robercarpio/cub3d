/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:23:18 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/16 16:48:23 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// static void	calc_perp_dist(t_dda_data *ray, t_player *p, int height)
// {
// 	if (ray->side == 0)
// 		ray->perp_dist = (ray->map_x - p->x
// 				+ (1 - ray->step_x) / 2.0) / ray->dir_x;
// 	else
// 		ray->perp_dist = (ray->map_y - p->y
// 				+ (1 - ray->step_y) / 2.0) / ray->dir_y;
// 	//!METER ESTO EN EL DDA
// 	// ray->line_height = (int)(height / ray->perp_dist);
// 	// ray->draw_start = -ray->line_height / 2 + height / 2;
// 	// ray->draw_end = ray->line_height / 2 + height / 2;
// 	if (ray->draw_start < 0)
// 		ray->draw_start = 0;
// 	if (ray->draw_end >= height)
// 		ray->draw_end = height - 1;
// }

// static void	draw_stripe_loop(t_stripe s, t_data *data, int x, t_dda_data *ray)
// {
// 	while (s.y <= ray->draw_end)
// 	{
// 		s.tex_y = (int)s.tex_pos & (TEX_HEIGHT - 1);
// 		s.tex_pos += s.step;
// 		s.frame[s.y * data->width + x]
// 			= s.tex_pixels[s.tex_y * s.tex_pitch + s.tex_x];
// 		s.y++;
// 	}
// }
static void	draw_stripe_loop(t_stripe s, t_data *data, int x, t_dda_data *ray)
{
	while (s.y <= ray->draw_end)
	{
		s.tex_y = (int)s.tex_pos & (TEX_HEIGHT - 1);
		s.tex_pos += s.step;
		
		// Usar TEX_WIDTH, no tex_pitch
		s.frame[s.y * data->width + x] = s.tex_pixels[s.tex_y * TEX_WIDTH + s.tex_x];
		
		s.y++;
	}
}

static void	draw_stripe(t_data *data, int x, t_dda_data *ray, t_img *tex)
{
	t_stripe	s;

	s.frame = (unsigned int *)data->img.addr;
	s.tex_pixels = (unsigned int *)tex->addr;
	
	// Calcular wall_x - punto exacto donde el rayo golpea la pared
	if (ray->side == 0)
		s.wall_x = data->player.y + ray->perpWallDist * ray->rayDirY;
	else
		s.wall_x = data->player.x + ray->perpWallDist * ray->rayDirX;
	
	s.wall_x -= floor(s.wall_x);
	
	// Calcular coordenada X de la textura
	s.tex_x = (int)(s.wall_x * (double)TEX_WIDTH);
	if ((ray->side == 0 && ray->rayDirX > 0) || (ray->side == 1 && ray->rayDirY < 0))
		s.tex_x = TEX_WIDTH - s.tex_x - 1;
	
	// Asegurar que tex_x está en rango válido
	if (s.tex_x < 0)
		s.tex_x = 0;
	if (s.tex_x >= TEX_WIDTH)
		s.tex_x = TEX_WIDTH - 1;
	
	// Calcular el paso y posición inicial para Y de la textura
	s.step = 1.0 * TEX_HEIGHT / ray->line_height;
	s.tex_pos = (ray->draw_start - data->height / 2 + ray->line_height / 2) * s.step;
	s.y = ray->draw_start;
	
	draw_stripe_loop(s, data, x, ray);
}


static t_img	*choose_texture(t_data *data, t_dda_data *ray)
{
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

static void	clear_frame(t_data *data)
{
	int				x;
	int				y;
	unsigned int	*frame;
	unsigned int	*bg;

	y = 0;
	frame = (unsigned int *)data->img.addr;
	bg = (unsigned int *)data->bgnd.addr;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			frame[y * data->width + x] = bg[y * data->width + x];
			x++;
		}
		y++;
	}
}



// int	ft_render_frame(t_data *data)
// {
// 	int		x;
// 	t_img	*tex;

// 	if (!data)
// 		return (-1);
	
// 	clear_frame(data);
	
// 	x = 0;
// 	while (x < data->width)  // <-- Usar data->width en lugar de data->map->m_width
// 	{
// 		raycast_dda(data);  // <-- ¿Necesitas recalcular raycast para cada columna?
// 		tex = choose_texture(data, &data->dda);
// 		draw_stripe(data, x, &data->dda, tex);
// 		x++;
// 	}
	
// 	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	
// 	return (0);
// }

// int	ft_render_frame(t_data *data)
// {
// 	int		x;
// 	t_img	*tex;

// 	if (!data)
// 		return (-1);
	
// 	clear_frame(data);
	
// 	x = 0;
// 	printf("DEBUG: data->width = %d, data->height = %d\n", data->width, data->height);
// 	while (x < data->width)  // Para cada columna de píxeles de la pantalla
// 	{
// 		if (x == 0 || x == 600 || x == 1199)
// 		{
// 			printf("Column %d: perpWallDist=%.2f, line_height=%d, draw_start=%d, draw_end=%d\n",
// 			x, data->dda.perpWallDist, data->dda.line_height, 
// 			data->dda.draw_start, data->dda.draw_end);
// 		}
// 		raycast_single_column(data, x);  // Calcular UN rayo para esta columna
// 		tex = choose_texture(data, &data->dda);
// 		draw_stripe(data, x, &data->dda, tex);
// 		x++;
// 		printf("Player: x=%.2f, y=%.2f, dir_x=%.2f, dir_y=%.2f\n",
//        data->player.x, data->player.y, 
//        data->player.dir_x, data->player.dir_y);
// 	}
	
// 	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	
// 	return (0);
// }
int	ft_render_frame(t_data *data)
{
	int		x;
	t_img	*tex;

	if (!data)
		return (-1);
	
	clear_frame(data);
	
	x = 0;
	printf("DEBUG: data->width = %d, data->height = %d\n", data->width, data->height);
	printf("Player: x=%.2f, y=%.2f, dir_x=%.2f, dir_y=%.2f\n",
	       data->player.x, data->player.y, 
	       data->player.dir_x, data->player.dir_y);
	
	while (x < data->width)
	{
		raycast_single_column(data, x);  // ← Primero calcular
		
		// Ahora sí, los valores son correctos
		if (x == 0 || x == 600 || x == 1199)
		{
			printf("Column %d: perpWallDist=%.2f, line_height=%d, draw_start=%d, draw_end=%d\n",
			       x, data->dda.perpWallDist, data->dda.line_height, 
			       data->dda.draw_start, data->dda.draw_end);
		}
		
		tex = choose_texture(data, &data->dda);
		draw_stripe(data, x, &data->dda, tex);
		x++;
	}
	
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	
	return (0);
}