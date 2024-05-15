/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:30:42 by thole             #+#    #+#             */
/*   Updated: 2024/05/15 14:09:06 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	is_starting_point(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	accepted_chars(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '1' || c == '0'
		|| c == ' ' || c == '2')
		return (1);
	return (0);
}

static int	parse_line(char *line, int i, int j, t_cub *cub)
{
	if (!line[j])
		return (SUCCESS);
	if (is_starting_point(line[j]))
	{
		if (cub->pos.orientation)
			return (ERR_PARSING);
		cub->pos.start_x = (double)j;
		cub->pos.start_y = (double)i;
		cub->pos.orientation = line[j];
	}
	if (!accepted_chars(line[j]))
		return (ERR_PARSING);
	return (parse_line(line, i, j + 1, cub));
}

static int	parse_map(char **map, int i, t_cub *cub)
{
	if (!map[i] && cub->pos.orientation)
		return (SUCCESS);
	else if (!map[i] && !cub->pos.orientation)
		return (ERR_PARSING);
	if (parse_line(map[i], i, 0, cub) != SUCCESS)
		return (ERR_PARSING);
	return (parse_map(map, i + 1, cub));
}

int	check_elements(t_cub *cub)
{
	return (parse_map(cub->img.map, 0, cub));
}
