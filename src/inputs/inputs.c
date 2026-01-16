/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:49:21 by mamaratr          #+#    #+#             */
/*   Updated: 2026/01/15 13:04:58 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int	key_press(int key, t_data *data)
{
	if (key == ESC)
		ft_exit(data);
	if (key >= 0 && key < MAX_KEYCODE)
		data->keys[key] = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key >= 0 && key < MAX_KEYCODE)
		data->keys[key] = 0;
	return (0);
}
