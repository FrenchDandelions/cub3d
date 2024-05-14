/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:02:16 by acroue            #+#    #+#             */
/*   Updated: 2024/05/14 17:17:45 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	*pick_img_source(int face, t_cub *cub)
{
	if (face == PINK)
		return (cub->img.south);
	else if (face == GREEN)
		return (cub->img.north);
	else if (face == BLUE)
		return (cub->img.west);
	else if (face == GOLD)
		return (cub->img.east);
	return (NULL);
}

static double	where_wall_hit(int face, t_cub *cub)
{
	double	hit_x;

	hit_x = 0;
	// if (face == EAST)
	// hit_x = cub->pos.start_x + cub->ray.perp_wall_dist * cub->ray.ray_dir_x;
	// else if (face == WEST)
	// hit_x = cub->pos.start_x - cub->ray.perp_wall_dist * cub->ray.ray_dir_x;
	// else if (face == NORTH)
	// hit_x = cub->pos.start_y + cub->ray.perp_wall_dist * cub->ray.ray_dir_y;
	// else if (face == SOUTH)
	// hit_x = cub->pos.start_y - cub->ray.perp_wall_dist * cub->ray.ray_dir_y;
	if (face == EAST || face == WEST)
		hit_x = cub->pos.start_x + cub->ray.tot_dist * cub->ray.ray_dir_x;
	else
		hit_x = cub->pos.start_y + cub->ray.tot_dist * cub->ray.ray_dir_y;
	hit_x -= floor(hit_x);
	return (hit_x);
}

static int	where_x_on_texture(int face, t_cub *cub, double wall_x)
{
	int	texture_x;

	texture_x = (int)(wall_x * (double)cub->img.width);
	(void)face;
	return (texture_x);
}

static int	get_pixel(t_cub *cub, char *img, int x, int y)
{
	return (*(int *)(img + (y * cub->img.ray_lb + x * \
	(cub->img.ray_bpp / 8))));
}

int set_pixel_color(int face, t_cub *cub)
{
	char	*img;
	double	wall_x;
	int	texture_x;
	int	color;

	img = mlx_get_data_addr(pick_img_source(face, cub),
	&cub->img.ray_bpp, &cub->img.ray_lb, &cub->img.ray_end);
	wall_x = where_wall_hit(face, cub);
	texture_x = where_x_on_texture(face, cub, wall_x);
	int line_height = (int)(MAP_HEIGHT / cub->ray.tot_dist);
	double step = 1.0f * cub->img.width / line_height;
	double tex_pos = (cub->ray.draw_start - MAP_HEIGHT / 2 + line_height / 2) * step;
	color = (get_pixel(cub, img, texture_x, (int) tex_pos & (cub->img.width - 1)));
	return (color);
}
