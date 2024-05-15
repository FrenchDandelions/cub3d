/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:14:27 by acroue            #+#    #+#             */
/*   Updated: 2024/05/15 19:18:15 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	close_animation(t_cub *cub)
{
	if (get_current_time() - cub->timestamp >= 1200)
	{
		cub->img.is_animating = 0;
		cub->img.curr_door = cub->img.doors[0];
		cub->img.map[cub->pos_y][cub->pos_x] = '2';
	}
	if (get_current_time() - cub->timestamp2 >= 100 && cub->frame >= 0)
	{
		cub->img.curr_door = cub->img.doors[cub->frame--];
		cub->timestamp2 = get_current_time();
	}
}

void	check_animation(t_cub *cub, int order)
{
	if (cub->img.is_animating && !order)
	{
		if (get_current_time() - cub->timestamp >= 1200)
		{
			cub->img.is_animating = 0;
			cub->img.curr_door = cub->img.doors[0];
			cub->img.map[cub->pos_y][cub->pos_x] = '3';
		}
		if (get_current_time() - cub->timestamp2 >= 100 && cub->frame < DNBR)
		{
			cub->img.curr_door = cub->img.doors[cub->frame++];
			cub->timestamp2 = get_current_time();
		}
	}
	else if (cub->img.is_animating && order)
	{
		close_animation(cub);
	}
}

void	anima(t_cub *cub, int pos_y, int pos_x)
{
	cub->timestamp = get_current_time();
	cub->timestamp2 = get_current_time();
	cub->frame = 1;
	cub->pos_x = pos_x;
	cub->pos_y = pos_y;
	cub->img.curr_door = cub->img.doors[cub->frame++];
	cub->img.map[cub->pos_y][cub->pos_x] = '4';
	cub->img.is_animating = 1;
	cub->order = 0;
}

void	reverse_anima(t_cub *cub, int pos_y, int pos_x)
{
	cub->pos_x = pos_x;
	cub->pos_y = pos_y;
	cub->img.map[cub->pos_y][cub->pos_x] = '4';
	cub->timestamp = get_current_time();
	cub->timestamp2 = get_current_time();
	cub->frame = 10;
	cub->img.curr_door = cub->img.doors[cub->frame--];
	cub->img.is_animating = 1;
	cub->order = 1;
}
