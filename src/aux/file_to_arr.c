/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:27:41 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/03/30 01:32:00 by rcarpio-mam      ###   ########.fr       */
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
		rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (rows);
}

char	**file_to_arr(char *route)
{
	int		height;
	int		i;
	char	**arr;
	int		fd;

	height = file_height(route);
	if (height <= 0)
		return (NULL);
	arr = (char **)malloc((height + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	fd = open(route, O_RDONLY);
	if (fd == -1)
		return (free(arr), NULL);
	i = 0;
	while (i < height)
	{
		arr[i] = get_next_line(fd);
		if (!arr[i])
			break ;
		i++;
	}
	arr[i] = NULL;
	close(fd);
	return (arr);
}
