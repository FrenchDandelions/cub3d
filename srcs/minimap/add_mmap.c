/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_mmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:08:26 by thole             #+#    #+#             */
/*   Updated: 2024/05/16 13:37:26 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_color(t_cub *cub, char **buffer, int yx[2])
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			cub->img.pixel = ((yx[0] * 8 + 10 + i) * cub->img.line_bytes)
				+ ((yx[1] * 8 + 10 + j) * 4);
			if (cub->img.endian == 0)
			{
				(*buffer)[cub->img.pixel + 0] = (cub->mmap.cl_pk) & 0xFF;
				(*buffer)[cub->img.pixel + 1] = (cub->mmap.cl_pk >> 8) & 0xFF;
				(*buffer)[cub->img.pixel + 2] = (cub->mmap.cl_pk >> 16) & 0xFF;
				(*buffer)[cub->img.pixel + 3] = (cub->mmap.cl_pk >> 24);
			}
			j++;
		}
		i++;
	}
}

static void	check_index(char c, t_cub *cub, size_t i, size_t j)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		cub->mmap.cl_pk = cub->mmap.color_floor;
		set_color(cub, &(cub->img.buffer), (int [2]){i, j});
	}
	if (c == '1')
	{
		cub->mmap.cl_pk = cub->mmap.color_wall;
		set_color(cub, &(cub->img.buffer), (int [2]){i, j});
	}
}

void	check_player(t_cub *cub, int i, int j)
{
	if (floor(cub->pos.start_y) == i && floor(cub->pos.start_x) == j)
	{
		cub->mmap.cl_pk = cub->mmap.color_player;
		set_color(cub, &(cub->img.buffer), (int [2]){i, j});
	}
}

void	add_mmap(t_cub *cub)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (cub->mmap.show && !cub->mmap.impossible)
	{
		cub->img.buffer = mlx_get_data_addr(cub->img.img_floor,
				&cub->img.pixel_bits, &cub->img.line_bytes, &cub->img.endian);
		while (i < cub->mmap.size_map)
		{
			j = 0;
			while (j < ft_strlen(cub->img.map[i]) && cub->img.map[i][j])
			{
				check_index(cub->img.map[i][j], cub, i, j);
				check_player(cub, i, j);
				j++;
			}
			i++;
		}
	}
}
