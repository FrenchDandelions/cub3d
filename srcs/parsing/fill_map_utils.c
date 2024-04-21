/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:01:25 by thole             #+#    #+#             */
/*   Updated: 2024/04/11 17:01:27 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_texture(char *s)
{
	if (ft_strncmp(s, "NO ", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "SO ", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "WE ", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "EA ", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "F ", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "C ", 2) == 0)
		return (1);
	return (0);
}

char	*ft_substr_cub3d(char *s, int start, int idx, char *str)
{
	if (s[start + idx] && ft_is_whitespaces(s[start + idx]))
		return (ft_substr_cub3d(s, start, idx + 1, str));
	else if (!s[start + idx])
	{
		if (str)
			return (str);
		return (ft_strdup(""));
	}
	else
	{
		if (str)
			return (str);
		return (ft_substr(s, start + idx, ft_strlen(s) - (start + idx)));
	}
}
