/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:44:59 by mamaratr          #+#    #+#             */
/*   Updated: 2026/01/18 14:21:43 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
//
# include "structs.h"
# include "../mlx/mlx.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>



int		play (char *route);

//GNL
char	*get_next_line(int fd);
int		ft_indexof(char *str, char c);
char	*ft_aux(char **stg);
char	*fbreturn(char *buffer, int rd, char **stg);

//PARSE
int		only_chars_allow(char *str, char *allow);
int		check_chars(char **map);
int		parse(char **map);
int     cub_file(char *str);

//PROCESS MAP
t_map   init_map(char **file);

//AUX
int     map_height(char **map);
int	    file_height(char *route);
char    **file_to_arr(char *route);
char    **allocate_map(char **map);

#endif