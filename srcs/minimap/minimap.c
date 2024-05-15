/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:58:07 by thole             #+#    #+#             */
/*   Updated: 2024/05/15 16:07:29 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_colors_mmap(t_cub *cub)
{
	cub->mmap.color_wall = 0xD3D3D3;
	if (get_color(cub->img.rgb_sky) == 0xD3D3D3)
	{
		cub->mmap.color_wall = 0x000000;
		cub->mmap.color_floor = 0xD3D3D3;
	}
	cub->mmap.color_player = 0xFF0000;
}

void	initialize_minimap_values(t_cub *cub)
{
	size_t	i;
	size_t	size;
	size_t	second_size;

	second_size = 0;
	i = 0;
	size = ft_strlen(cub->img.map[i]);
	while (cub->img.map[i])
	{
		second_size = ft_strlen(cub->img.map[i]);
		if (second_size > size)
			size = second_size;
		i++;
	}
	cub->mmap.max_len = size;
	cub->mmap.size_map = i;
	cub->mmap.show = 1;
	if ((i * 8) + 40 >= MAP_HEIGHT || (size * 8) + 40 >= MAP_WIDTH)
		cub->mmap.impossible = 1;
	else
		cub->mmap.impossible = 0;
	cub->m.show = 1;
	set_colors_mmap(cub);
}

void	change_mmap_values(t_cub *cub)
{
	if (cub->mmap.show == 1)
		cub->mmap.show = 0;
	else
		cub->mmap.show = 1;
}

void	change_mouse_values(t_cub *cub)
{
	if (cub->m.show == 1)
		cub->m.show = 0;
	else
		cub->m.show = 1;
}
