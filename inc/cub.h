/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:44:59 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/17 09:26:45 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "structs.h"
# include "../mlx/mlx.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>


int	ft_init(t_data *data , char *route);
void	play (char *route);
void	print_arr(char **arr);
void    print_map(t_map map);

//GNL
char	*get_next_line(int fd);
int		ft_indexof(char *str, char c);
char	*ft_aux(char **stg);
char	*fbreturn(char *buffer, int rd, char **stg);

//PARSE
int		only_chars_allow(char *str, char *allow);
int		check_chars(char **map);
int	    parse(t_data data);
int     cub_file(char *str);
char	**expand_map(t_map map);
int     closed_map(t_data data);

//PROCESS MAP
int	get_texture_id(char *str);
//int  is_texture(char *str);
void	skip_textures(char	***file);
t_map   init_map(char **file);
//t_texture init_textures(char **file);

//AUX
int     map_height(char **map);
int     map_width (char **map);
int	    file_height(char *route);
char    **file_to_arr(char *route);
char    **allocate_map(char **map);
char *fill_str(char c, int width);
int line_len(char *str);

//INPUTS
int	ft_exit(t_data *data);
int	key_press(int key, t_data *data);
int	key_release(int key, t_data *data);

//MOVEMENT
void	init_player(t_data *data);
void	move_forward(t_data *data, int dir);
void	move_strafe(t_data *data, int dir);
void	rotate_player(t_data *data, double angle);

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color);
void	draw_square(t_data *data, int start_x, int start_y, int size,  int color);
void	draw_player(t_data *data);
void	draw_ray(t_data *data);
void	draw_map(t_data *data);
void	clear_image(t_data *data);

//RAYCASTING
void    raycast_dda(t_data *data);
void	show_dda_data(t_dda_data *d);
void	raycast_single_column(t_data *data, int x);

//TEXTURES
void	init_textures(t_texture *tex);
void	parse_textures(char **file, t_texture *tex);
void	load_textures(t_data *data, t_texture *tex);

//RENDER
int	ft_render_frame(t_data *data);

int	ft_alloc_data(t_data *data, t_map *map);

#endif