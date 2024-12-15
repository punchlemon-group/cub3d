/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:31:19 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/15 11:14:27 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_player_status(t_player player)
{
	printf("x:%f, y:%f, angle_rad:%f\n", player.x, player.y, player.angle_rad);
}

void	player_move(t_vars *vars)
{
	float	speed;
	int		bias;

	bias = 0;
	speed = 0.0001;
	if (vars->keys[W_ID] != vars->keys[S_ID])
	{
		if (vars->keys[W_ID])
			bias += 90;
		else if (vars->keys[S_ID])
			bias += 270;
	}
	if (vars->keys[A_ID] != vars->keys[D_ID])
	{
		if (vars->keys[A_ID])
			bias += 180;
		if (vars->keys[W_ID] != vars->keys[S_ID])
			bias /= 2;
	}
	if (vars->keys[W_ID] != vars->keys[S_ID]
		|| vars->keys[A_ID] != vars->keys[D_ID])
	{
		vars->player.x += speed * cos(vars->player.angle_rad + bias * PI / 180);
		vars->player.y -= speed * sin(vars->player.angle_rad + bias * PI / 180);
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
	if (vars->last_calc_time)
		printf("%lfHz\n", 1000000.0 / (tmp - vars->last_calc_time));
	vars->last_calc_time = tmp;
	if (!vars->last_disp_time || (tmp - vars->last_disp_time) > 1000000 / FPS)
	{
		vars->last_disp_time = tmp;
		if ((vars->keys[W_ID] != vars->keys[S_ID])
			|| (vars->keys[A_ID] != vars->keys[D_ID])
			|| (vars->keys[RIGHT_ID] != vars->keys[LEFT_ID]))
			print_player_status(vars->player);
		draw_player_2d(vars, 0xff0000);
	}
	return (CNT);
}
