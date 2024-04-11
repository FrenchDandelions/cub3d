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
	cub->map = NULL;
	cub->initial_map = NULL;
	cub->past_string = NULL;
	cub->north_texture = NULL;
	cub->south_texture = NULL;
	cub->west_texture = NULL;
	cub->east_texture = NULL;
	cub->floor_color = NULL;
	cub->sky_color = NULL;
	cub->flag_double = 0;
}

void	print_struct(t_cub *cub)
{
	printf("NO :%s\n", cub->north_texture);
	printf("SO :%s\n", cub->south_texture);
	printf("WE :%s\n", cub->west_texture);
	printf("EA :%s\n", cub->east_texture);
	printf("F :%s\n", cub->floor_color);
	printf("C :%s\n", cub->sky_color);
	if (cub->map)
		for (int i = 0; cub->map[i]; i++)
			printf("%s\n", cub->map[i]);
	ft_memdel(cub->north_texture);
	ft_memdel(cub->south_texture);
	ft_memdel(cub->east_texture);
	ft_memdel(cub->west_texture);
	ft_memdel(cub->floor_color);
	ft_memdel(cub->sky_color);
	ft_free_tab(cub->initial_map);
	free(cub->map);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	initialize_struct(&cub);
	if (argc == 2)
	{
		if (!check_name_map(argv[1]))
			return (ft_dprintf(STDERR_FILENO, "Wrong file name\n"), 2);
		printf("Here : %d\n", create_map(argv[1], &cub));
		print_struct(&cub);
		return (0);
	}
	else
		return (ft_dprintf(STDERR_FILENO, "Error, wrong argument count\n"), 2);
}
