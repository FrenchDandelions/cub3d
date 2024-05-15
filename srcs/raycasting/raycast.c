/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:59:31 by thole             #+#    #+#             */
/*   Updated: 2024/05/15 19:37:11 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	*pick_img_source(t_cub *cub)
{
	if (cub->ray.side == 0 && cub->ray.ray_dir_x < 0)
		return (cub->img.south);
	else if (cub->ray.side == 0 && cub->ray.ray_dir_x > 0)
		return (cub->img.north);
	else if (cub->ray.side == 1 && cub->ray.ray_dir_y > 0)
		return (cub->img.west);
	else if (cub->ray.side == 1 && cub->ray.ray_dir_y < 0)
		return (cub->img.east);
	return (NULL);
}

void	draw_line(int x, t_cub *cub)
{
	cub->img.buffer = mlx_get_data_addr(cub->img.img_floor,
			&cub->img.pixel_bits, &cub->img.line_bytes, &cub->img.endian);
	cub->ray.lh = (int)(MAP_HEIGHT / cub->ray.tot_dist);
	cub->ray.step = 1.0f * cub->img.width / cub->ray.lh;
	cub->ray.picked_img = mlx_get_data_addr(pick_img_source(cub),
			&cub->img.ray_bpp, &cub->img.ray_lb, &cub->img.ray_end);
	while (cub->ray.draw_start <= cub->ray.draw_end)
	{
		find_color(cub);
		cub->img.pixel = (cub->ray.draw_start * cub->img.line_bytes) + (x * 4);
		if (cub->img.endian == 0)
		{
			cub->img.buffer[cub->img.pixel + 0] = (cub->ray.color) & 0xFF;
			cub->img.buffer[cub->img.pixel + 1] = (cub->ray.color >> 8) & 0xFF;
			cub->img.buffer[cub->img.pixel + 2] = (cub->ray.color >> 16) & 0xFF;
			cub->img.buffer[cub->img.pixel + 3] = (cub->ray.color >> 24);
		}
		cub->ray.draw_start += 1;
	}
}

void	get_wall_dist(t_cub *cub)
{
	if (cub->ray.side == 0)
		cub->ray.perp_wall_dist = cub->ray.side_dist_x - cub->ray.delta_dist_x;
	else
		cub->ray.perp_wall_dist = cub->ray.side_dist_y - cub->ray.delta_dist_y;
	cub->ray.tot_dist += cub->ray.perp_wall_dist;
	cub->ray.line_height = (int)(MAP_HEIGHT / cub->ray.perp_wall_dist);
	cub->ray.draw_start = -cub->ray.line_height / 2 + MAP_HEIGHT / 2;
	if (cub->ray.draw_start < 0)
		cub->ray.draw_start = 0;
	cub->ray.draw_end = cub->ray.line_height / 2 + MAP_HEIGHT / 2;
	if (cub->ray.draw_end >= MAP_HEIGHT)
		cub->ray.draw_end = MAP_HEIGHT - 1;
}

void	digital_differential_analysis(t_cub *cub)
{
	while (cub->ray.hit == 0)
	{
		if (cub->ray.side_dist_x < cub->ray.side_dist_y)
		{
			cub->ray.side_dist_x += cub->ray.delta_dist_x;
			cub->ray.map_x += cub->ray.step_x;
			cub->ray.side = 0;
		}
		else
		{
			cub->ray.side_dist_y += cub->ray.delta_dist_y;
			cub->ray.map_y += cub->ray.step_y;
			cub->ray.side = 1;
		}
		if (cub->img.map[cub->ray.map_x][cub->ray.map_y] == '1')
			cub->ray.hit = 1;
	}
}

int	calculate_ray(t_cub *cub)
{
	int	x;

	x = -1;
	while (++x < MAP_WIDTH)
	{
		cub->ray.tot_dist = 0;
		cub->ray.camera_x = 2 * x / (double)MAP_WIDTH - 1;
		cub->ray.ray_dir_x = cub->ray.dir_x + cub->ray.plane_x
			* cub->ray.camera_x;
		cub->ray.ray_dir_y = cub->ray.dir_y + cub->ray.plane_y
			* cub->ray.camera_x;
		cub->ray.map_x = (int)cub->pos.start_y;
		cub->ray.map_y = (int)cub->pos.start_x;
		cub->ray.hit = 0;
		calculate_delta(cub);
		handle_step(cub);
		digital_differential_analysis(cub);
		get_wall_dist(cub);
		draw_line(x, cub);
	}
	add_mmap(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_win, cub->img.img_floor, 0,
		0);
	return (0);
}
