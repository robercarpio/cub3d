/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:23:35 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/03 16:39:43 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == 'P')
			{
				data->player.x = x + 0.5;
				data->player.y = y + 0.5;
				data->player.dir_x = 0.0;
				data->player.dir_y = -1.0;
				data->player.plane_x = 0.0;
				data->player.plane_y = 0.66;
				data->map->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

void	move_forward(t_data *data, int dir)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + data->player.dir_x * MOVE_SPEED * dir;
	new_y = data->player.y + data->player.dir_y * MOVE_SPEED * dir;
	
	if (data->map->map[(int)data->player.y][(int)new_x] == '0')
		data->player.x = new_x;
	if (data->map->map[(int)new_y][(int)data->player.x] == '0')
		data->player.y = new_y;
}

void	move_strafe(t_data *data, int dir)
{
	double	new_x;
	double	new_y;
	double	perp_dir_x;
	double	perp_dir_y;

	perp_dir_x = -data->player.dir_y;
	perp_dir_y = data->player.dir_x;
	new_x = data->player.x + perp_dir_x * MOVE_SPEED * dir;
	new_y = data->player.y + perp_dir_y * MOVE_SPEED * dir;
	
	if (data->map->map[(int)data->player.y][(int)new_x] == '0')
		data->player.x = new_x;
	if (data->map->map[(int)new_y][(int)data->player.x] == '0')
		data->player.y = new_y;
}

void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(angle);
	sin_angle = sin(angle);
	
	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	
	data->player.dir_x = data->player.dir_x * cos_angle
		- data->player.dir_y * sin_angle;
	data->player.dir_y = old_dir_x * sin_angle
		+ data->player.dir_y * cos_angle;
	data->player.plane_x = data->player.plane_x * cos_angle
		- data->player.plane_y * sin_angle;
	data->player.plane_y = old_plane_x * sin_angle
		+ data->player.plane_y * cos_angle;	
	if (DEBUG_MODE)
	{
		printf("PLAYER DIR X :%f \n", data->player.dir_x);
		printf("PLAYER DIR Y :%f \n", data->player.dir_y);
		printf("----------------------------------------------------------------------------------------------------------------------\n");
	}
}
