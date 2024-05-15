/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:29:16 by thole             #+#    #+#             */
/*   Updated: 2024/05/14 19:40:50 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_cross(t_cub *cub)
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
		right_arrow(cub);
	}
	else if (code == XK_Left)
	{
		left_arrow(cub);
	}
	return (0);
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
