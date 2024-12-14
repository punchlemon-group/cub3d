/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:41:15 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/14 17:20:10 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ESC 65307
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
# define A 97
# define W 119
# define S 115
# define D 100

# define PI 3.14159265358979

# define P 4

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>

enum
{
	CNT = 0,
	END,
};

typedef struct s_player
{
	float	x;
	float	y;
	int		angle_deg;
	float	angle_rad;
}	t_player;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	t_player	player;
	char		*addr;
}	t_vars;

void	end(t_vars *vars, int status);
int		key_hook(int keycode, t_vars *vars);
int		window_close(t_vars *vars);

#endif
