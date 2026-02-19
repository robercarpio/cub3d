/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarpio-mamaratr <rcarpio-mamaratr@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:44:11 by mamaratr          #+#    #+#             */
/*   Updated: 2026/02/19 13:42:50 by rcarpio-mam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int    mouse_move(int x, int y, t_data *data)
{
    int     delta_x;
    int     center_x;

	(void)y;
    center_x = SCREEN_WIDTH / 2;
    // Evita recursión infinita cuando recentramos el cursor
    if (x == center_x)
        return (0);
    delta_x = x - center_x;
    rotate_player(data, delta_x * 0.0001);
    mlx_mouse_move(data->mlx, data->win, center_x, SCREEN_HEIGHT / 2);
    return (0);
}

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
	ft_render_frame(data);
	return (0);
}

static void    start_window(t_data *data)
{
    data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
    data->img.img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
            &data->img.line_length, &data->img.endian);
    mlx_hook(data->win, 2, 1L << 0, key_press, data);
    mlx_hook(data->win, 3, 1L << 1, key_release, data);
    mlx_hook(data->win, 6, 1L << 6, mouse_move, data);   // <- nuevo
    mlx_hook(data->win, 17, 0, ft_exit, data);
    mlx_loop_hook(data->mlx, game_loop, data);
    mlx_mouse_move(data->mlx, data->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    mlx_loop(data->mlx);
}

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
	init_textures(file, data);
	parse_textures(file, data);
	load_textures(data);
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (0);
	*data->map = init_map(file);
	init_player(data);
	start_window(data);
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
