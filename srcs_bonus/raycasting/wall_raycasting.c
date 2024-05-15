/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:02:16 by acroue            #+#    #+#             */
/*   Updated: 2024/05/15 13:59:10 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	find_color(t_cub *cub)
{
	double	tex_pos;

	tex_pos = (cub->ray.draw_start - MAP_HEIGHT / 2 + cub->ray.lh / 2)
		* cub->ray.step;
	if (cub->ray.side == 1)
	{
		if (cub->ray.ray_dir_y > 0)
			cub->ray.color = set_pixel_color(BLUE, cub, tex_pos,
					cub->ray.picked_img);
		else
			cub->ray.color = set_pixel_color(GOLD, cub, tex_pos,
					cub->ray.picked_img);
	}
	else
	{
		if (cub->ray.ray_dir_x > 0)
			cub->ray.color = set_pixel_color(GREEN, cub, tex_pos,
					cub->ray.picked_img);
		else
			cub->ray.color = set_pixel_color(PINK, cub, tex_pos,
					cub->ray.picked_img);
	}
}

static double	where_wall_hit(int face, t_cub *cub)
{
	double	hit_x;

	hit_x = 0;
	if (face == EAST || face == WEST)
		hit_x = cub->pos.start_y + cub->ray.tot_dist * cub->ray.ray_dir_x;
	else
		hit_x = cub->pos.start_x + cub->ray.tot_dist * cub->ray.ray_dir_y;
	hit_x -= floor(hit_x);
	return (hit_x);
}

static int	where_x_on_texture(int face, t_cub *cub, double wall_x)
{
	int	texture_x;

	texture_x = (int)(wall_x * (double)cub->img.width);
	if (face == EAST || face == NORTH)
		return ((double)cub->img.width - texture_x - 1);
	(void)face;
	return (texture_x);
}

static int	get_pixel(t_cub *cub, char *img, int x, int y)
{
	return (*(int *)(img + (y * cub->img.ray_lb + x * (cub->img.ray_bpp / 8))));
}

int	set_pixel_color(int face, t_cub *cub, double tex_pos, char *img)
{
	double	wall_x;
	int		texture_x;
	int		color;

	wall_x = where_wall_hit(face, cub);
	texture_x = where_x_on_texture(face, cub, wall_x);
	color = (get_pixel(cub, img, texture_x, (int)tex_pos & (cub->img.width
					- 1)));
	return (color);
}
