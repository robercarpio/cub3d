/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:56:39 by rcarpio-mam       #+#    #+#             */
/*   Updated: 2026/02/17 10:43:48 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"

# include <fcntl.h>
# include <sys/time.h>
# include <math.h>


#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_WHITE   "\033[1;37m"


//COLORES
#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"

# define DEBUG_MODE 1
# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 800
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MINIMAP_SIZE 200
# define MINIMAP_TILES 10
# define MINIMAP_TILE_SIZE (MINIMAP_SIZE / MINIMAP_TILES)
# define MINIMAP_X 20
# define MINIMAP_Y 20
# define TILE_SIZE 32
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
# define MOVE_SPEED 0.01
# define ROT_SPEED 0.01
# define PLAYER_RADIUS 0.01

typedef struct s_stripe
{
	unsigned int	*frame;
	unsigned int	*tex_pixels;
	int				tex_pitch;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	int				y;
}	t_stripe;

typedef enum e_tex_id
{
	TEX_NORTH = 0,
	TEX_SOUTH,
	TEX_WEST,
	TEX_EAST,
	TEX_COUNT
}	t_tex_id;

typedef struct s_dda_data
{
	double	rayDirX;      // Dirección X del rayo individual (dir + plano * cameraX).
	double	rayDirY;      // Dirección Y del rayo individual.
	int		mapX;         // Coordenada X entera de la celda actual en el mapa.
	int		mapY;         // Coordenada Y entera de la celda actual en el mapa.
	double	sideDistX;    // Distancia acumulada hasta el próximo borde vertical (X).
	double	sideDistY;    // Distancia acumulada hasta el próximo borde horizontal (Y).
	double	deltaDistX;   // Distancia que el rayo debe recorrer para cruzar una celda en X.
	double	deltaDistY;   // Distancia que el rayo debe recorrer para cruzar una celda en Y.
	int		stepX;        // Dirección del salto en el mapa (-1 o 1) para el eje X.
	int		stepY;        // Dirección del salto en el mapa (-1 o 1) para el eje Y.
	int		side;         // Indica si se chocó con un muro en X (0) o en Y (1).
	double	perpWallDist; // Distancia final proyectada para evitar el efecto ojo de pez.
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_dda_data;

typedef	struct	s_coords
{
	int	x;
	int	y;
}	t_coords;

typedef struct s_img
{
	void	*img;
	void	*frame;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_texture
{
	char	*paths[TEX_COUNT];
	t_img	images[TEX_COUNT];
	char	*celling;
	char	*floor;
}	t_texture;

typedef struct s_map
{
	char			**map;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
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
	t_img		img;
	t_img		bgnd;
	t_texture	textures;
	t_dda_data	dda;
}	t_data;

#endif