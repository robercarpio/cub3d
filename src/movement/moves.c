/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 09:54:08 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/22 09:56:02 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	is_walkable(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= data->map->m_height)
		return (0);
	if (!data->map->map[map_y])
		return (0);
	if (map_x < 0 || map_x >= (int)ft_strlen(data->map->map[map_y]))
		return (0);
	if (data->map->map[map_y][map_x] == '1')
		return (0);
	return (1);
}

static void	move_player(t_data *data, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	double	r;

	new_x = data->player.x + move_x;
	new_y = data->player.y + move_y;
	r = PLAYER_RADIUS;
	if (is_walkable(data, new_x - r, data->player.y - r)
		&& is_walkable(data, new_x + r, data->player.y - r)
		&& is_walkable(data, new_x - r, data->player.y + r)
		&& is_walkable(data, new_x + r, data->player.y + r))
	{
		data->player.x = new_x;
	}
	if (is_walkable(data, data->player.x - r, new_y - r)
		&& is_walkable(data, data->player.x + r, new_y - r)
		&& is_walkable(data, data->player.x - r, new_y + r)
		&& is_walkable(data, data->player.x + r, new_y + r))
	{
		data->player.y = new_y;
	}
}

void	move_forward(t_data *data, int dir)
{
	move_player(data,
		data->player.dir_x * MOVE_SPEED * dir,
		data->player.dir_y * MOVE_SPEED * dir);
}

void	move_strafe(t_data *data, int dir)
{
	double	perp_x;
	double	perp_y;

	perp_x = -data->player.dir_y;
	perp_y = data->player.dir_x;
	move_player(data,
		perp_x * MOVE_SPEED * dir,
		perp_y * MOVE_SPEED * dir);
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
		printf("-----------------------------------------\n");
	}
}
