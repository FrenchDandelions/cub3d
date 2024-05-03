/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:37:08 by thole             #+#    #+#             */
/*   Updated: 2023/11/13 11:37:09 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		if (!s[i + 1])
			return (i + 1);
		else if (!s[i + 2])
			return (i + 2);
		else if (!s[i + 3])
			return (i + 3);
		else if (!s[i + 4])
			return (i + 4);
		else if (!s[i + 5])
			return (i + 5);
		else if (!s[i + 6])
			return (i + 6);
		else if (!s[i + 7])
			return (i + 7);
		else if (!s[i + 8])
			return (i + 8);
		i += 8;
	}
	return (i);
}
