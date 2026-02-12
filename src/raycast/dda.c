/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:05:12 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/12 12:06:51 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


static void reset_dda_data (t_dda_data *dda)
{
    dda->rayDirX = 0;
	dda->rayDirY = 0;
	dda->mapX = 0;
	dda->mapY = 0;
	dda->sideDistX = 0;
	dda->sideDistY = 0;
	dda->deltaDistX = 0;
	dda->deltaDistY = 0;
	dda->stepX = 0;
	dda->stepY = 0;
	dda->side = 0;
	dda->perpWallDist = 0;
}

// void	show_dda_data(t_dda_data *d)
// {
// 	printf(CYAN "\n========== DDA DATA ==========\n" RESET);

// 	// Ray direction
// 	printf(BLUE "--- Ray Direction ---\n" RESET);
// 	printf(BLUE "rayDirX        : %f\n" RESET, d->rayDirX);
// 	printf(BLUE "rayDirY        : %f\n" RESET, d->rayDirY);

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
// 	printf(MAGENTA "stepX          : %d\n" RESET, d->stepX);
// 	printf(MAGENTA "stepY          : %d\n" RESET, d->stepY);

// 	// Result
// 	printf(RED "\n--- Result ---\n" RESET);
// 	printf(RED "side           : %d (%s)\n" RESET,
// 		d->side, d->side == 0 ? "X wall" : "Y wall");
// 	printf(RED "perpWallDist   : %f\n" RESET, d->perpWallDist);

// 	printf(CYAN "==============================\n\n" RESET);
// }


void    raycast_dda(t_data *data) 
{
    int     i;
    double  cameraX;
    int     hit;

    i = -1;
    
    while (++i < data->map->m_width)
    {
        reset_dda_data(&data->dda);
        hit = 0;

        cameraX = 2 * i / (double)data->map->m_width - 1;
        data->dda.rayDirX = data->player.dir_x + data->player.plane_x * cameraX;
        data->dda.rayDirY = data->player.dir_y + data->player.plane_y * cameraX;

        data->dda.mapX = (int)data->player.x;
        data->dda.mapY = (int)data->player.y;
        
        data->dda.deltaDistX = (data->dda.rayDirX == 0) ? 1e30 : fabs(1 / data->dda.rayDirX);
        data->dda.deltaDistY = (data->dda.rayDirY == 0) ? 1e30 : fabs(1 / data->dda.rayDirY);

        if (data->dda.rayDirX < 0)
        {
            data->dda.stepX = -1;
            data->dda.sideDistX = (data->player.x - data->dda.mapX) * data->dda.deltaDistX;
        }
        else
        {
            data->dda.stepX = 1;
            data->dda.sideDistX = (data->dda.mapX + 1.0 - data->player.x) * data->dda.deltaDistX;
        }

        if (data->dda.rayDirY < 0)
        {
            data->dda.stepY = -1;
            data->dda.sideDistY = (data->player.y - data->dda.mapY) * data->dda.deltaDistY;
        }
        else
        {
            data->dda.stepY = 1;
            data->dda.sideDistY = (data->dda.mapY + 1.0 - data->player.y) * data->dda.deltaDistY;
        }
            
        while (hit == 0)
        {
            if (data->dda.sideDistX < data->dda.sideDistY)
            {
                data->dda.sideDistX += data->dda.deltaDistX;
                data->dda.mapX += data->dda.stepX;
                data->dda.side = 0;
            }
            else
            {
                data->dda.sideDistY += data->dda.deltaDistY;
                data->dda.mapY += data->dda.stepY;
                data->dda.side = 1;
            }
            if (data->map->map[data->dda.mapY][data->dda.mapX] > '0')
                hit = 1;
        }

        if (data->dda.side == 0)
        {
            data->dda.perpWallDist = data->dda.sideDistX - data->dda.deltaDistX;
        }
        else
        {
            data->dda.perpWallDist = data->dda.sideDistY - data->dda.deltaDistY;
        }
        //show_dda_data(&data->dda);
    }
}

