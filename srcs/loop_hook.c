/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:31:19 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/18 22:58:33 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_player_status_for_dev(t_vars *vars)
{
	t_player	p;

	if ((vars->keys[W_ID] != vars->keys[S_ID])
		|| (vars->keys[A_ID] != vars->keys[D_ID])
		|| (vars->keys[RIGHT_ID] != vars->keys[LEFT_ID]))
	{
		p = vars->player;
		printf(", x:%f, y:%f, angle_rad:%f", p.x, p.y, p.angle_rad);
	}
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
	float	bias_rad;
	double	x_;
	double	y_;

	bias_rad = get_bias_rad(vars->keys);
	if (vars->keys[W_ID] != vars->keys[S_ID]
		|| vars->keys[A_ID] != vars->keys[D_ID])
	{
		x_ = vars->player.x
			+ MOVE_SPEED * cos(vars->player.angle_rad + bias_rad);
		y_ = vars->player.y
			+ MOVE_SPEED * -sin(vars->player.angle_rad + bias_rad);
		if ((vars->map)[(int)y_][(int)x_] != '1') // 壁の衝突判定 (ドアも衝突する)
		{
			vars->player.x = x_;
			vars->player.y = y_;
		}
	}
}

void	player_rotate(t_vars *vars)
{
	if (vars->keys[RIGHT_ID] != vars->keys[LEFT_ID])
	{
		if (vars->keys[RIGHT_ID])
			vars->player.angle_rad -= ROTATE_SPEED;
		if (vars->keys[LEFT_ID])
			vars->player.angle_rad += ROTATE_SPEED;
		if (vars->player.angle_rad > (2 * PI))
			vars->player.angle_rad -= (2 * PI);
		else if (vars->player.angle_rad < (-2 * PI))
			vars->player.angle_rad += (2 * PI);
	}
}

int	loop_hook(t_vars *vars)
{
	struct timeval	tv;
	long			now;
	float			frame_delta;
	float			event_delta;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec * 1000000 + tv.tv_usec;
	event_delta = 1000000.0 / (now - vars->last_calc_time);
	if (EVENT_HZ > event_delta)
	{
		// printf("event_delta %.2f\n", event_delta);
		vars->event_delta_sum += event_delta;
		vars->event_count++;
		vars->last_calc_time = now;
		player_move(vars);
		player_rotate(vars);
	}
	frame_delta = 1000000.0 / (now - vars->last_disp_time);
	if (FRAME_HZ > frame_delta)
	{
		if (vars->last_disp_time)
		{
			printf("loop: %03d, calc: %.1f[Hz], disp: %.2f[Hz]",
				vars->i, vars->event_delta_sum / vars->event_count, frame_delta);
			print_player_status_for_dev(vars);
			vars->i = 0;
			vars->event_count = 0;
			vars->event_delta_sum = 0;
			printf("\n");
		}
		vars->last_disp_time = now;
		cast_rays(vars);
		draw_ceiling(vars, 0x00aaff);
		draw_floor(vars, 0x222222);
		draw_wall(vars, 0xff0000);
		draw_map_2d(vars, 0xdddddd, 0xffff00);
		draw_player_2d(vars, 0xff0000, 0x0000ff);
		draw_rays_2d(vars, 0x00ff00);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->image_buffer, 0, 0);
	}
	vars->i++;
	return (CNT);
}
