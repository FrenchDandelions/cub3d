/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:02:16 by acroue            #+#    #+#             */
/*   Updated: 2024/05/09 20:43:15 by acroue           ###   ########.fr       */
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
	if (face == NORTH)
		hit_x = cub->pos.start_x + cub->ray.perp_wall_dist * cub->ray.ray_dir_x;
	else if (face == SOUTH)
		hit_x = cub->pos.start_x - cub->ray.perp_wall_dist * cub->ray.ray_dir_x;
	else if (face == EAST)
		hit_x = cub->pos.start_y + cub->ray.perp_wall_dist * cub->ray.ray_dir_y;
	else if (face == WEST)
		hit_x = cub->pos.start_y - cub->ray.perp_wall_dist * cub->ray.ray_dir_y;
	hit_x -= floor(hit_x);
	return (hit_x);
}

static int	where_x_on_texture(int face, t_cub *cub, double wall_x)
{
	int	texture_x;

	texture_x = (int)(wall_x * (double)cub->img.width);
	if (face == EAST)
		texture_x = cub->img.width - texture_x - 1;
	else if (face == SOUTH)
		texture_x = cub->img.width - texture_x - 1;
	return (texture_x);
}

static int	get_pixel(t_cub *cub, char *img, int x, int y)
{
	return (*(int *)(img + (y * cub->img.line_bytes + x * \
	(cub->img.pixel_bits / 8))));
}

int	set_pixel_color(int face, t_cub *cub)
{
	char	*img;
	double	wall_x;
	int		texture_x;
	int		color;

	if (cub->ray.tex_y == 32)
		cub->ray.tex_y = 0;
	img = mlx_get_data_addr(pick_img_source(face, cub),
			&cub->img.pixel_bits, &cub->img.line_bytes, &cub->img.endian);
	wall_x = where_wall_hit(face, cub);
	texture_x = where_x_on_texture(face, cub, wall_x);
	color = (get_pixel(cub, img, texture_x, cub->ray.tex_y));
	cub->ray.tex_y++;
	return (color);
}
