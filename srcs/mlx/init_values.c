/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:12:21 by acroue            #+#    #+#             */
/*   Updated: 2024/05/15 19:36:08 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir(t_cub *cub)
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
}

static void	set_dir_two(t_cub *cub)
{
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

static void	initialize_t_ray(t_cub *cub)
{
	set_dir(cub);
	set_dir_two(cub);
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

void	init_and_calculate_ray(t_cub *cub)
{
	initialize_t_ray(cub);
	initialize_minimap_values(cub);
	calculate_ray(cub);
}

void	init_mlx(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		(free_all(cub), write(2, "Error\nMissing env\n", 19), exit(2));
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
	init_and_calculate_ray(cub);
	mlx_hook(cub->mlx_win, KeyPress, KeyPressMask, &handle_key, cub);
	mlx_hook(cub->mlx_win, 17, 0, &handle_cross, cub);
	mlx_hook(cub->mlx_win, MotionNotify, PointerMotionMask, &handle_mouse, cub);
	mlx_loop_hook(cub->mlx_ptr, &ray_loop, cub);
	mlx_loop(cub->mlx_ptr);
}
