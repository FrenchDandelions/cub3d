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
# include "../minilibx-linux/mlx.h"

# define SUCCESS 7
# define FAILURE 0
# define ERR_MALLOC -2
# define ERR_PARSING 2
# define MAP_ERR "Error\nThe map isn't properly formatted"

typedef struct s_img
{
	void			*north;
	void			*south;
	void			*west;
	void			*east;
	char			**map;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*floor_color;
	char			*sky_color;
	int				width;
	int				height;
	int				size_map;
}					t_img;

/*
p = map[y][x];

.............x......
....................
y............p......
....................
*/

typedef struct s_pos
{
	char			orientation;
	int				start_x;
	int				start_y;
}					t_pos;

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
	struct s_map	*prev;
}					t_map;

typedef struct s_cub
{
	char			**initial_map;
	char			*past_string;
	void			*mlx_ptr;
	void			*mlx_win;
	int				size_list;
	t_map			*map;
	t_img			img;
	t_pos			pos;
}					t_cub;

bool				check_name_map(char *s);
int					fill_struct(t_cub *cub, char **map, int i, int j);
char				*ft_substr_cub3d(char *s, int start, int index, char *str);
int					is_texture(char *s);
void				print_map(t_cub *cub);
void				free_all(t_cub *cub);
int					check_elements(t_cub *cub);
int					check_access(char **map, int size_map, int i);
int					create_map_list(char *map_name, t_cub *cub);
void				ft_delete_list(t_map **map);
int					list_to_map(t_map *map, t_cub *cub, char ***new_map, int i);
void				print_error_exit(char *err, t_cub *cub);

#endif
