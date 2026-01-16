/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:03:07 by rcarpio-cye       #+#    #+#             */
/*   Updated: 2026/01/15 14:43:55 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	*dup_line(char *s)
{
	char	*str;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] != '\0')
		len++;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	files_map(char *route)
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
	}
	close(fd);
	return (rows);
}

static char	**allocate_map(char *route)
{
	int		fd;
	char	*line;
	int		height;
	char	**map;
	int		i;

	fd = open(route, O_RDONLY);
	if (fd == -1)
		return (perror("Error al abrir el archivo"), NULL);
	height = files_map(route);
	map = (char **)malloc((height + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map[i] = dup_line(line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	play (char *route)
{
	char	**map;

	map = allocate_map(route);
	if (!map)
		return (0);
	if (parse(map))
	{
		printf("Mapa cargado y validado correctamente.\n");
	}
	// else
	// {
	// 	printf("Error: Mapa inválido.\n");
	// }
	return (0);
}