/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:44:11 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/17 09:33:01 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_exit(t_data *data)
{
	if (data)
	{
		if (data->mlx && data->win)
			mlx_destroy_window(data->mlx, data->win);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

int	ft_alloc_data(t_data *data, t_map *map)
{
	ft_bzero(data, sizeof(t_data));
	ft_bzero(map, sizeof(t_map));
	data->map = map;
	return (1);
}


void	draw_texture_debug(t_data *data, t_img *tex, int off_x, int off_y)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < tex->height && y + off_y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < tex->width && x + off_x < SCREEN_WIDTH)
		{
			color = *(unsigned int *)(tex->addr
				+ (y * tex->line_length)
				+ (x * (tex->bpp / 8)));
			my_mlx_pixel_put(&data->img, x + off_x, y + off_y, color);
			x++;
		}
		y++;
	}
}

// int	game_loop(t_data *data)
// {
// 	if (data->keys[W])
// 		move_forward(data, UP);
// 	if (data->keys[S])
// 		move_forward(data, DOWN);
// 	if (data->keys[A])
// 		move_strafe(data, LEFT);
// 	if (data->keys[D])
// 		move_strafe(data, RIGHT);
// 	if (data->keys[KEY_LEFT])
// 		rotate_player(data, -ROT_SPEED);
// 	if (data->keys[KEY_RIGHT])
// 		rotate_player(data, ROT_SPEED);

// 	clear_image(data);
	
// 	draw_texture_debug(data, &data->textures.images[TEX_NORTH], 0, 0);
// 	draw_texture_debug(data, &data->textures.images[TEX_SOUTH], 300, 0);
// 	draw_texture_debug(data, &data->textures.images[TEX_EAST], 500, 0);
// 	draw_texture_debug(data, &data->textures.images[TEX_WEST], 700, 0);
	
// 	// printf("1 in call game loop\n");
// 	draw_map(data);
// 	// printf("2 in call game loop\n");
// 	draw_player(data);
// 	// printf("3 in call game loop\n");
// 	draw_ray(data);
// 	printf("4 in call game loop\n");
// 	ft_render_frame(data);
// 	printf("5 in call game loop\n");
// 	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
// 	printf("6 in call game loop\n");
// 	return (0);
// }

int	game_loop(t_data *data)
{
	if (data->keys[W])
		move_forward(data, UP);
	if (data->keys[S])
		move_forward(data, DOWN);
	if (data->keys[A])
		move_strafe(data, LEFT);
	if (data->keys[D])
		move_strafe(data, RIGHT);
	if (data->keys[KEY_LEFT])
		rotate_player(data, -ROT_SPEED);
	if (data->keys[KEY_RIGHT])
		rotate_player(data, ROT_SPEED);

	clear_image(data);
	
	draw_texture_debug(data, &data->textures.images[TEX_NORTH], 0, 0);
	draw_texture_debug(data, &data->textures.images[TEX_SOUTH], 300, 0);
	draw_texture_debug(data, &data->textures.images[TEX_EAST], 500, 0);
	draw_texture_debug(data, &data->textures.images[TEX_WEST], 700, 0);
	
	draw_map(data);
	draw_player(data);
	draw_ray(data);
	
	printf("4 in call game loop\n");
	ft_render_frame(data);  // Ya llama a mlx_put_image_to_window internamente
	printf("5 in call game loop\n");
	
	// ELIMINAR ESTA LÍNEA - duplicada
	// mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	
	printf("6 in call game loop\n");
	return (0);
}

// static void	start_window(t_data data)
// {
// 	data.win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
// 	data.img.img = mlx_new_image(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
// 	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp,
// 			&data.img.line_length, &data.img.endian);
// 	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
// 	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
// 	mlx_hook(data.win, 17, 0, ft_exit, &data);
// 	mlx_loop_hook(data.mlx, game_loop, &data);
// 	printf("8 in call start window\n");
// 	mlx_loop(data.mlx);
// 	printf("9 in call start window\n");
// }

