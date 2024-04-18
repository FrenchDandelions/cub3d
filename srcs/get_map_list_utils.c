/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:32:56 by thole             #+#    #+#             */
/*   Updated: 2024/04/18 18:32:57 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_delete_list(t_map **map)
{
	t_map	*copy;

	copy = *map;
	while ((*map))
	{
		copy = (*map)->next;
		ft_memdel((*map)->line);
		ft_memdel(*map);
		*map = copy;
	}
}

void	print_error_exit(char *err, t_cub *cub)
{
	ft_dprintf(STDERR_FILENO, "%s\n", err);
	(void)cub;
}

int	list_to_map(t_map *map, t_cub *cub, char ***new_map, int i)
{
	if (!map)
		return ((*new_map)[i] = NULL, SUCCESS);
	if (!*new_map)
	{
		*new_map = malloc(sizeof(char *) * (cub->size_list + 1));
		if (!*new_map)
			return (ERR_MALLOC);
	}
	(*new_map)[i] = map->line;
	return (list_to_map(map->next, cub, &(*new_map), i + 1));
}