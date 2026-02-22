/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:49:21 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/22 09:39:40 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		ft_exit(data);
	if (key >= 0 && key < MAX_KEYCODE)
	{
		raycast_dda(data);
		data->keys[key] = 1;
	}
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key >= 0 && key < MAX_KEYCODE)
		data->keys[key] = 0;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	int	delta_x;
	int	center_x;

	(void)y;
	center_x = SCREEN_WIDTH / 2;
	if (x == center_x)
		return (0);
	delta_x = x - center_x;
	rotate_player(data, delta_x * 0.0001);
	mlx_mouse_move(data->mlx, data->win, center_x, SCREEN_HEIGHT / 2);
	return (0);
}
