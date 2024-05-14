/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:28:33 by thole             #+#    #+#             */
/*   Updated: 2024/04/21 16:28:36 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_atoi_rgb(char *str, int *index, int *flag)
{
	int	num;

	if (!str[*index])
		return (*flag = 1, -1);
	num = 0;
	while (ft_is_whitespaces(str[*index]))
		(*index)++;
	if (!str[*index] || !ft_isdigit(str[*index]))
		return (*flag = 1, -1);
	while (str[*index] && ft_isdigit(str[*index]))
	{
		num = num * 10 + (str[*index] - 48);
		if (num > 255)
			return (*flag = 1, -1);
		(*index)++;
	}
	while (str[*index] && ft_is_whitespaces(str[*index]))
		(*index)++;
	if (str[*index] && str[*index] != ',')
		return (*flag = 1, -1);
	return (num);
}
