/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:57:40 by thole             #+#    #+#             */
/*   Updated: 2024/05/14 19:30:49 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_cub *cub)
{
	if (cub->img.map[(int)(cub->pos.start_y + cub->ray.dir_x
			* cub->ray.move_speed)][(int)cub->pos.start_x] != '1')
	{
		cub->pos.start_y += cub->ray.dir_x * cub->ray.move_speed;
	}
	if (cub->img.map[(int)cub->pos.start_y][(int)(cub->pos.start_x
		+ cub->ray.dir_y * cub->ray.move_speed)] != '1')
	{
		cub->pos.start_x += cub->ray.dir_y * cub->ray.move_speed;
	}
}

void	move_down(t_cub *cub)
{
	if (cub->img.map[(int)(cub->pos.start_y - cub->ray.dir_x
			* cub->ray.move_speed)][(int)cub->pos.start_x] != '1')
	{
		cub->pos.start_y -= cub->ray.dir_x * cub->ray.move_speed;
	}
	if (cub->img.map[(int)cub->pos.start_y][(int)(cub->pos.start_x
		- cub->ray.dir_y * cub->ray.move_speed)] != '1')
	{
		cub->pos.start_x -= cub->ray.dir_y * cub->ray.move_speed;
	}
}

void	move_left(t_cub *cub)
{
	if (cub->img.map[(int)(cub->pos.start_y - cub->ray.dir_y
			* cub->ray.move_speed)][(int)cub->pos.start_x] != '1')
	{
		cub->pos.start_y -= cub->ray.dir_y * cub->ray.move_speed;
	}
	if (cub->img.map[(int)cub->pos.start_y][(int)(cub->pos.start_x
		+ cub->ray.dir_x * cub->ray.move_speed)] != '1')
	{
		cub->pos.start_x += cub->ray.dir_x * cub->ray.move_speed;
	}
}

void	move_right(t_cub *cub)
{
	if (cub->img.map[(int)(cub->pos.start_y + cub->ray.dir_y
			* cub->ray.move_speed)][(int)cub->pos.start_x] != '1')
	{
		cub->pos.start_y += cub->ray.dir_y * cub->ray.move_speed;
	}
	if (cub->img.map[(int)cub->pos.start_y][(int)(cub->pos.start_x
		- cub->ray.dir_x * cub->ray.move_speed)] != '1')
	{
		cub->pos.start_x -= cub->ray.dir_x * cub->ray.move_speed;
	}
}
