/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:51:18 by thole             #+#    #+#             */
/*   Updated: 2024/04/16 19:51:19 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dup_array(char **array, int size)
{
	char	**dup;
	int		i;

	dup = malloc(sizeof(char *) * size);
	if (!dup)
		return (NULL);
	i = 0;
	while (array[i])
	{
		dup[i] = ft_strdup(array[i]);
		if (!dup[i])
			return (ft_free_tab(dup), NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
