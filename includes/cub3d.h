/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:11:48 by thole             #+#    #+#             */
/*   Updated: 2024/04/11 14:11:49 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"

# define SUCCESS 7
# define ERR_MALLOC -2

typedef struct s_cub
{
	char	**initial_map;
	char	*past_string;
	char	**map;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	char	*floor_color;
	char	*sky_color;
	int		flag_double;
}			t_cub;

int			create_map(char *map_name, t_cub *cub);
bool		check_name_map(char *s);
int			fill_struct(t_cub *cub, char **map, int i, int j);
char		*ft_substr_cub3d(char *s, int start, int index, char *str);
int			is_texture(char *s);

#endif
