/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:08:30 by acroue            #+#    #+#             */
/*   Updated: 2024/05/14 19:10:21 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	right_arrow(t_cub *cub)
{
	cub->ray.old_dir_x = cub->ray.dir_x;
	cub->ray.dir_x = cub->ray.dir_x * cos(-cub->ray.rot_speed)
		- cub->ray.dir_y * sin(-cub->ray.rot_speed);
	cub->ray.dir_y = cub->ray.old_dir_x * sin(-cub->ray.rot_speed)
		+ cub->ray.dir_y * cos(-cub->ray.rot_speed);
	cub->ray.old_plane_x = cub->ray.plane_x;
	cub->ray.plane_x = cub->ray.plane_x * cos(-cub->ray.rot_speed)
		- cub->ray.plane_y * sin(-cub->ray.rot_speed);
	cub->ray.plane_y = cub->ray.old_plane_x * sin(-cub->ray.rot_speed)
		+ cub->ray.plane_y * cos(-cub->ray.rot_speed);
}

void	left_arrow(t_cub *cub)
{
	cub->ray.old_dir_x = cub->ray.dir_x;
	cub->ray.dir_x = cub->ray.dir_x * cos(cub->ray.rot_speed)
		- cub->ray.dir_y * sin(cub->ray.rot_speed);
	cub->ray.dir_y = cub->ray.old_dir_x * sin(cub->ray.rot_speed)
		+ cub->ray.dir_y * cos(cub->ray.rot_speed);
	cub->ray.old_plane_x = cub->ray.plane_x;
	cub->ray.plane_x = cub->ray.plane_x * cos(cub->ray.rot_speed)
		- cub->ray.plane_y * sin(cub->ray.rot_speed);
	cub->ray.plane_y = cub->ray.old_plane_x * sin(cub->ray.rot_speed)
		+ cub->ray.plane_y * cos(cub->ray.rot_speed);
}
