/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:11:48 by thole             #+#    #+#             */
/*   Updated: 2024/05/16 14:32:43 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <sys/time.h>

# define SUCCESS 7
# define FAILURE 0
# define ERR_MALLOC -2
# define ERR_PARSING 2
# define ERR_STACK 3
# define MAP_ERR "Error\nThe map isn't properly formatted"
# define ERR_TEXTURE "Error\nCould not load texture"
# define ERR_CLR_F -7
# define ERR_CLR_S -8
# define MAP_HEIGHT 1080
# define MAP_WIDTH 1920
# define RED 0xFF0000
# define GOLD 0xFFD700
# define BLUE 0x0000FF
# define GREEN 0x7CFC00
# define PINK 0x1ABC9C
# define NORTH GREEN
# define SOUTH PINK
# define EAST GOLD
# define WEST BLUE
# define ROT 0.2
# define MOV 0.4
# define DOOR_NUMBER 11
# define DNBR DOOR_NUMBER
# define DOOR_ZERO "./assets/doors/door0.xpm"
# define DOOR_ONE "./assets/doors/door1.xpm"
# define DOOR_TWO "./assets/doors/door2.xpm"
# define DOOR_THREE "./assets/doors/door3.xpm"
# define DOOR_FOUR "./assets/doors/door4.xpm"
# define DOOR_FIVE "./assets/doors/door5.xpm"
# define DOOR_SIX "./assets/doors/door6.xpm"
# define DOOR_SEVEN "./assets/doors/door7.xpm"
# define DOOR_EIGHT "./assets/doors/door8.xpm"
# define DOOR_NINE "./assets/doors/door9.xpm"
# define DOOR_TEN "./assets/doors/door10.xpm"

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
	int				rgb_floor[3];
	int				rgb_sky[3];
	int				endian;
	void			*img_floor;
	void			*img_sky;
	int				pixel_bits;
	int				line_bytes;
	char			*buffer;
	int				pixel;
	int				ray_bpp;
	int				ray_lb;
	int				ray_end;
	void			*curr_door;
	void			*doors[DOOR_NUMBER];
	bool			is_animating;
}					t_img;

/*
p = map[x][y];

.............y......
....................
x............p......
....................
*/

typedef struct s_pos
{
	char			orientation;
	double			start_x;
	double			start_y;
}					t_pos;

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
	struct s_map	*prev;
}					t_map;

typedef struct s_ray
{
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			time;
	double			oldtime;
	double			camera_x;
	double			width_screen;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			move_speed;
	double			rot_speed;
	double			old_dir_x;
	double			old_plane_x;
	double			frame_time;
	int				color;
	int				tex_y;
	double			tot_dist;
	int				lh;
	double			step;
	char			*picked_img;
}					t_ray;

typedef struct s_mouse
{
	int				x;
	int				y;
	int				show;
}					t_mouse;

typedef struct s_minimap
{
	size_t			size_map;
	size_t			max_len;
	int				impossible;
	int				show;
	int				color_wall;
	int				color_player;
	int				color_floor;
	int				cl_pk;
	int				color_door_open;
	int				color_door_closed;
	int				color_door_animation;
}					t_minimap;

typedef struct s_cub
{
	char			**initial_map;
	char			*past_string;
	void			*mlx_ptr;
	void			*mlx_win;
	int				size_list;
	int				status;
	t_map			*map;
	t_img			img;
	t_pos			pos;
	t_ray			ray;
	t_mouse			m;
	size_t			timestamp;
	size_t			timestamp2;
	int				frame;
	int				pos_x;
	int				pos_y;
	int				order;
	t_minimap		mmap;
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
int					ft_atoi_rgb(char *str, int *index, int *flag);
int					check_rgb(t_cub *cub);
int					get_color(int *colors);
void				init_mlx(t_cub *cub);
void				free_and_exit(t_cub *cub);
int					calculate_ray(t_cub *cub);
void				find_color(t_cub *cub);
int					set_pixel_color(int face, t_cub *cub, double tex_pos,
						char *img);
void				move_up(t_cub *cub);
void				move_down(t_cub *cub);
void				move_left(t_cub *cub);
void				move_right(t_cub *cub);
void				rotate_left(t_cub *cub);
void				rotate_right(t_cub *cub);
void				right_arrow(t_cub *cub);
void				left_arrow(t_cub *cub);
void				handle_step(t_cub *cub);
void				calculate_delta(t_cub *cub);
void				get_imgs(t_cub *cub, void *img, int color, int color2);
int					handle_cross(t_cub *cub);
int					handle_key(int code, t_cub *cub);
int					handle_mouse(int x, int y, t_cub *cub);
int					ray_loop(t_cub *cub);
void				*init_img(t_cub *cub, char *texture_path);
void				init_doors(t_cub *cub);
void				free_image(void **image, t_cub *cub);
void				free_doors(t_cub *cub);
void				space_bar(t_cub *cub);
size_t				get_current_time(void);
void				check_animation(t_cub *cub, int order);
void				anima(t_cub *cub, int pos_y, int pos_x);
void				reverse_anima(t_cub *cub, int pos_y, int pos_x);
void				initialize_minimap_values(t_cub *cub);
void				change_mmap_values(t_cub *cub);
void				change_mouse_values(t_cub *cub);
void				add_mmap(t_cub *cub);

#endif
