/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:55:46 by thole             #+#    #+#             */
/*   Updated: 2024/04/16 19:55:47 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	recusivity(char **map, int x, int y, int size_map)
{
	int	check;

	if (map[x] && map[x + 1])
	{
		check = check_access(map, x + 1, y, size_map);
		if ((check != SUCCESS && check != FAILURE))
			return (check);
	}
	if (map[x][y] && map[x][y + 1])
	{
		check = check_access(map, x, y + 1, size_map);
		if ((check != SUCCESS && check != FAILURE))
			return (check);
	}
	if (map[x][y] && y - 1 >= 0)
	{
		check = check_access(map, x, y - 1, size_map);
		if ((check != SUCCESS && check != FAILURE))
			return (check);
	}
	if (map[x] && x - 1 >= 0)
	{
		check = check_access(map, x - 1, y, size_map);
		if ((check != SUCCESS && check != FAILURE))
			return (check);
	}
	return (SUCCESS);
}

int	check_access(char **map, int x, int y, int size_map)
{
	if (!map)
		return (ERR_MALLOC);
	if (y < 0 || x < 0 || x >= size_map || y >= (int)ft_strlen(map[x])
		|| map[x][y] == '1')
		return (FAILURE);
	printf("char :%c, x %d y %d,line %s\n", map[x][y], x, y, map[x]);
	if (map[x][y] == ' ')
		return (ERR_PARSING);
	map[x][y] = '1';
	return (recusivity(map, x, y, size_map));
}
