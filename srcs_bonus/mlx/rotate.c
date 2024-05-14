/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:17:46 by thole             #+#    #+#             */
/*   Updated: 2024/05/09 17:17:48 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_cub *cub)
{
	cub->ray.old_dir_x = cub->ray.dir_x;
	cub->ray.dir_x = cub->ray.dir_x * cos(cub->ray.rot_speed) - cub->ray.dir_y
		* sin(cub->ray.rot_speed);
	cub->ray.dir_y = cub->ray.old_dir_x * sin(cub->ray.rot_speed)
		+ cub->ray.dir_y * cos(cub->ray.rot_speed);
	cub->ray.old_plane_x = cub->ray.plane_x;
	cub->ray.plane_x = cub->ray.plane_x * cos(cub->ray.rot_speed)
		- cub->ray.plane_y * sin(cub->ray.rot_speed);
	cub->ray.plane_y = cub->ray.old_plane_x * sin(cub->ray.rot_speed)
		+ cub->ray.plane_y * cos(cub->ray.rot_speed);
}

void	rotate_right(t_cub *cub)
{
	cub->ray.old_dir_x = cub->ray.dir_x;
	cub->ray.dir_x = cub->ray.dir_x * cos(-cub->ray.rot_speed) - cub->ray.dir_y
		* sin(-cub->ray.rot_speed);
	cub->ray.dir_y = cub->ray.old_dir_x * sin(-cub->ray.rot_speed)
		+ cub->ray.dir_y * cos(-cub->ray.rot_speed);
	cub->ray.old_plane_x = cub->ray.plane_x;
	cub->ray.plane_x = cub->ray.plane_x * cos(-cub->ray.rot_speed)
		- cub->ray.plane_y * sin(-cub->ray.rot_speed);
	cub->ray.plane_y = cub->ray.old_plane_x * sin(-cub->ray.rot_speed)
		+ cub->ray.plane_y * cos(-cub->ray.rot_speed);
}
