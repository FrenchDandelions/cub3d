/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:28:57 by thole             #+#    #+#             */
/*   Updated: 2024/04/11 16:28:58 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_struct(t_cub *cub, int mode)
{
	if (mode == 0)
	{
		if (!cub->north_texture || !cub->south_texture || !cub->west_texture
			|| !cub->east_texture || !cub->floor_color || !cub->sky_color
			|| !cub->map[0])
			return (0);
		return (1);
	}
	else
	{
		if (cub->north_texture && cub->south_texture && cub->west_texture
			&& cub->east_texture && cub->floor_color && cub->sky_color
			&& cub->map[0])
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
	if (temp == *cub_str && temp)
		return (2);
	*cub_str = temp;
	if (!*cub_str)
		return (ERR_MALLOC);
	if (!*cub_str[0])
		return (2);
	return (0);
}

static int	fill_texture(char *s, t_cub *cub)
{
	if (cub->map[0])
		return (2);
	if (ft_strncmp(s, "NO", 2) == 0)
		return (checker(&cub->north_texture, 2, s));
	else if (ft_strncmp(s, "SO", 2) == 0)
		return (checker(&cub->south_texture, 2, s));
	else if (ft_strncmp(s, "WE", 2) == 0)
		return (checker(&cub->west_texture, 2, s));
	else if (ft_strncmp(s, "EA", 2) == 0)
		return (checker(&cub->east_texture, 2, s));
	else if (ft_strncmp(s, "F", 1) == 0)
		return (checker(&cub->floor_color, 1, s));
	else if (ft_strncmp(s, "C", 1) == 0)
		return (checker(&cub->sky_color, 1, s));
	return (2);
}

int	is_texture(char *s)
{
	if (ft_strncmp(s, "NO", 2) == 0 && s[2] == ' ')
		return (1);
	else if (ft_strncmp(s, "SO", 2) == 0 && s[2] == ' ')
		return (1);
	else if (ft_strncmp(s, "WE", 2) == 0 && s[2] == ' ')
		return (1);
	else if (ft_strncmp(s, "EA", 2) == 0 && s[2] == ' ')
		return (1);
	else if (ft_strncmp(s, "F", 1) == 0 && s[1] == ' ')
		return (1);
	else if (ft_strncmp(s, "C", 1) == 0 && s[1] == ' ')
		return (1);
	return (0);
}

int	fill_struct(t_cub *cub, char **map, int i, int j)
{
	int	status;

	if (!map[i] && !check_struct(cub, 0))
		return (2);
	else if (!map[i])
	{
		status = check_struct(cub, 1);
		if (status)
			return (SUCCESS);
	}
	if (is_texture(map[i]))
	{
		status = fill_texture(map[i], cub);
		if (status)
			return (status);
	}
	else
	{
		cub->map[j] = map[i];
		return (cub->map[j + 1] = NULL, fill_struct(cub, map, i + 1, j + 1));
	}
	return (fill_struct(cub, map, i + 1, j));
}
