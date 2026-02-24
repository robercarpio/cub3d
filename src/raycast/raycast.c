/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 08:58:17 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/23 10:30:24 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	raycast_single_column(t_data *data, int x)
{
	reset_dda_data(&data->dda);
	init_ray(data, x);
	init_step_and_side(data);
	perform_dda(data);
	compute_projection(data);
}

void	raycast_dda(t_data *data)
{
	int	x;

	x = -1;
	while (++x < data->map->m_width)
		raycast_single_column(data, x);
}