static void	fill_background(t_data *data)
{
	int				x;
	int				y;
	unsigned int	*bg;
	unsigned int	ceiling_color;
	unsigned int	floor_color;

	// TODO: Obtener estos colores de tu parser (data->textures.ceiling_color, etc.)
	ceiling_color = 0x87CEEB;  // Azul cielo (ejemplo)
	floor_color = 0x8B7355;    // Marrón suelo (ejemplo)
	
	bg = (unsigned int *)data->bgnd.addr;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (y < data->height / 2)
				bg[y * data->width + x] = ceiling_color;
			else
				bg[y * data->width + x] = floor_color;
			x++;
		}
		y++;
	}
}

static void	start_window(t_data *data)  // <-- Cambiar a puntero
{
	// Crear ventana
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
	
	// Inicializar imagen principal
	data->img.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_length, &data->img.endian);
	
	// AÑADIR: Inicializar background (cielo/suelo)
	data->bgnd.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->bgnd.addr = mlx_get_data_addr(data->bgnd.img, &data->bgnd.bpp,
			&data->bgnd.line_length, &data->bgnd.endian);
	
	// TODO: Aquí deberías rellenar data->bgnd.addr con los colores de cielo/suelo
	// Por ejemplo, mitad superior con color de cielo, mitad inferior con color de suelo
	fill_background(data);  // <-- Necesitarás crear esta función
	
	// Hooks
	mlx_hook(data->win, 2, 1L << 0, key_press, data);  // <-- Cambiar &data a data
	mlx_hook(data->win, 3, 1L << 1, key_release, data);  // <-- Cambiar &data a data
	mlx_hook(data->win, 17, 0, ft_exit, data);  // <-- Cambiar &data a data
	mlx_loop_hook(data->mlx, game_loop, data);  // <-- Cambiar &data a data
	
	printf("8 in call start window\n");
	mlx_loop(data->mlx);
	printf("9 in call start window\n");
}

// int	ft_init(t_data *data, char *route)
// {
// 	char	**file;

// 	data->mlx = mlx_init();
// 	if (!data->mlx)
// 		return (0);
// 	data->keys = ft_calloc(MAX_KEYCODE, sizeof(int));
// 	if (!data->keys)
// 		return (0);
// 	file = file_to_arr(route);
// 	// printf("pre call init textures\n");
// 	init_textures(&data->textures);
// 	// printf("post call init textures\n");
// 	// printf("pre call parse textures\n");
// 	parse_textures(file, &data->textures);
// 	// printf("post call init textures\n");a
// 	// printf("pre call load textures\n");
// 	load_textures(data, &data->textures);
// 	// printf("post call load textures\n");
// 	//MAP
// 	// printf("pre call init map\n");
// 	*data->map = init_map(file);
// 	// printf("post call init map\n");
// 	//PLAYER
// 	// printf("pre call init player\n");
// 	init_player(data);
// 	// printf("post call init player\n");
// 	//DDA
// 	raycast_dda(data);
// 	// printf("pre call start window\n");
// 	start_window(*data);
// 	// printf("post call start window\n");
// 	//MLX
// 	return (1);
// }

int	ft_init(t_data *data, char *route)
{
	char	**file;

	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->width = SCREEN_WIDTH;
	data->height = SCREEN_HEIGHT;		
	data->keys = ft_calloc(MAX_KEYCODE, sizeof(int));
	if (!data->keys)
		return (0);
	file = file_to_arr(route);
	init_textures(&data->textures);
	parse_textures(file, &data->textures);
	load_textures(data, &data->textures);
	*data->map = init_map(file);
	init_player(data);
	// raycast_dda(data);
	
	// CAMBIO: Pasar por PUNTERO, no por valor
	start_window(data);  // <-- Quitar el asterisco
	
	return (1);
}

int	main(int argc, char *argv[])
{
	if (argc == 2)
		play(argv[1]);
	else
		printf("Error!\nInvalid map file\nUsage: ./cub3d <map.cub>\n");
	return (0);
}