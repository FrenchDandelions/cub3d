/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:29:16 by thole             #+#    #+#             */
/*   Updated: 2024/05/09 19:51:23 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_cross(t_cub *cub)
{
	free_and_exit(cub);
	return (0);
}

int	handle_key(int code, t_cub *cub)
{
	if (code == XK_Escape)
		free_and_exit(cub);
	if (code == XK_w)
		move_up(cub);
	else if (code == XK_s)
		move_down(cub);
	if (code == XK_a)
		move_left(cub);
	else if (code == XK_d)
		move_right(cub);
	if (code == XK_Right)
	{
		cub->ray.old_dir_x = cub->ray.dir_x;
		cub->ray.dir_x = cub->ray.dir_x * cos(-cub->ray.rot_speed)
			- cub->ray.dir_y * sin(-cub->ray.rot_speed);
		cub->ray.dir_y = cub->ray.old_dir_x * sin(-cub->ray.rot_speed)
			+ cub->ray.dir_y * cos(-cub->ray.rot_speed);
		cub->ray.old_plane_x = cub->ray.plane_x;
		cub->ray.plane_x = cub->ray.plane_x * cos(-cub->ray.rot_speed)
			- cub->ray.plane_y * sin(-cub->ray.rot_speed);
		cub->ray.plane_y = cub->ray.old_plane_x * sin(-cub->ray.rot_speed)
			+ cub->ray.plane_y * cos(-cub->ray.rot_speed);
	}
	else if (code == XK_Left)
	{
		cub->ray.old_dir_x = cub->ray.dir_x;
		cub->ray.dir_x = cub->ray.dir_x * cos(cub->ray.rot_speed)
			- cub->ray.dir_y * sin(cub->ray.rot_speed);
		cub->ray.dir_y = cub->ray.old_dir_x * sin(cub->ray.rot_speed)
			+ cub->ray.dir_y * cos(cub->ray.rot_speed);
		cub->ray.old_plane_x = cub->ray.plane_x;
		cub->ray.plane_x = cub->ray.plane_x * cos(cub->ray.rot_speed)
			- cub->ray.plane_y * sin(cub->ray.rot_speed);
		cub->ray.plane_y = cub->ray.old_plane_x * sin(cub->ray.rot_speed)
			+ cub->ray.plane_y * cos(cub->ray.rot_speed);
	}
	return (0);
}

void	put_ray(t_cub *cub, int color, int color2)
{
	int		y;
	int		x;
	void	*img;
	char	*buffer;

	img = mlx_new_image(cub->mlx_ptr, 12, 50);
	buffer = mlx_get_data_addr(img, &cub->img.pixel_bits, &cub->img.line_bytes,
			&cub->img.endian);
	y = -1;
	while (++y < 25)
	{
		x = -1;
		while (++x < 12)
		{
			cub->img.pixel = (y * cub->img.line_bytes) + (x * 4);
			if (cub->img.endian == 0)
			{
				buffer[cub->img.pixel + 0] = (color)&0xFF;
				buffer[cub->img.pixel + 1] = (color >> 8) & 0xFF;
				buffer[cub->img.pixel + 2] = (color >> 16) & 0xFF;
				buffer[cub->img.pixel + 3] = (color >> 24);
			}
		}
	}
	y--;
	while (++y < 50)
	{
		x = -1;
		while (++x < 12)
		{
			cub->img.pixel = (y * cub->img.line_bytes) + (x * 4);
			if (cub->img.endian == 0)
			{
				buffer[cub->img.pixel + 0] = (color2)&0xFF;
				buffer[cub->img.pixel + 1] = (color2 >> 8) & 0xFF;
				buffer[cub->img.pixel + 2] = (color2 >> 16) & 0xFF;
				buffer[cub->img.pixel + 3] = (color2 >> 24);
			}
		}
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_win, img, MAP_WIDTH / 2,
		MAP_HEIGHT / 2 - 25);
	mlx_destroy_image(cub->mlx_ptr, img);
}

void	get_imgs(t_cub *cub, void *img, int color, int color2)
{
	int	y;
	int	x;

	cub->img.buffer = mlx_get_data_addr(img, &cub->img.pixel_bits,
			&cub->img.line_bytes, &cub->img.endian);
	y = -1;
	while (++y < MAP_HEIGHT / 2)
	{
		x = -1;
		while (++x < MAP_WIDTH)
		{
			cub->img.pixel = (y * cub->img.line_bytes) + (x * 4);
			if (cub->img.endian == 0)
			{
				cub->img.buffer[cub->img.pixel + 0] = (color)&0xFF;
				cub->img.buffer[cub->img.pixel + 1] = (color >> 8) & 0xFF;
				cub->img.buffer[cub->img.pixel + 2] = (color >> 16) & 0xFF;
				cub->img.buffer[cub->img.pixel + 3] = (color >> 24);
			}
		}
	}
	y--;
	while (++y < MAP_HEIGHT)
	{
		x = -1;
		while (++x < MAP_WIDTH)
		{
			cub->img.pixel = (y * cub->img.line_bytes) + (x * 4);
			if (cub->img.endian == 0)
			{
				cub->img.buffer[cub->img.pixel + 0] = (color2)&0xFF;
				cub->img.buffer[cub->img.pixel + 1] = (color2 >> 8) & 0xFF;
				cub->img.buffer[cub->img.pixel + 2] = (color2 >> 16) & 0xFF;
				cub->img.buffer[cub->img.pixel + 3] = (color2 >> 24);
			}
		}
	}
}

void	set_dir(t_cub *cub)
{
	if (cub->pos.orientation == 'W')
	{
		cub->ray.dir_x = 0;
		cub->ray.dir_y = -1;
		cub->ray.plane_x = -0.66;
		cub->ray.plane_y = 0;
	}
	if (cub->pos.orientation == 'S')
	{
		cub->ray.dir_x = 1;
		cub->ray.dir_y = 0;
		cub->ray.plane_x = 0;
		cub->ray.plane_y = -0.66;
	}
	if (cub->pos.orientation == 'N')
	{
		cub->ray.dir_x = -1;
		cub->ray.dir_y = 0;
		cub->ray.plane_x = 0;
		cub->ray.plane_y = 0.66;
	}
	if (cub->pos.orientation == 'E')
	{
		cub->ray.dir_x = 0;
		cub->ray.dir_y = 1;
		cub->ray.plane_x = 0.66;
		cub->ray.plane_y = 0;
	}
}

void	initialize_t_ray(t_cub *cub)
{
	set_dir(cub);
	cub->ray.time = 0;
	cub->ray.oldtime = 0;
	cub->ray.step_x = 0;
	cub->ray.step_y = 0;
	cub->ray.move_speed = MOV;
	cub->ray.rot_speed = ROT;
	cub->ray.tex_y = 0000000000000000000;
	mlx_mouse_move(cub->mlx_ptr, cub->mlx_win, MAP_WIDTH / 2, MAP_HEIGHT / 2);
	mlx_mouse_get_pos(cub->mlx_ptr, cub->mlx_win, &cub->m.x, &cub->m.y);
	cub->pos.start_x += 0.2;
	cub->pos.start_y += 0.2;
}

int	ray_loop(t_cub *cub)
{
	mlx_mouse_move(cub->mlx_ptr, cub->mlx_win, MAP_WIDTH / 2, MAP_HEIGHT / 2);
	mlx_destroy_image(cub->mlx_ptr, cub->img.img_floor);
	cub->img.img_floor = mlx_new_image(cub->mlx_ptr, MAP_WIDTH, MAP_HEIGHT);
	get_imgs(cub, cub->img.img_floor, get_color(cub->img.rgb_sky),
		get_color(cub->img.rgb_floor));
	calculate_ray(cub);
	return (1);
}

int	handle_mouse(int x, int y, t_cub *cub)
{
	double	old_rot_speed;

	(void)y;
	old_rot_speed = cub->ray.rot_speed;
	cub->ray.rot_speed /= 20;
	if (x < MAP_WIDTH / 2)
		rotate_left(cub);
	else if (x > MAP_WIDTH / 2)
		rotate_right(cub);
	cub->ray.rot_speed = old_rot_speed;
	return (0);
}

void	init_mlx(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		(free_all(cub), exit(2));
	cub->mlx_win = mlx_new_window(cub->mlx_ptr, MAP_WIDTH, MAP_HEIGHT, "cub3d");
	if (!cub->mlx_win)
		(free_all(cub), exit(2));
	cub->img.img_floor = mlx_new_image(cub->mlx_ptr, MAP_WIDTH, MAP_HEIGHT);
	get_imgs(cub, cub->img.img_floor, get_color(cub->img.rgb_sky),
		get_color(cub->img.rgb_floor));
	cub->img.north = mlx_xpm_file_to_image(cub->mlx_ptr, cub->img.north_texture,
			&cub->img.width, &cub->img.height);
	cub->img.south = mlx_xpm_file_to_image(cub->mlx_ptr, cub->img.south_texture,
			&cub->img.width, &cub->img.height);
	cub->img.east = mlx_xpm_file_to_image(cub->mlx_ptr, cub->img.east_texture,
			&cub->img.width, &cub->img.height);
	cub->img.west = mlx_xpm_file_to_image(cub->mlx_ptr, cub->img.west_texture,
			&cub->img.width, &cub->img.height);
	if (!cub->img.north || !cub->img.south || !cub->img.east || !cub->img.west)
		return (free_and_exit(cub));
	initialize_t_ray(cub);
	calculate_ray(cub);
	mlx_hook(cub->mlx_win, KeyPress, KeyPressMask, &handle_key, cub);
	mlx_hook(cub->mlx_win, 17, 0, &handle_cross, cub);
	mlx_hook(cub->mlx_win, MotionNotify, PointerMotionMask, &handle_mouse, cub);
	mlx_loop_hook(cub->mlx_ptr, &ray_loop, cub);
	mlx_loop(cub->mlx_ptr);
}
