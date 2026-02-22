/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 08:58:17 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/22 09:01:50 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	run_dda_pipeline(t_data *data, int x)
{
	reset_dda_data(&data->dda);
	init_ray(data, x);
	init_step_and_side(data);
	perform_dda(data);
	compute_projection(data);
}

void	raycast_single_column(t_data *data, int x)
{
	run_dda_pipeline(data, x);
}

void	raycast_dda(t_data *data)
{
	int	x;

	x = -1;
	while (++x < data->map->m_width)
		run_dda_pipeline(data, x);
}
