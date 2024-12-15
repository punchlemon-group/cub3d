/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:31:19 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/15 16:15:51 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_player_status(t_player player)
{
	printf("x:%f, y:%f, angle_rad:%f\n", player.x, player.y, player.angle_rad);
}

float	get_bias_rad(int *keys)
{
	float	bias_rad;

	bias_rad = 0.0;
	if (keys[W_ID] != keys[S_ID])
	{
		if (keys[W_ID])
			bias_rad += PI / 2;
		else if (keys[S_ID])
			bias_rad += 3 * PI / 2;
	}
	if (keys[A_ID] != keys[D_ID])
	{
		if (keys[A_ID])
			bias_rad += PI;
		if (keys[W_ID] != keys[S_ID])
			bias_rad = bias_rad / 2.0;
	}
	return (bias_rad);
}

void	player_move(t_vars *vars)
{
	float	speed;
	float	bias_rad;
	double	x_;
	double	y_;

	speed = 0.0001;
	bias_rad = get_bias_rad(vars->keys);
	if (vars->keys[W_ID] != vars->keys[S_ID]
		|| vars->keys[A_ID] != vars->keys[D_ID])
	{
		x_ = vars->player.x + speed * cos(vars->player.angle_rad + bias_rad);
		y_ = vars->player.y - speed * sin(vars->player.angle_rad + bias_rad);
		if ((vars->map)[(int)y_][(int)x_] != '1') // 壁の衝突判定 (ドアも衝突する)
		{
			vars->player.x = x_;
			vars->player.y = y_;
		}
	}
}

void	player_rotate(t_vars *vars)
{
	float	speed;

	speed = 0.0001;
	if (vars->keys[RIGHT_ID] != vars->keys[LEFT_ID])
	{
		if (vars->keys[RIGHT_ID])
			vars->player.angle_rad -= speed;
		if (vars->keys[LEFT_ID])
			vars->player.angle_rad += speed;
	}
}

int	loop_hook(t_vars *vars)
{
	struct timeval	tv;
	long			tmp;

	player_move(vars);
	player_rotate(vars);
	gettimeofday(&tv, NULL);
	tmp = tv.tv_sec * 1000000 + tv.tv_usec;
	// if (vars->last_calc_time)
	// 	printf("%lfHz\n", 1000000.0 / (tmp - vars->last_calc_time));
	vars->last_calc_time = tmp;
	if (!vars->last_disp_time || (tmp - vars->last_disp_time) > 1000000 / FPS)
	{
		printf("%lfHz\n", 1000000.0 / (tmp - vars->last_disp_time));
		vars->last_disp_time = tmp;
		// if ((vars->keys[W_ID] != vars->keys[S_ID])
		// 	|| (vars->keys[A_ID] != vars->keys[D_ID])
		// 	|| (vars->keys[RIGHT_ID] != vars->keys[LEFT_ID]))
		// 	print_player_status(vars->player);
		draw_ceiling(vars, 0x00aaff);
		draw_floor(vars, 0x222222);
		draw_map_2d(vars, 0xdddddd, 0xffff00);
		draw_player_2d(vars, 0xff0000, 0x0000ff);
	}
	return (CNT);
}
