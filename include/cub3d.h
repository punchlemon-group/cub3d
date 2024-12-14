/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:41:15 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/14 21:32:06 by retanaka         ###   ########.fr       */
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

# define FRESH_RATE 50

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

typedef struct s_player
{
	double	x;
	double	y;
	float	angle_rad;
}	t_player;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_img		*image_buffer;
	int			width;
	int			height;
	t_player	player;
	char		*addr;
	int			keys[KEY_NUM];
}	t_vars;

void	ft_pixel_put_to_image(t_vars *vars, int color, int x, int y);
void	draw_player_2d(t_vars *vars, int color);
void	end(t_vars *vars, int status);
// int		key_hook(int keycode, t_vars *vars);
int		window_close(t_vars *vars);
int		loop_hook(t_vars *vars);
int		key_press(int key, t_vars *vars);
int		key_release(int key, t_vars *vars);

#endif
