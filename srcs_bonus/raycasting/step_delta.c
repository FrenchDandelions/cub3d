/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_delta.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:17:14 by thole             #+#    #+#             */
/*   Updated: 2024/05/15 13:59:09 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_step(t_cub *cub)
{
	if (cub->ray.ray_dir_x < 0)
	{
		cub->ray.step_x = -1;
		cub->ray.side_dist_x = (cub->pos.start_y - cub->ray.map_x)
			* cub->ray.delta_dist_x;
	}
	else
	{
		cub->ray.step_x = 1;
		cub->ray.side_dist_x = (cub->ray.map_x + 1.0 - cub->pos.start_y)
			* cub->ray.delta_dist_x;
	}
	if (cub->ray.ray_dir_y < 0)
	{
		cub->ray.step_y = -1;
		cub->ray.side_dist_y = (cub->pos.start_x - cub->ray.map_y)
			* cub->ray.delta_dist_y;
	}
	else
	{
		cub->ray.step_y = 1;
		cub->ray.side_dist_y = (cub->ray.map_y + 1.0 - cub->pos.start_x)
			* cub->ray.delta_dist_y;
	}
}

void	calculate_delta(t_cub *cub)
{
	if (cub->ray.ray_dir_x == 0)
		cub->ray.delta_dist_x = 1e30;
	else
		cub->ray.delta_dist_x = fabs(1 / cub->ray.ray_dir_x);
	if (cub->ray.ray_dir_y == 0)
		cub->ray.delta_dist_y = 1e30;
	else
		cub->ray.delta_dist_y = fabs(1 / cub->ray.ray_dir_y);
}
