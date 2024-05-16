/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:45:04 by acroue            #+#    #+#             */
/*   Updated: 2024/05/16 14:35:14 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_doors(t_cub *cub)
{
	free_image(&cub->img.doors[0], cub);
	free_image(&cub->img.doors[1], cub);
	free_image(&cub->img.doors[2], cub);
	free_image(&cub->img.doors[3], cub);
	free_image(&cub->img.doors[4], cub);
	free_image(&cub->img.doors[5], cub);
	free_image(&cub->img.doors[6], cub);
	free_image(&cub->img.doors[7], cub);
	free_image(&cub->img.doors[8], cub);
	free_image(&cub->img.doors[9], cub);
	free_image(&cub->img.doors[10], cub);
}

void	init_doors(t_cub *cub)
{
	cub->img.doors[0] = init_img(cub, DOOR_ZERO);
	cub->img.doors[1] = init_img(cub, DOOR_ONE);
	cub->img.doors[2] = init_img(cub, DOOR_TWO);
	cub->img.doors[3] = init_img(cub, DOOR_THREE);
	cub->img.doors[4] = init_img(cub, DOOR_FOUR);
	cub->img.doors[5] = init_img(cub, DOOR_FIVE);
	cub->img.doors[6] = init_img(cub, DOOR_SIX);
	cub->img.doors[7] = init_img(cub, DOOR_SEVEN);
	cub->img.doors[8] = init_img(cub, DOOR_EIGHT);
	cub->img.doors[9] = init_img(cub, DOOR_NINE);
	cub->img.doors[10] = init_img(cub, DOOR_TEN);
	if (!cub->img.doors[0] || !cub->img.doors[1] || !cub->img.doors[2])
		return ((void)ft_dprintf(2, "%s\n", ERR_TEXTURE), free_and_exit(cub));
	if (!cub->img.doors[3] || !cub->img.doors[4] || !cub->img.doors[5])
		return ((void)ft_dprintf(2, "%s\n", ERR_TEXTURE), free_and_exit(cub));
	if (!cub->img.doors[6] || !cub->img.doors[7] || !cub->img.doors[8])
		return ((void)ft_dprintf(2, "%s\n", ERR_TEXTURE), free_and_exit(cub));
	if (!cub->img.doors[9] || !cub->img.doors[10])
		return ((void)ft_dprintf(2, "%s\n", ERR_TEXTURE), free_and_exit(cub));
	cub->img.curr_door = cub->img.doors[0];
}

int	is_door(t_cub *cub, int pos_y, int pos_x, char ch)
{
	if (cub->img.map[pos_y][pos_x] == ch)
		return (1);
	return (0);
}

void	space_bar(t_cub *cub)
{
	int	pos_x;
	int	pos_y;

	pos_x = (int)cub->pos.start_x;
	pos_y = (int)cub->pos.start_y;
	if (cub->ray.dir_y > 0.75 && is_door(cub, pos_y, pos_x + 1, '2'))
		anima(cub, pos_y, pos_x + 1);
	else if (cub->ray.dir_y <= -0.75 && is_door(cub, pos_y, pos_x - 1, '2'))
		anima(cub, pos_y, pos_x - 1);
	else if (cub->ray.dir_x > 0.75 && is_door(cub, pos_y + 1, pos_x, '2'))
		anima(cub, pos_y + 1, pos_x);
	else if (cub->ray.dir_x <= -0.75 && is_door(cub, pos_y - 1, pos_x, '2'))
		anima(cub, pos_y - 1, pos_x);
	else if (cub->ray.dir_y > 0.75 && is_door(cub, pos_y, pos_x + 1, '3'))
		reverse_anima(cub, pos_y, pos_x + 1);
	else if (cub->ray.dir_y <= -0.75 && is_door(cub, pos_y, pos_x - 1, '3'))
		reverse_anima(cub, pos_y, pos_x - 1);
	else if (cub->ray.dir_x > 0.75 && is_door(cub, pos_y + 1, pos_x, '3'))
		reverse_anima(cub, pos_y + 1, pos_x);
	else if (cub->ray.dir_x <= -0.75 && is_door(cub, pos_y - 1, pos_x, '3'))
		reverse_anima(cub, pos_y - 1, pos_x);
}
