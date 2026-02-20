/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-cyepes <rcarpio-cyepes@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:49:21 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/20 16:43:04 by rcarpio-cye      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		ft_exit(data);
	if (key == TAB_KEY)
		data->show_bigmap = !data->show_bigmap;
	if (key == KEY_E)
		try_open_door(data);
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
