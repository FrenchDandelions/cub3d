/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:04:07 by thole             #+#    #+#             */
/*   Updated: 2024/04/11 16:04:08 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	check_name_map(char *s)
{
	char	*cub_name;
	size_t	end;
	size_t	end_cub;

	cub_name = ".cub";
	end = ft_strlen(s) - 1;
	end_cub = ft_strlen(cub_name) - 1;
	if (end == end_cub && ft_strcmp(cub_name, s) == 0)
		return (0);
	while (end > 0 && end_cub > 0 && s[end] == cub_name[end_cub])
	{
		end--;
		end_cub--;
	}
	if (end_cub)
		return (false);
	return (true);
}
