/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:05:12 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/26 12:21:09 by mamaratr         ###   ########.fr       */
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
		if (data->map->map[data->dda.map_y][data->dda.map_x] == '1' ||
			data->map->map[data->dda.map_y][data->dda.map_x] == 'D')
			hit = 1;
	}
	data->dda.hit_type = data->map->map[data->dda.map_y][data->dda.map_x];
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
