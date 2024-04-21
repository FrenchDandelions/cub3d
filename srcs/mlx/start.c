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

int	second_half(t_cub *cub, int color)
{
	int	i;
	int	j;

	i = MAP_HEIGHT / 2;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
			mlx_pixel_put(cub->mlx_ptr, cub->mlx_win, j++, i, color);
		++i;
	}
	return (0);
}

int	first_half(t_cub *cub, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_HEIGHT / 2)
	{
		j = 0;
		while (j < MAP_WIDTH)
			mlx_pixel_put(cub->mlx_ptr, cub->mlx_win, j++, i, color);
		++i;
	}
	return (0);
}

int	handle_key(int code, t_cub *cub)
{
	if (code == XK_Escape)
	{
		mlx_loop_end(cub->mlx_ptr);
		mlx_destroy_window(cub->mlx_ptr, cub->mlx_win);
		mlx_destroy_display(cub->mlx_ptr);
		ft_memdel(cub->mlx_ptr);
		free_all(cub);
		exit(0);
	}
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
	first_half(cub, get_color(cub->img.rgb_sky));
	second_half(cub, get_color(cub->img.rgb_floor));
	mlx_hook(cub->mlx_win, KeyPress, KeyPressMask, &handle_key, cub);
	mlx_loop(cub->mlx_ptr);
}
