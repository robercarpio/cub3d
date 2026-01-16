/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:31:47 by rcarpio-          #+#    #+#             */
/*   Updated: 2026/01/15 13:11:36 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	int			rd;
	char		*temp ;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	rd = read(fd, buffer, BUFFER_SIZE);
	while (rd > 0)
	{
		buffer[rd] = '\0';
		if (!storage)
			storage = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(storage, buffer);
			free(storage);
			storage = temp;
		}
		if (ft_strchr(storage, '\n'))
			break ;
		rd = read(fd, buffer, BUFFER_SIZE);
	}
	return (fbreturn(buffer, rd, &storage));
}

char	*fbreturn(char *buffer, int rd, char **stg)
{
	free(buffer);
	if (rd < 0 || (!*stg && rd == 0))
		return (NULL);
	return (ft_aux(stg));
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*ptr;
// 	char	*p;
// 	size_t	r_len;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	r_len = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	ptr = malloc(r_len);
// 	if (!ptr)
// 		return (NULL);
// 	p = ptr;
// 	while (*s1)
// 		*p++ = *s1++;
// 	while (*s2)
// 		*p++ = *s2++;
// 	*p = '\0';
// 	return (ptr);
// }

char	*ft_aux(char **stg)
{
	char	*l;
	char	*tmp;
	int		len;

	//if (!*stg || !(ft_strchr(*stg, '\n')) || (**stg == '\n' && !(**stg++)))
	if (!*stg || !(ft_strchr(*stg, '\n')))
	{
		l = ft_strdup(*stg);
		free(*stg);
		*stg = NULL;
		return (l);
	}
	len = ft_indexof(*stg, '\n') + 1;
	l = ft_substr(*stg, 0, len);
	tmp = ft_strdup(*stg + len);
	free(*stg);
	*stg = tmp;
	return (l);
}

// size_t	ft_strlen(char *str)
// {
// 	size_t	i;

// 	if (!str)
// 		return (0);
// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }
// int main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error al abrir el archivo");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);  // Importante: liberar la memoria asignada por get_next_line
// 	}
// 	close(fd);
// 	return (0);
// }
