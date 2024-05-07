/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:28:57 by thole             #+#    #+#             */
/*   Updated: 2024/05/07 13:59:56 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_struct(t_cub *cub, int mode)
{
	if (mode == 0)
	{
		if (!cub->img.north_texture || !cub->img.south_texture
			|| !cub->img.west_texture || !cub->img.east_texture
			|| !cub->img.floor_color || !cub->img.sky_color || !cub->img.map[0])
			return (0);
		return (1);
	}
	else if (mode == 2)
	{
		if (cub->img.north_texture && cub->img.south_texture
			&& cub->img.west_texture && cub->img.east_texture
			&& cub->img.floor_color && cub->img.sky_color)
			return (1);
	}
	else
	{
		if (cub->img.north_texture && cub->img.south_texture
			&& cub->img.west_texture && cub->img.east_texture
			&& cub->img.floor_color && cub->img.sky_color && cub->img.map[0])
			return (1);
		else
			return (0);
	}
	return (0);
}

static int	checker(char **cub_str, int size, char *s)
{
	char	*temp;

	temp = ft_substr_cub3d(s, size, 0, *cub_str);
	if (!temp)
		return (ERR_MALLOC);
	if (temp == *cub_str && temp)
		return (2);
	*cub_str = temp;
	if (!*cub_str[0])
		return (2);
	return (0);
}

static int	fill_texture(char *s, t_cub *cub)
{
	if (cub->img.map[0])
		return (2);
	if (ft_strncmp(s, "NO", 2) == 0)
		return (checker(&cub->img.north_texture, 2, s));
	else if (ft_strncmp(s, "SO", 2) == 0)
		return (checker(&cub->img.south_texture, 2, s));
	else if (ft_strncmp(s, "WE", 2) == 0)
		return (checker(&cub->img.west_texture, 2, s));
	else if (ft_strncmp(s, "EA", 2) == 0)
		return (checker(&cub->img.east_texture, 2, s));
	else if (ft_strncmp(s, "F", 1) == 0)
		return (checker(&cub->img.floor_color, 1, s));
	else if (ft_strncmp(s, "C", 1) == 0)
		return (checker(&cub->img.sky_color, 1, s));
	return (2);
}

int	is_empty(t_cub *cub, int j, int i, char **map)
{
	if (!map[i][0] && j == 0 && !cub->img.map[j])
		return (fill_struct(cub, map, i + 1, j));
	else if (!map[i][0] && j > 0 && cub->img.map[j - 1])
	{
		cub->status = 2;
		return (2);
	}
	return (0);
}

int	fill_struct(t_cub *cub, char **map, int i, int j)
{
	int	status;

	if (!map[i] && !check_struct(cub, 0))
		return (2);
	else if (!map[i])
		if (check_struct(cub, 1))
			return (SUCCESS);
	if (is_texture(map[i]))
	{
		status = fill_texture(map[i], cub);
		if (status)
			return (status);
	}
	else if (check_struct(cub, 2))
	{
		status = is_empty(cub, j, i, map);
		if (status)
			return (status);
		cub->img.map[j] = map[i];
		return (cub->img.map[j + 1] = NULL, fill_struct(cub, map, i + 1, j
				+ 1));
	}
	return (fill_struct(cub, map, i + 1, j));
}
