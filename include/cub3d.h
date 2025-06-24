/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:41:15 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/24 13:28:01 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MAX_MAP_WIDTH 100
# define MAX_MAP_HEIGHT 100

# define ESC 65307
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363
# define W 119
# define A 97
# define S 115
# define D 100
# define M 109

# define PI 3.14159265358979323846
# define TPI 6.28318530717958647692

# define P 4

# define KEY_NUM 9

# define LITTLE_ENDIAN 0

# define WINDOW_WIDTH 960
# define WINDOW_HEIGHT 540
# define MAP_SCALE 10
# define PLAYER_SIZE 5

# define ONE_SEC_FOR_USEC 1000000.0
# define MOUSE_HZ 1000
# define KEY_HZ 1000
# define FRAME_HZ 60

// # define SCREEN_RATIO (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT
# define SCREEN_RATIO 1.7777777777777777778

# define PLAYER_RADIUS 0.2

// 60 deg
# define VIEWING_HORIZONTAL_ANGLE_RAD 1.047197551196598

// (VIEWING_HORIZONTAL_ANGLE_RAD / SCREEN_RATIO)
# define VIEWING_VERTICAL_ANGLE_RAD 0.589048622548086

# define KEY_MOVE_SPEED 5
# define KEY_ROTATE_SPEED 1
# define MOUSE_ROTATE_SPEED 0.001
# define MOUSE_ROTATE_SPEED_EVENT 0.005
# define SHORTEST_CONSECUTIVE_PRESS_USEC 100

# define LIGHT_DEAD_LEN_POW_2 256

# define PLAYER_HEIGHT 1.75
# define MAX_JUMP_HEIGHT 0.3
# define BLOCK_HEIGHT 2.5

# define JUMP_TIME 0.2

//(int)(JUMP_TIME * FRAME_HZ)
# define JUMP_FRAME 12

# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include "mlx_int.h"
# include <math.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>

enum
{
	CNT = 0,
	END,
};

enum
{
	LEFT_ID = 0,
	RIGHT_ID,
	UP_ID,
	DOWN_ID,
	W_ID,
	A_ID,
	S_ID,
	D_ID,
	M_ID,
};

enum
{
	OK = 0,
	TOO_SHORT,
	NO_EXTENTION,
};

enum
{
	NORMAL = 0,
	JUMP,
};

typedef struct s_colors
{
	int	ceiling;
	int	floor;
}	t_colors;

typedef struct s_ipoint
{
	int	x;
	int	y;
}	t_pnt_i;

typedef struct s_fpoint
{
	float	x;
	float	y;
}	t_pnt_f;

typedef struct s_player
{
	float	x;
	float	y;
	float	z;
	float	angle_rad;
	int		status;
}	t_player;

typedef struct s_ray
{
	t_img	*img;
	int		x;
	float	len;
}	t_ray;

typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color[3];
	int		ceil_color[3];
	int		has_no;
	int		has_so;
	int		has_we;
	int		has_ea;
	int		has_floor;
	int		has_ceil;
}	t_config;

typedef struct s_parse_data
{
	char	**raw_map;
	char	*error_msg;
	int		height;
	int		max_width;
	int		in_map_section;
}	t_parse_data;

typedef struct s_vars
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_img		*north;
	t_img		*east;
	t_img		*west;
	t_img		*south;
	t_img		*image_buffer;
	char		**map;
	t_config	config;
	int			width;
	int			height;
	long		last_event_time;
	long		last_mouse_time;
	long		last_frame_time;
	int			map_width;
	int			map_height;
	t_player	player;
	const char	*addr;
	int			keys[KEY_NUM];
	t_ray		rays[WINDOW_WIDTH];
	t_pnt_i		mouse;
	int			is_in_mouse;
	int			last_key_m;
	int			is_map;
}	t_vars;

typedef struct s_wall_draw_vars
{
	int		j;
	int		limit;
	t_pnt_i	head;
	float	y;
	float	d_y;
}	t_wall_draw_vars;

typedef struct s_ray_params
{
	int		d_x;
	int		x_int;
	float	d_y;
	int		d_y_h;
	int		y_int;
	float	d_x_h;
}	t_ray_params;

