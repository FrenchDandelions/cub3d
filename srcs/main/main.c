/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:08:39 by thole             #+#    #+#             */
/*   Updated: 2024/04/11 14:08:40 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	initialize_struct(t_cub *cub)
{
	cub->img.map = NULL;
	cub->initial_map = NULL;
	cub->past_string = NULL;
	cub->img.north_texture = NULL;
	cub->img.south_texture = NULL;
	cub->img.west_texture = NULL;
	cub->img.east_texture = NULL;
	cub->img.floor_color = NULL;
	cub->img.sky_color = NULL;
	cub->img.north = NULL;
	cub->img.south = NULL;
	cub->img.west = NULL;
	cub->img.east = NULL;
	cub->img.width = 64;
	cub->img.height = 64;
	cub->img.size_map = 0;
	cub->size_list = 0;
	cub->pos.orientation = '\0';
	cub->pos.start_x = -1;
	cub->pos.start_y = -1;
	cub->status = 0;
}

void	print_map(t_cub *cub)
{
	printf("NO :%s\n", cub->img.north_texture);
	printf("SO :%s\n", cub->img.south_texture);
	printf("WE :%s\n", cub->img.west_texture);
	printf("EA :%s\n", cub->img.east_texture);
	printf("F :%s\n", cub->img.floor_color);
	printf("C :%s\n", cub->img.sky_color);
	if (cub->img.map)
		for (int i = 0; cub->img.map[i]; i++)
			printf("%s\n", cub->img.map[i]);
	printf("Pos x: %d, Pos y : %d\n", cub->pos.start_x, cub->pos.start_y);
	if (cub->pos.start_x != -1)
		printf("Char postion : %c\n",
			cub->img.map[cub->pos.start_x][cub->pos.start_y]);
}

void	free_all(t_cub *cub)
{
	ft_memdel(cub->img.north_texture);
	ft_memdel(cub->img.south_texture);
	ft_memdel(cub->img.east_texture);
	ft_memdel(cub->img.west_texture);
	ft_memdel(cub->img.floor_color);
	ft_memdel(cub->img.sky_color);
	ft_memdel(cub->img.north);
	ft_memdel(cub->img.south);
	ft_memdel(cub->img.west);
	ft_memdel(cub->img.east);
	ft_memdel(cub->initial_map);
	ft_memdel(cub->img.map);
	ft_delete_list(&cub->map);
}

void	print_and_free_struct(t_cub *cub)
{
	print_map(cub);
	free_all(cub);
}

void	print_err(int err)
{
	if (err == ERR_PARSING)
		ft_dprintf(STDERR_FILENO, "%s\n", MAP_ERR);
	if (err == ERR_MALLOC)
		ft_dprintf(STDERR_FILENO, "Error\nMalloc\n");
	if (err == FAILURE)
		ft_dprintf(STDERR_FILENO, "Error\nThe map isn't surrounded by walls\n");
	if (err == ERR_CLR_F)
		ft_dprintf(STDERR_FILENO,
			"Error\nThe floor color isn't properly formatted\n");
	if (err == ERR_CLR_S)
		ft_dprintf(STDERR_FILENO,
			"Error\nThe sky color isn't properly formatted\n");
}

void	print_map_list(t_cub *cub)
{
	t_map	*copy;

	copy = cub->map;
	while (copy)
	{
		printf("Coucou : %s\n", copy->line);
		copy = copy->next;
	}
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		status;

	initialize_struct(&cub);
	if (argc == 2)
	{
		if (!check_name_map(argv[1]))
			return (ft_dprintf(STDERR_FILENO, "Error\nWrong file name\n"), 2);
		status = create_map_list(argv[1], &cub);
		if (status != SUCCESS && status != 0)
			return (print_err(status), free_all(&cub), status);
		// print_map_list(&cub);
		status = check_elements(&cub);
		if (status != SUCCESS)
			return (print_err(status), free_all(&cub), status);
		status = check_access(cub.img.map, cub.img.size_map, 0);
		if (status != SUCCESS)
			return (print_err(status), free_all(&cub), status);
		status = check_rgb(&cub);
		if (status != SUCCESS)
			return (print_err(status), free_all(&cub), status);
		print_map(&cub);
		init_mlx(&cub);
		// free_all(&cub);
		return (0);
	}
	else
		return (ft_dprintf(STDERR_FILENO, "Error\nWrong argument count\n"), 2);
}
