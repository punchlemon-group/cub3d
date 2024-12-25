/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:31:19 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/25 13:08:08 by retanaka         ###   ########.fr       */
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
		{
			bias_rad = bias_rad / 2.0;
			if (keys[S_ID] && keys[D_ID])
				bias_rad = -PI / 4;
		}
	}
	return (bias_rad);
}

void	player_move(t_vars *vars, float key_delta)
{
	float	bias_rad;
	double	x_;
	double	y_;

	bias_rad = get_bias_rad(vars->keys);
	if (vars->keys[W_ID] != vars->keys[S_ID]
		|| vars->keys[A_ID] != vars->keys[D_ID])
	{
		x_ = vars->player.x + MOVE_SPEED
			* cos(vars->player.angle_rad + bias_rad) * (float)KEY_HZ / key_delta;
		y_ = vars->player.y + MOVE_SPEED
			* -sin(vars->player.angle_rad + bias_rad) * (float)KEY_HZ / key_delta;
		if ((vars->map)[(int)y_][(int)x_] != '1') // 壁の衝突判定 (ドアも衝突する) // すりぬけをなんとかする
		{
			vars->player.x = x_;
			vars->player.y = y_;
		}
	}
}

void	player_rotate_for_key(t_vars *vars, float key_delta)
{
	if (vars->keys[RIGHT_ID] != vars->keys[LEFT_ID])
	{
		if (vars->keys[RIGHT_ID])
			vars->player.angle_rad -= KEY_ROTATE_SPEED * (float)KEY_HZ / key_delta;
		if (vars->keys[LEFT_ID])
			vars->player.angle_rad += KEY_ROTATE_SPEED * (float)KEY_HZ / key_delta;
		if (vars->player.angle_rad > (2 * PI))
			vars->player.angle_rad -= (2 * PI);
		else if (vars->player.angle_rad < (-2 * PI))
			vars->player.angle_rad += (2 * PI);
	}
}

void	release_check(t_vars *vars, long now)
{
	long	last_key_release_time;
	int		i;

	i = 0;
	while (i < KEY_NUM)
	{
		if (vars->keys[i] == 1)
		{
			last_key_release_time = vars->last_key_release_time[i];
			if (vars->last_key_press_time[i] < last_key_release_time
				&& now > 1000 + last_key_release_time)
				vars->keys[i] = 0;
		}
		i++;
	}
}

int	loop_hook(t_vars *vars)
{
	long			now;
	float			frame_delta;
	float			mouse_delta;
	float			key_delta;

	now = gettime();
	release_check(vars, now);
	mouse_delta = 1000000.0 / (now - vars->last_mouse_time);
	if (MOUSE_HZ > mouse_delta)
	{
		mouse_event(vars);
		vars->last_mouse_time = now;
	}
	key_delta = 1000000.0 / (now - vars->last_event_time);
	if (KEY_HZ > key_delta)
	{
		// vars->event_delta_sum += key_delta;
		// vars->event_count++;
		if (vars->last_key_m == 0 && vars->keys[M_ID] == 1)
			vars->is_map = !vars->is_map;
		vars->last_key_m = vars->keys[M_ID];
		player_move(vars, key_delta);
		player_rotate_for_key(vars, key_delta);
		vars->last_event_time = now;
	}
	frame_delta = 1000000.0 / (now - vars->last_frame_time);
	if (FRAME_HZ > frame_delta)
	{
		// if (vars->last_frame_time)
		// {
		// 	printf("loop: %03d, calc: %.1f[Hz], disp: %.2f[Hz]",
		// 		vars->i, vars->event_delta_sum / vars->event_count, frame_delta);
		// 	print_player_status_for_dev(vars);
		// 	vars->i = 0;
		// 	vars->event_count = 0;
		// 	vars->event_delta_sum = 0;
		// 	printf("\n");
		// }
		cast_rays(vars);
		draw_background(vars, 0x36300c, 0x222222);
		draw_wall(vars);
		if (vars->is_map)
		{
			draw_map_2d(vars, 0xcb996e, 0xf1c189);
			draw_player_2d(vars, 0xffff00, 0xff0000);
			draw_rays_2d(vars, 0x00ff00);
		}
		mlx_put_image_to_window(vars->mlx, vars->win, vars->image_buffer, 0, 0);
		vars->last_frame_time = now;
	}
	// vars->i++;
	return (CNT);
}
