/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:03:16 by acroue            #+#    #+#             */
/*   Updated: 2024/05/15 13:59:05 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_image(void **image, t_cub *cub)
{
	if (*image)
		mlx_destroy_image(cub->mlx_ptr, *image);
	*image = NULL;
}

void	free_and_exit(t_cub *cub)
{
	mlx_loop_end(cub->mlx_ptr);
	free_image(&cub->img.north, cub);
	free_image(&cub->img.south, cub);
	free_image(&cub->img.east, cub);
	free_image(&cub->img.west, cub);
	mlx_destroy_image(cub->mlx_ptr, cub->img.img_floor);
	mlx_destroy_window(cub->mlx_ptr, cub->mlx_win);
	mlx_destroy_display(cub->mlx_ptr);
	ft_memdel(cub->mlx_ptr);
	free_all(cub);
	exit(0);
}
