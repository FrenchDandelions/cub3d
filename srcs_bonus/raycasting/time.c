/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testtime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 16:40:44 by thole             #+#    #+#             */
/*   Updated: 2024/04/28 16:40:47 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// int	main(void)
// {
// 	size_t	start;
// 	size_t	time_now;

// 	start = get_current_time();
// 	while (1)
// 	{
// 		time_now = get_current_time();
// 		if (time_now - start >= 300)
// 		{
// 			printf("[%zu] ms reached\n", time_now - start);
// 			start = time_now;
// 		}
// 	}
// }
