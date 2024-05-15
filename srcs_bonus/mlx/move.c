/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:57:40 by thole             #+#    #+#             */
/*   Updated: 2024/05/15 19:12:08 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_air(char curr_tile)
{
	if (curr_tile == '1' || curr_tile == '2')
		return (0);
	return (1);
}

void	move_up(t_cub *cub)
{
	if (is_air(cub->img.map[(int)(cub->pos.start_y + cub->ray.dir_x
				* cub->ray.move_speed)][(int)cub->pos.start_x]))
	{
		cub->pos.start_y += cub->ray.dir_x * cub->ray.move_speed;
	}
	if (is_air(cub->img.map[(int)cub->pos.start_y][(int)(cub->pos.start_x
			+ cub->ray.dir_y * cub->ray.move_speed)]))
	{
		cub->pos.start_x += cub->ray.dir_y * cub->ray.move_speed;
	}
}

void	move_down(t_cub *cub)
{
	if (is_air(cub->img.map[(int)(cub->pos.start_y - cub->ray.dir_x
				* cub->ray.move_speed)][(int)cub->pos.start_x]))
	{
		cub->pos.start_y -= cub->ray.dir_x * cub->ray.move_speed;
	}
	if (is_air(cub->img.map[(int)cub->pos.start_y][(int)(cub->pos.start_x
			- cub->ray.dir_y * cub->ray.move_speed)]))
	{
		cub->pos.start_x -= cub->ray.dir_y * cub->ray.move_speed;
	}
}

void	move_left(t_cub *cub)
{
	if (is_air(cub->img.map[(int)(cub->pos.start_y - cub->ray.dir_y
				* cub->ray.move_speed)][(int)cub->pos.start_x]))
	{
		cub->pos.start_y -= cub->ray.dir_y * cub->ray.move_speed;
	}
	if (is_air(cub->img.map[(int)cub->pos.start_y][(int)(cub->pos.start_x
			+ cub->ray.dir_x * cub->ray.move_speed)]))
	{
		cub->pos.start_x += cub->ray.dir_x * cub->ray.move_speed;
	}
}

void	move_right(t_cub *cub)
{
	if (is_air(cub->img.map[(int)(cub->pos.start_y + cub->ray.dir_y
				* cub->ray.move_speed)][(int)cub->pos.start_x]))
	{
		cub->pos.start_y += cub->ray.dir_y * cub->ray.move_speed;
	}
	if (is_air(cub->img.map[(int)cub->pos.start_y][(int)(cub->pos.start_x
			- cub->ray.dir_x * cub->ray.move_speed)]))
	{
		cub->pos.start_x -= cub->ray.dir_x * cub->ray.move_speed;
	}
}
