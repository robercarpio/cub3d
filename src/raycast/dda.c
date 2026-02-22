/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:05:12 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/22 10:32:19 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	reset_dda_data(t_dda_data *dda)
{
	dda->raydir_x = 0;
	dda->raydir_y = 0;
	dda->map_x = 0;
	dda->map_y = 0;
	dda->sidedist_x = 0;
	dda->sidedist_y = 0;
	dda->deltadist_x = 0;
	dda->deltadist_y = 0;
	dda->step_x = 0;
	dda->step_y = 0;
	dda->side = 0;
	dda->perp_wall_dist = 0;
}

// void	show_dda_data(t_dda_data *d)
// {
// 	printf(CYAN "\n========== DDA DATA ==========\n" RESET);
// 	// Ray direction
// 	printf(BLUE "--- Ray Direction ---\n" RESET);
// 	printf(BLUE "raydir_x        : %f\n" RESET, d->raydir_x);
// 	printf(BLUE "raydir_y        : %f\n" RESET, d->raydir_y);
// 	// Map position
// 	printf(GREEN "\n--- Map Position ---\n" RESET);
// 	printf(GREEN "mapX           : %d\n" RESET, d->mapX);
// 	printf(GREEN "mapY           : %d\n" RESET, d->mapY);
// 	// Distances
// 	printf(YELLOW "\n--- Distances ---\n" RESET);
// 	printf(YELLOW "sideDistX      : %f\n" RESET, d->sideDistX);
// 	printf(YELLOW "sideDistY      : %f\n" RESET, d->sideDistY);
// 	printf(YELLOW "deltaDistX     : %f\n" RESET, d->deltaDistX);
// 	printf(YELLOW "deltaDistY     : %f\n" RESET, d->deltaDistY);
// 	// Steps
// 	printf(MAGENTA "\n--- Steps ---\n" RESET);
// 	printf(MAGENTA "step_x          : %d\n" RESET, d->step_x);
// 	printf(MAGENTA "stepY          : %d\n" RESET, d->stepY);
// 	// Result
// 	printf(RED "\n--- Result ---\n" RESET);
// 	printf(RED "side           : %d (%s)\n" RESET,
// 		d->side, d->side == 0 ? "X wall" : "Y wall");
// 	printf(RED "perpWallDist   : %f\n" RESET, d->perpWallDist);
// 	printf(CYAN "==============================\n\n" RESET);
// }

void	init_ray(t_data *data, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)data->width - 1;
	data->dda.raydir_x = data->player.dir_x
		+ data->player.plane_x * camera_x;
	data->dda.raydir_y = data->player.dir_y
		+ data->player.plane_y * camera_x;
	data->dda.map_x = (int)data->player.x;
	data->dda.map_y = (int)data->player.y;
	if (data->dda.raydir_x == 0)
		data->dda.deltadist_x = 1e30;
	else
		data->dda.deltadist_x = fabs(1 / data->dda.raydir_x);
	if (data->dda.raydir_y == 0)
		data->dda.deltadist_y = 1e30;
	else
		data->dda.deltadist_y = fabs(1 / data->dda.raydir_y);
}

void	init_step_and_side(t_data *data)
{
	if (data->dda.raydir_x < 0)
	{
		data->dda.step_x = -1;
		data->dda.sidedist_x = (data->player.x - data->dda.map_x)
			* data->dda.deltadist_x;
	}
	else
	{
		data->dda.step_x = 1;
		data->dda.sidedist_x = (data->dda.map_x + 1.0 - data->player.x)
			* data->dda.deltadist_x;
	}
	if (data->dda.raydir_y < 0)
	{
		data->dda.step_y = -1;
		data->dda.sidedist_y = (data->player.y - data->dda.map_y)
			* data->dda.deltadist_y;
	}
	else
	{
		data->dda.step_y = 1;
		data->dda.sidedist_y = (data->dda.map_y + 1.0 - data->player.y)
			* data->dda.deltadist_y;
	}
}

