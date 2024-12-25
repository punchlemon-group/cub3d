/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:41:15 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/18 22:56:21by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

# define MOUSE_HZ 1000
# define KEY_HZ 1000
# define FRAME_HZ 60

# define SCREEN_RATIO ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT)

// 60 deg
# define VIEWING_HORIZONTAL_ANGLE_RAD (PI / 3)
# define VIEWING_VERTICAL_ANGLE_RAD (VIEWING_HORIZONTAL_ANGLE_RAD / SCREEN_RATIO)

# define MOVE_SPEED 0.005
# define KEY_ROTATE_SPEED 0.001
# define MOUSE_ROTATE_SPEED 0.001

# define LIGHT_DEAD_LEN_POW_2 256

# define PLAYER_HEIGHT 1.75
# define MAX_JUMP_HEIGHT 0.3
# define BLOCK_HEIGHT 2.5

# define JUMP_TIME 0.2
# define JUMP_FRAME (int)(JUMP_TIME * FRAME_HZ)

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
	NORMAL = 0,
	JUMP,
};

typedef struct s_cordinate
{
	int	x;
	int	y;
}	t_cordinate;

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
	long		last_event_time;
	long		last_mouse_time;
	long		last_frame_time;
	int			i;
	int			event_count;
	float		event_delta_sum;
	int			map_width;
	int			map_height;
	t_player	player;
	const char	*addr;
	long		last_key_press_time[KEY_NUM];
	long		last_key_release_time[KEY_NUM];
	int			keys[KEY_NUM];
	t_ray		rays[WINDOW_WIDTH];
	t_cordinate	mouse;
	int			is_in_mouse;
	int			last_key_m;
	int			is_map;
}	t_vars;

void	ft_pixel_put_to_image(t_vars *vars, int color, t_cordinate c);
void	ft_circle_put_to_image(t_vars *vars, int color, t_cordinate c, int r);
void	ft_square_put_to_image(t_vars *vars, int color, t_cordinate c, int a);
void	ft_rectangle_put_to_image(t_vars *vars, int color, t_cordinate c,
	t_cordinate len);

void	cast_rays(t_vars *vars);
int		dark_color(int color, float len);
void	draw_background(t_vars *vars, int ceiling_color, int floor_color);
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
void	player_rotate_for_mouse(t_vars *vars, t_cordinate *new);

#endif
