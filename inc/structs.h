/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:56:39 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/01/16 14:42:22 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"

# include <fcntl.h>
# include <sys/time.h>
# include <math.h>

# define MAX_KEYCODE 65536
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define UP 1
# define DOWN -1
# define LEFT -1
# define RIGHT 1

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*celling;
	char	*floor;
}	t_texture;

typedef struct s_map
{
	char			**map;
	int				m_width;
	int				m_height;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			*keys;
	int			width;
	int			height;
	t_map		*map;
	t_player	player;
	t_texture	textures;
}	t_data;


int	ft_exit(t_data *data);
int	key_press(int key, t_data *data);
int	key_release(int key, t_data *data);

#endif