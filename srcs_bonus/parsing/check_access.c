/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:55:46 by thole             #+#    #+#             */
/*   Updated: 2024/05/15 14:09:32 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	len(char *s)
{
	return ((int)ft_strlen(s));
}

static int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

static int	check_if_out_of_bounds(char **map, int i, int j, int size_map)
{
	if (i - 1 < 0 || j - 1 < 0 || j >= (int)ft_strlen(map[i]) || i >= size_map)
		return (FAILURE);
	if (j - 1 > len(map[i - 1]) || j + 1 > len(map[i + 1]))
		return (FAILURE);
	if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j - 1] == ' '
		|| map[i][j + 1] == ' ')
		return (FAILURE);
	return (SUCCESS);
}

static int	check_line(char **map, int i, int j, int size_map)
{
	if (!map[i][j])
		return (0);
	if (map[i][j] == '0' || is_player(map[i][j]) || map[i][j] == '2')
		if (check_if_out_of_bounds(map, i, j, size_map) == FAILURE)
			return (1);
	return (check_line(map, i, j + 1, size_map));
}

int	check_access(char **map, int size_map, int i)
{
	if (!map[i])
		return (SUCCESS);
	if (check_line(map, i, 0, size_map))
		return (FAILURE);
	return (check_access(map, size_map, i + 1));
}
