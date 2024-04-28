/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:29:16 by thole             #+#    #+#             */
/*   Updated: 2024/04/21 18:29:17 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_key(int code, t_cub *cub)
{
	if (code == XK_Escape)
	{
		mlx_loop_end(cub->mlx_ptr);
		mlx_destroy_image(cub->mlx_ptr, cub->img.img_floor);
		mlx_destroy_image(cub->mlx_ptr, cub->img.img_sky);
		mlx_destroy_window(cub->mlx_ptr, cub->mlx_win);
		mlx_destroy_display(cub->mlx_ptr);
		ft_memdel(cub->mlx_ptr);
		free_all(cub);
		exit(0);
	}
	return (0);
}

void	get_imgs(t_cub *cub, void *img, int color, int pos)
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
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_win, img, 0, pos);
}

void	init_mlx(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		(free_all(cub), exit(2));
	cub->mlx_win = mlx_new_window(cub->mlx_ptr, MAP_WIDTH, MAP_HEIGHT, "cub3d");
	if (!cub->mlx_win)
		(free_all(cub), exit(2));
	cub->img.img_floor = mlx_new_image(cub->mlx_ptr, MAP_WIDTH, MAP_HEIGHT / 2);
	cub->img.img_sky = mlx_new_image(cub->mlx_ptr, MAP_WIDTH, MAP_HEIGHT / 2);
	get_imgs(cub, cub->img.img_floor, get_color(cub->img.rgb_floor), 0);
	get_imgs(cub, cub->img.img_sky, get_color(cub->img.rgb_sky), MAP_HEIGHT
		/ 2);
	mlx_hook(cub->mlx_win, KeyPress, KeyPressMask, &handle_key, cub);
	mlx_loop(cub->mlx_ptr);
}