void	perform_dda(t_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->dda.sidedist_x < data->dda.sidedist_y)
		{
			data->dda.sidedist_x += data->dda.deltadist_x;
			data->dda.map_x += data->dda.step_x;
			data->dda.side = 0;
		}
		else
		{
			data->dda.sidedist_y += data->dda.deltadist_y;
			data->dda.map_y += data->dda.step_y;
			data->dda.side = 1;
		}
		if (data->map->map[data->dda.map_y][data->dda.map_x] > '0')
			hit = 1;
	}
}

void	compute_projection(t_data *data)
{
	if (data->dda.side == 0)
		data->dda.perp_wall_dist = data->dda.sidedist_x - data->dda.deltadist_x;
	else
		data->dda.perp_wall_dist = data->dda.sidedist_y - data->dda.deltadist_y;
	data->dda.line_height = (int)(data->height / data->dda.perp_wall_dist);
	data->dda.draw_start = -data->dda.line_height / 2 + data->height / 2;
	data->dda.draw_end = data->dda.line_height / 2 + data->height / 2;
	if (data->dda.draw_start < 0)
		data->dda.draw_start = 0;
	if (data->dda.draw_end >= data->height)
		data->dda.draw_end = data->height - 1;
}

// void	raycast_dda(t_data *data)
// {
// 	int		i;
// 	double	camera_x;
// 	int		hit;
//
// 	i = -1;
// 	while (++i < data->map->m_width)
// 	{
// 		reset_dda_data(&data->dda);
// 		hit = 0;
// 		camera_x = 2 * i / (double)data->map->m_width - 1;
// 		data->dda.raydir_x = data->player.dir_x + data->player.plane_x
// 			* camera_x;
// 		data->dda.raydir_y = data->player.dir_y + data->player.plane_y
// 			* camera_x;
// 		data->dda.mapX = (int)data->player.x;
// 		data->dda.mapY = (int)data->player.y;
// 		data->dda.deltaDistX = (data->dda.raydir_x == 0) ? 1e30: 
//fabs(1 / data->dda.raydir_x);
// 		data->dda.deltaDistY = (data->dda.raydir_y == 0) ? 1e30 : 
//fabs(1 / data->dda.raydir_y);
// 		if (data->dda.raydir_x < 0)
// 		{
// 			data->dda.step_x = -1;
// 			data->dda.sideDistX = (data->player.x - data->dda.mapX)
// 				* data->dda.deltaDistX;
// 		}
// 		else
// 		{
// 			data->dda.step_x = 1;
// 			data->dda.sideDistX = (data->dda.mapX + 1.0 - data->player.x)
// 				* data->dda.deltaDistX;
// 		}
// 		if (data->dda.raydir_y < 0)
// 		{
// 			data->dda.stepY = -1;
// 			data->dda.sideDistY = (data->player.y - data->dda.mapY)
// 				* data->dda.deltaDistY;
// 		}
// 		else
// 		{
// 			data->dda.stepY = 1;
// 			data->dda.sideDistY = (data->dda.mapY + 1.0 - data->player.y)
// 				* data->dda.deltaDistY;
// 		}
// 		while (hit == 0)
// 		{
// 			if (data->dda.sideDistX < data->dda.sideDistY)
// 			{
// 				data->dda.sideDistX += data->dda.deltaDistX;
// 				data->dda.mapX += data->dda.step_x;
// 				data->dda.side = 0;
// 			}
// 			else
// 			{
// 				data->dda.sideDistY += data->dda.deltaDistY;
// 				data->dda.mapY += data->dda.stepY;
// 				data->dda.side = 1;
// 			}
// 			if (data->map->map[data->dda.mapY][data->dda.mapX] > '0')
// 				hit = 1;
// 		}
// 		if (data->dda.side == 0)
// 		{
// 			data->dda.perpWallDist = data->dda.sideDistX - data->dda.deltaDistX;
// 		}
// 		else
// 		{
// 			data->dda.perpWallDist = data->dda.sideDistY - data->dda.deltaDistY;
// 		}
// 		// if (DEBUG_MODE)
// 		// 	show_dda_data(&data->dda);
// 		data->dda.line_height = (int)(data->height / data->dda.perpWallDist);
// 		data->dda.draw_start = -data->dda.line_height / 2 + data->height / 2;
// 		data->dda.draw_end = data->dda.line_height / 2 + data->height / 2;
// 	}
// }

