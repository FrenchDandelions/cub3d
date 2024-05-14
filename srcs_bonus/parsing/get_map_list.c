/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:58:09 by thole             #+#    #+#             */
/*   Updated: 2024/05/07 13:50:46 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	size_map(t_cub *cub, char **map, int i)
{
	if (!map[i])
	{
		cub->img.map = malloc(sizeof(char *) * (i + 1));
		cub->img.size_map = i + 1;
		if (!cub->img.map)
			return (ERR_MALLOC);
		cub->img.map[0] = NULL;
		return (SUCCESS);
	}
	return (size_map(cub, map, i + 1));
}

static t_map	*next_map(char *str, t_map **map)
{
	(*map)->next = malloc(sizeof(t_map));
	if (!(*map)->next)
		return (ft_delete_list(&(*map)), NULL);
	(*map)->next->prev = *map;
	(*map)->next->line = str;
	(*map)->next->next = NULL;
	return ((*map)->next);
}

static t_map	*new_map(char *str)
{
	t_map	*new_map;

	new_map = malloc(sizeof(t_map));
	if (!new_map)
		return (NULL);
	new_map->line = str;
	new_map->next = NULL;
	new_map->prev = NULL;
	return (new_map);
}

int	get_map(int fd, t_map **map, int *status, t_cub *cub)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (SUCCESS);
	if (!*map)
	{
		*map = new_map(line);
		if (!*map)
			return (ERR_MALLOC);
		cub->map = *map;
	}
	else
	{
		if ((*map)->prev && (*map)->prev->line && ft_strcmp(line, "\n") == 0
			&& (!is_texture((*map)->prev->line) && ft_strcmp((*map)->prev->line,
					"\n")))
			return (*status = 2, ft_memdel(line), SUCCESS);
		(*map) = next_map(line, map);
		if (!(*map))
			return (ERR_MALLOC);
	}
	if (cub->size_list >= 100)
		return (2);
	return (cub->size_list++, get_map(fd, map, status, cub));
}

int	create_map_list(char *map_name, t_cub *cub)
{
	int		fd;
	int		status;
	t_map	*map_list;
	char	**map;

	status = 0;
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		print_error_exit("Error\nCouldn't open the map\n", cub);
	map_list = NULL;
	map = NULL;
	if (get_map(fd, &map_list, &status, cub) != SUCCESS)
		return (ft_delete_list(&cub->map), close(fd), ERR_MALLOC);
	close(fd);
	if (status == 2)
		return (ft_delete_list(&cub->map), print_error_exit(MAP_ERR, cub), 2);
	status = list_to_map(cub->map, cub, &map, 0);
	if (status != SUCCESS)
		return (ERR_MALLOC);
	cub->initial_map = map;
	if (size_map(cub, map, 0) == ERR_MALLOC)
		return (ft_free_tab(map), ERR_MALLOC);
	return (fill_struct(cub, map, 0, 0));
}
