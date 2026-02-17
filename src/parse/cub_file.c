/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:43 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/01/16 12:15:59 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	cub_file(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	return ((ft_strcmp(str + len - 4, ".cub") == 0) && len > 4);
}