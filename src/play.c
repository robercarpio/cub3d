/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:03:07 by rcarpio-cye       #+#    #+#             */
/*   Updated: 2026/01/20 17:56:46 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// static char	*dup_line(char *s)
// {
// 	char	*str;
// 	int		i;
// 	int		len;

// 	if (!s)
// 		return (NULL);
// 	len = 0;
// 	while (s[len] != '\0')
// 		len++;
// 	str = malloc(len + 1);
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		str[i] = s[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// static int	files_map(char *route)
// {
// 	int		fd;
// 	char	*line;
// 	int		rows;

// 	rows = 0;
// 	fd = open(route, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error al abrir el archivo");
// 		return (-1);
// 	}
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		if (line[0] != '\0')
// 		{
// 			rows++;
// 			free (line);
// 			line = get_next_line(fd);
// 		}
// 	}
// 	close(fd);
// 	return (rows);
// }

// static char	**allocate_file(char *route)
// {
// 	int		fd;
// 	char	*line;
// 	int		height;
// 	char	**map;
// 	int		i;

// 	fd = open(route, O_RDONLY);
// 	if (fd == -1)
// 		return (perror("Error al abrir el archivo"), NULL);
// 	height = files_map(route);
// 	map = (char **)malloc((height + 1) * sizeof(char *));
// 	if (!map)
// 		return (NULL);
// 	i = 0;
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		map[i] = dup_line(line);
// 		i++;
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	map[i] = NULL;
// 	close(fd);
// 	return (map);
// }

static void print_map(t_map map)
{
	int i;
	
	i = 0;
	while (map.map[i])
	{
		printf("%s", map.map[i]);
		i++;
	}
}

int	play (char *route)
{
	char	**arr;

	arr = file_to_arr(route);
	if (!arr)
		return (0);
	t_map map = init_map(arr);
	print_map(map);
	// print_map(map);
	// printf("\n");
	// printf("HEIGHT %d \n",map.m_height);
	// printf("WIDTH %d \n",map.m_width);
	return (1);	
}