void	ft_pixel_put_to_image(t_vars *vars, int color, t_pnt_i c);
void	ft_circle_put_to_image(t_vars *vars, int color, t_pnt_i c, int r);
void	ft_square_put_to_image(t_vars *vars, int color, t_pnt_i c, int a);
void	ft_rectangle_put_to_image(t_vars *vars, int color, t_pnt_i c,
			t_pnt_i len);

void	slide_along_corner(t_pnt_f *p, float corner_x, float corner_y);
float	get_bias_rad(int *keys);
void	check_corner(t_vars *vars, t_pnt_f *p);
void	handle_key_event(t_vars *vars, long now);
void	cast_rays(t_vars *vars);
int		dark_color(int color, float len);
void	draw_background(t_vars *vars, t_colors colors);
void	draw_map_2d(t_vars *vars, int floor_color, int wall_color);
void	draw_player_2d(t_vars *vars, int base_color, int nose_color);
void	draw_rays_2d(t_vars *vars, int color);
void	draw_wall(t_vars *vars);
void	end(t_vars *vars, int status, const char *message);
int		get_img_color(t_img *img, int x, int y);
char	**get_map(const char *file);
long	gettime(void);
int		window_close(t_vars *vars);
int		loop_hook(t_vars *vars);
int		key_press(int key, t_vars *vars);
int		key_release(int key, t_vars *vars);
// int		mouse_move(int x, int y, t_vars *vars);
void	mouse_event(t_vars *vars);
void	player_rotate_for_mouse(t_vars *vars, t_pnt_i *new);
// init functions
int		is_valid_filename(const char *src, const char *extention);
void	check_args(int argc, char **argv, t_vars *vars);
void	create_tiles(t_vars *vars);
void	init(t_vars *vars);
// Parse functions
void	validation_and_parse(int argc, char **argv, t_vars *vars);
void	parse_cub_file(char *file_path, t_vars *vars);
void	error_message_and_free(t_vars *vars, char *message, int exit_code);
void	error_message_and_free_with_line(t_vars *vars, char *message,
			char *line, int exit_code);
int		is_valid_extension(char *filename);
void	initialize_config(t_vars *vars);
void	handle_config_error(char *line, int fd, t_vars *vars, char *error_msg);
int		validate_all_configs(t_vars *vars);
int		handle_duplicate_config(int has_config, char **error_msg, char *value);
int		parse_config_line(char *line, t_config *config, char **error_msg);
int		process_config_by_type(t_config *config, int type, char *value,
			char **error_msg);
int		handle_no_config(t_config *config, char *value, char **error_msg);
int		handle_so_config(t_config *config, char *value, char **error_msg);
int		handle_we_config(t_config *config, char *value, char **error_msg);
int		handle_ea_config(t_config *config, char *value, char **error_msg);
int		handle_floor_config(t_config *config, char *value, char **error_msg);
int		handle_ceil_config(t_config *config, char *value, char **error_msg);
int		is_valid_texture_path(char *path, char **error_msg);
int		validate_color_count(char **parts, char **error_msg);
int		validate_color_value(char *part, int *color_val, char **error_msg);
int		start_map_section(char *line, t_parse_data *data, t_vars *vars);
void	process_map_line(t_vars *vars, char **line, t_parse_data *data);
int		is_valid_map_line(char *line);
int		is_map_enclosed(char **map, int height, int width);
int		validate_player_position(char **map, int height, int width,
			int *player_count);
void	finalize_parsing(t_vars *vars, t_parse_data *data);
char	**allocate_raw_map(void);
void	cleanup_raw_map(char **raw_map, int height);
void	parse_file_content(int fd, t_vars *vars, t_parse_data *data);
void	handle_empty_line(char *line, int in_map_section, t_vars *vars,
			t_parse_data *data);
void	process_not_map_line(t_vars *vars, char *line, t_parse_data *data,
			int fd);
void	init_vparam(t_vars *v, float a, t_ray *r, t_ray_params *p);
void	init_hparam(t_vars *v, float a, t_ray *r, t_ray_params *p);
int		vloop(t_vars *v, float a, t_ray *r, t_ray_params *p);
int		hloop(t_vars *v, float a, t_ray *r, t_ray_params *p);

#endif
