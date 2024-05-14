/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:26:37 by acroue            #+#    #+#             */
/*   Updated: 2024/05/14 19:26:52 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_color(t_cub *cub, int color, char **buffer)
{
	cub->img.pixel = (y * cub->img.line_bytes) + (x * 4);
	if (cub->img.endian == 0)
	{
		*buffer[cub->img.pixel + 0] = (color) & 0xFF;
		*buffer[cub->img.pixel + 1] = (color >> 8) & 0xFF;
		*buffer[cub->img.pixel + 2] = (color >> 16) & 0xFF;
		*buffer[cub->img.pixel + 3] = (color >> 24);
	}
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
			set_color(cub, color, &buffer);
	}
	y--;
	while (++y < 50)
	{
		x = -1;
		while (++x < 12)
			set_color(cub, color2, &buffer);
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
			set_color(cub, color, &cub->img.buffer);
	}
	y--;
	while (++y < MAP_HEIGHT)
	{
		x = -1;
		while (++x < MAP_WIDTH)
			set_color(cub, color2, &cub->img.buffer);
	}
}
