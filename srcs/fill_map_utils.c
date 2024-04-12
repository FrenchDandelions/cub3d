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

char	*ft_substr_cub3d(char *s, int start, int index, char *str)
{
	if (s[start + index] && ft_is_whitespaces(s[start + index]))
		return (ft_substr_cub3d(s, start, index + 1, str));
	else if (!s[start + index])
	{
		if (str)
			return (str);
		return (ft_strdup(""));
	}
	else
	{
		if (str)
			return (str);
		return (ft_substr(s, start + index, ft_strlen(s) - (size_t)(start
					+ index)));
	}
}
