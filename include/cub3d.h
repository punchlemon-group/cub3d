/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:41:15 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/18 15:06:41 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ESC 65307
// # define UP 65362
# define LEFT 65361
// # define DOWN 65364
# define RIGHT 65363
# define W 119
# define A 97
# define S 115
# define D 100

# define PI 3.14159265358979

# define P 4

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define X_BUTTON 17

# define KEY_NUM 6

# define LITTLE_ENDIAN 0

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define MAP_SCALE 20
# define PLAYER_SIZE 5

# define EVENT_HZ 1000
# define FRAME_HZ 60

# define VIEWING_ANGLE_RAD PI / 3

# define MOVE_SPEED 0.005
# define ROTATE_SPEED 0.01

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
	W_ID,
	A_ID,
	S_ID,
	D_ID,
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
	float	angle_rad;
}	t_player;

typedef struct s_ray
{
	t_img	*img; // 描画するべきimage
	int		x; // imageのx番目の列のピクセルたちを持ってくる
	float	len;
}	t_ray;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_img		*image_buffer;
	t_player	player;
	char		*addr;
	long		last_calc_time;
	long		last_disp_time;
	char		**map;
	int			map_width;
	int			map_height;
	t_img		*north;
	t_img		*east;
	t_img		*west;
	t_img		*south;
	int			keys[KEY_NUM];
	t_ray		rays[WINDOW_WIDTH];
	int			i;
	float		event_delta_sum;
	int			event_count;
}	t_vars;

void	ft_pixel_put_to_image(t_vars *vars, int color, t_cordinate c);
void	ft_circle_put_to_image(t_vars *vars, int color, t_cordinate c, int r);
void	ft_square_put_to_image(t_vars *vars, int color, t_cordinate c, int a);
void	ft_rectangle_put_to_image(t_vars *vars, int color, t_cordinate c,
	t_cordinate len);
void	cast_rays(t_vars *vars);
void	draw_ceiling(t_vars *vars, int color);
void	draw_floor(t_vars *vars, int color);
void	draw_map_2d(t_vars *vars, int floor_color, int wall_color);
void	draw_player_2d(t_vars *vars, int base_color, int nose_color);
void	draw_rays_2d(t_vars *vars, int color);
void	end(t_vars *vars, int status);
int		window_close(t_vars *vars);
int		loop_hook(t_vars *vars);
int		key_press(int key, t_vars *vars);
int		key_release(int key, t_vars *vars);

#endif
