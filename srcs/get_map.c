/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:08:47 by thole             #+#    #+#             */
/*   Updated: 2024/04/11 14:08:49 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	size_map(t_cub *cub, char **map, int i)
{
	if (!map[i])
	{
		cub->map = malloc(sizeof(char *) * (i + 1));
		if (!cub->map)
			return (ERR_MALLOC);
		cub->map[0] = NULL;
		return (SUCCESS);
	}
	return (size_map(cub, map, i + 1));
}

static void	print_error_exit(char *s, t_cub *cub)
{
	ft_dprintf(STDERR_FILENO, "%s\n", s);
	free_all(cub);
	exit(2);
}

static char	*ft_cub_join(char *s1, char *s2)
{
	char	*line;
	size_t	i;
	size_t	len1;
	size_t	len2;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	line = ft_calloc(sizeof(char), (len1 + len2 + 2));
	if (!line)
		return (ft_memdel(s1), NULL);
	ft_gnl_strlcpy(line, s1, len1 + 1);
	ft_gnl_strlcpy(line + len1, s2, len2 + 1);
	free(s1);
	return (line);
}

static int	get_map(int fd, char **str, int *status, t_cub *cub)
{
	char	*line;

	line = get_next_line(fd);
	if (!cub->past_string)
		cub->past_string = line;
	else
	{
		if (line && ft_strcmp(line, "\n") == 0 && (!is_texture(cub->past_string)
				&& ft_strcmp(cub->past_string, "\n")))
			return (*status = 2, ft_memdel(cub->past_string), ft_memdel(line),
				SUCCESS);
		ft_memdel(cub->past_string);
		cub->past_string = line;
	}
	if (!line)
		return (close(fd), SUCCESS);
	if (!(*str))
		*str = ft_strdup(line);
	else if (ft_strcmp(line, "\n"))
		*str = ft_cub_join(*str, line);
	if (!(*str))
		return (ft_memdel(line), ERR_MALLOC);
	return (get_map(fd, &(*str), &(*status), cub));
}

int	create_map(char *map_name, t_cub *cub)
{
	int		fd;
	int		status;
	char	*str;
	char	**map;

	status = 0;
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		print_error_exit("Error, couldn't open the map", cub);
	str = NULL;
	if (get_map(fd, &str, &status, cub) != SUCCESS)
		return (ft_memdel(str), ERR_MALLOC);
	if (status == 2)
		return (ft_memdel(str), print_error_exit(MAP_ERR, cub), 2);
	map = ft_split(str, '\n');
	cub->initial_map = map;
	if (!map)
		return (ft_memdel(str), ERR_MALLOC);
	for (int i = 0; map[i]; i++)
		printf("Coucou : %s\n", map[i]);
	if (size_map(cub, map, 0) == ERR_MALLOC)
		return (ft_free_tab(map), ERR_MALLOC);
	return (free(str), fill_struct(cub, map, 0, 0));
}