// void	dda_loop(int hit, t_data *data)
// {
// 	while (hit == 0)
// 	{
// 		if (data->dda.sideDistX < data->dda.sideDistY)
// 		{
// 			data->dda.sideDistX += data->dda.deltaDistX;
// 			data->dda.mapX += data->dda.step_x;
// 			data->dda.side = 0;
// 		}
// 		else
// 		{
// 			data->dda.sideDistY += data->dda.deltaDistY;
// 			data->dda.mapY += data->dda.stepY;
// 			data->dda.side = 1;
// 		}
// 		if (data->map->map[data->dda.mapY][data->dda.mapX] > '0')
// 			hit = 1;
// 	}
// }

// void	calc_ray_column_x(t_data *data, int x)
// {
// 	double	camera_x;
//
// 	camera_x = 2 * x / (double)data->width - 1;
// 	data->dda.raydir_x = data->player.dir_x + data->player.plane_x 
//* camera_x;
// 	data->dda.raydir_y = data->player.dir_y + data->player.plane_y 
//* camera_x;
// 	data->dda.mapX = (int)data->player.x;
// 	data->dda.mapY = (int)data->player.y;
// 	data->dda.deltaDistX = (data->dda.raydir_x == 0) ? 1e30 : 
//fabs(1 / data->dda.raydir_x);
// 	data->dda.deltaDistY = (data->dda.raydir_y == 0) ? 1e30 : 
//fabs(1 / data->dda.raydir_y);
// 	if (data->dda.raydir_x < 0)
// 	{
// 		data->dda.step_x = -1;
// 		data->dda.sideDistX = (data->player.x - data->dda.mapX)
// 			* data->dda.deltaDistX;
// 	}
// 	else
// 	{
// 		data->dda.step_x = 1;
// 		data->dda.sideDistX = (data->dda.mapX + 1.0 - data->player.x)
// 			* data->dda.deltaDistX;
// 	}
// 	if (data->dda.raydir_y < 0)
// 	{
// 		data->dda.stepY = -1;
// 		data->dda.sideDistY = (data->player.y - data->dda.mapY)
// 			* data->dda.deltaDistY;
// 	}
// 	else
// 	{
// 		data->dda.stepY = 1;
// 		data->dda.sideDistY = (data->dda.mapY + 1.0 - data->player.y)
// 			* data->dda.deltaDistY;
// 	}
// }

// void	raycast_single_column(t_data *data, int x)
// {
// 	int		hit;
//
// 	reset_dda_data(&data->dda);
// 	hit = 0;
// 	calc_ray_column_x(data, x);
// 	dda_loop(hit, data);
// 	// Calcular distancia perpendicular
// 	if (data->dda.side == 0)
// 		data->dda.perpWallDist = data->dda.sideDistX - data->dda.deltaDistX;
// 	else
// 		data->dda.perpWallDist = data->dda.sideDistY - data->dda.deltaDistY;
// 	// Calcular altura de línea y límites de dibujo
// 	data->dda.line_height = (int)(data->height / data->dda.perpWallDist);
// 	data->dda.draw_start = -data->dda.line_height / 2 + data->height / 2;
// 	data->dda.draw_end = data->dda.line_height / 2 + data->height / 2;
// 	// Clipping
// 	if (data->dda.draw_start < 0)
// 		data->dda.draw_start = 0;
// 	if (data->dda.draw_end >= data->height)
// 		data->dda.draw_end = data->height - 1;
// }
