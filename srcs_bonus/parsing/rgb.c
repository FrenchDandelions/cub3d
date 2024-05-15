/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:28:26 by thole             #+#    #+#             */
/*   Updated: 2024/05/15 13:59:09 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	get_color(int *colors)
{
	return ((colors[0] << 16) | (colors[1] << 8) | colors[2]);
}

int	check_rgb(t_cub *cub)
{
	int	index;
	int	flag;

	index = 0;
	flag = 0;
	cub->img.rgb_floor[0] = ft_atoi_rgb(cub->img.floor_color, &index, &flag);
	if (flag == 1 || index++ < 0)
		return (ERR_CLR_F);
	cub->img.rgb_floor[1] = ft_atoi_rgb(cub->img.floor_color, &index, &flag);
	if (flag == 1 || index++ < 0)
		return (ERR_CLR_F);
	cub->img.rgb_floor[2] = ft_atoi_rgb(cub->img.floor_color, &index, &flag);
	if (flag == 1 || cub->img.floor_color[index])
		return (ERR_CLR_F);
	index = 0;
	cub->img.rgb_sky[0] = ft_atoi_rgb(cub->img.sky_color, &index, &flag);
	if (flag == 1 || index++ < 0)
		return (ERR_CLR_S);
	cub->img.rgb_sky[1] = ft_atoi_rgb(cub->img.sky_color, &index, &flag);
	if (flag == 1 || index++ < 0)
		return (ERR_CLR_S);
	cub->img.rgb_sky[2] = ft_atoi_rgb(cub->img.sky_color, &index, &flag);
	if (flag == 1 || cub->img.sky_color[index])
		return (ERR_CLR_S);
	return (SUCCESS);
}
