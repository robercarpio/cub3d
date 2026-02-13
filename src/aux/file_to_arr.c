/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:27:41 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/13 14:17:06 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	file_height(char *route)
{
	int		fd;
	char	*line;
	int		rows;

	rows = 0;
	fd = open(route, O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo");
		return (-1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] != '\0')
		{
			rows++;
			free (line);
			line = get_next_line(fd);
		}
		else
			break;
	}
	close(fd);
	return (rows);
}

char	**file_to_arr(char *route)
{
	int     height;
	int     i;
	char    **arr;
	int     fd;
	
	height = file_height(route);
	arr = (char **)malloc((height + 1) * sizeof(char *));
	if (!arr)
		return(NULL);
	i = -1;
	fd = open(route, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Failed to open the map file.\n");
	}
	//printf("ENTRA WHILE FILE2ARR \n");
	while (++i < height)
	{
		arr[i] = get_next_line(fd);
	}
	arr[height] = NULL;
	close(fd);
	return (arr);
}
