/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:31:19 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/30 17:35:09 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_player_status_for_dev(t_vars *vars)
{
	t_player	p;

	// if ((vars->keys[W_ID] != vars->keys[S_ID])
	// 	|| (vars->keys[A_ID] != vars->keys[D_ID])
	// 	|| (vars->keys[RIGHT_ID] != vars->keys[LEFT_ID]))
	// {
		p = vars->player;
		printf(", x:%f, y:%f, angle_rad:%f", p.x, p.y, p.angle_rad);
	// }
}

float	get_bias_rad(int *keys)
{
	float	bias_rad;

	bias_rad = 0.0;
	if (keys[A_ID] != keys[D_ID])
	{
		if (keys[A_ID])
			bias_rad += PI / 2;
		else if (keys[D_ID])
			bias_rad += 3 * PI / 2;
	}
	if (keys[W_ID] != keys[S_ID])
	{
		if (keys[S_ID])
			bias_rad += PI;
		if (keys[A_ID] != keys[D_ID])
		{
			bias_rad = bias_rad / 2.0;
			if (keys[W_ID] && keys[D_ID])
				bias_rad = 7 * PI / 4;
		}
	}
	return (bias_rad);
}

int	check_y(t_vars *vars, t_pnt_f *p)
{
	float	now_y_frac;

	now_y_frac = vars->player.y - (int)vars->player.y;
	if (now_y_frac + p->y < PLAYER_RADIUS
		&& vars->map[(int)vars->player.y - 1][(int)vars->player.x] == '1')
		p->y = PLAYER_RADIUS - now_y_frac;
	else if (now_y_frac + p->y > 1 - PLAYER_RADIUS
		&& vars->map[(int)vars->player.y + 1][(int)vars->player.x] == '1')
		p->y = 1 - PLAYER_RADIUS - now_y_frac;
	else
		return (0);
	return (1);
}

int	check_x(t_vars *vars, t_pnt_f *p)
{
	float	now_x_frac;

	now_x_frac = vars->player.x - (int)vars->player.x;
	if (now_x_frac + p->x < PLAYER_RADIUS
		&& vars->map[(int)vars->player.y][(int)vars->player.x - 1] == '1')
		p->x = PLAYER_RADIUS - now_x_frac;
	else if (now_x_frac + p->x > 1 - PLAYER_RADIUS
		&& vars->map[(int)vars->player.y][(int)vars->player.x + 1] == '1')
		p->x = 1 - PLAYER_RADIUS - now_x_frac;
	else
		return (0);
	return (1);
}

void	slide_along_corner(t_pnt_f *p, float corner_x, float corner_y)
{
	float	corner_len;
	float	dot_product;
	float	projection_x;
	float	projection_y;
	float	original_speed;

	// 元の移動速度を保存
	original_speed = sqrt(p->x * p->x + p->y * p->y);
	if (original_speed < 0.001f)
		return;

	// 角の位置ベクトルの長さを計算
	corner_len = sqrt(corner_x * corner_x + corner_y * corner_y);
	if (corner_len < 0.001f)
	{
		p->x = 0;
		p->y = 0;
		return;
	}
	
	// 角の法線ベクトル（正規化）
	corner_x /= corner_len;
	corner_y /= corner_len;
	
	// 移動ベクトルと法線ベクトルの内積
	dot_product = p->x * corner_x + p->y * corner_y;
	
	// 角に向かう成分のみを除去（角から離れる方向は残す）
	if (dot_product > 0)
	{
		projection_x = dot_product * corner_x;
		projection_y = dot_product * corner_y;
		
		p->x -= projection_x;
		p->y -= projection_y;
		
		// 滑り移動の速度を元の速度の一定割合に調整
		float slide_speed = sqrt(p->x * p->x + p->y * p->y);
		if (slide_speed > 0.001f)
		{
			float speed_ratio = original_speed * 0.8f / slide_speed;
			p->x *= speed_ratio;
			p->y *= speed_ratio;
		}
	}
}

void	check_corner(t_vars *vars, t_pnt_f *p)
{
	float	x_;
	float	y_;
	float	radius_2;
	float	x_2;
	float	y_2;

	x_ = vars->player.x - (int)vars->player.x + p->x;
	y_ = vars->player.y - (int)vars->player.y + p->y;
	x_2 = x_ * x_;
	y_2 = y_ * y_;
	radius_2 = PLAYER_RADIUS * PLAYER_RADIUS;
	
	// 左上の角
	if (x_2 + y_2 < radius_2)
	{
		if (vars->map[(int)vars->player.y - 1][(int)vars->player.x - 1] == '1')
			slide_along_corner(p, x_, y_);
	}
	// 左下の角
	else if (x_2 + (1 - y_) * (1 - y_) < radius_2)
	{
		if (vars->map[(int)vars->player.y + 1][(int)vars->player.x - 1] == '1')
			slide_along_corner(p, x_, y_ - 1);
	}
	// 右上の角
	else if ((1 - x_) * (1 - x_) + y_2 < radius_2)
	{
		if (vars->map[(int)vars->player.y - 1][(int)vars->player.x + 1] == '1')
			slide_along_corner(p, x_ - 1, y_);
	}
	// 右下の角
	else if ((1 - x_) * (1 - x_) + (1 - y_) * (1 - y_) < radius_2)
	{
		if (vars->map[(int)vars->player.y + 1][(int)vars->player.x + 1] == '1')
			slide_along_corner(p, x_ - 1, y_ - 1);
	}
}

void	player_move(t_vars *vars, float key_delta)
{
	float	angle;
	float	move_len;
	int		flag;
	t_pnt_f	p;

	if (vars->keys[W_ID] != vars->keys[S_ID]
		|| vars->keys[A_ID] != vars->keys[D_ID])
	{
		move_len = (float)KEY_MOVE_SPEED / key_delta;
		angle = vars->player.angle_rad + get_bias_rad(vars->keys);
		p.x = move_len * -sin(angle);
		p.y = move_len * -cos(angle);
		flag = !check_x(vars, &p);
		flag = !check_y(vars, &p) && flag;
		if (flag)
			check_corner(vars, &p);
		vars->player.x += p.x;
		vars->player.y += p.y;
	}
}

void	player_rotate_for_key(t_vars *vars, float key_delta)
{
	if (vars->keys[RIGHT_ID] != vars->keys[LEFT_ID])
	{
		if (vars->keys[RIGHT_ID])
			vars->player.angle_rad -= KEY_ROTATE_SPEED / key_delta;
		if (vars->keys[LEFT_ID])
			vars->player.angle_rad += KEY_ROTATE_SPEED / key_delta;
		if (vars->player.angle_rad > (2 * PI))
			vars->player.angle_rad -= (2 * PI);
		else if (vars->player.angle_rad < (-2 * PI))
			vars->player.angle_rad += (2 * PI);
	}
}

// void	release_check(t_vars *vars, long now)
// {
// 	long	last_key_release_time;
// 	int		i;

// 	i = 0;
// 	while (i < KEY_NUM)
// 	{
// 		if (vars->keys[i] == 1)
// 		{
// 			last_key_release_time = vars->last_key_release_time[i];
// 			printf("[i:%d, press:%ld, release:%ld] ", i, vars->last_key_press_time[i], last_key_release_time);
// 			if (vars->last_key_press_time[i] <= last_key_release_time && now
// 				> (SHORTEST_CONSECUTIVE_PRESS_USEC + last_key_release_time))
// 				vars->keys[i] = 0;
// 		}
// 		i++;
// 	}
// 	printf("\n");
// }

int	loop_hook(t_vars *vars)
{
	long			now;
	float			frame_delta;
	float			mouse_delta;
	float			key_delta;
	t_colors		colors;

	now = gettime();
	// release_check(vars, now);
	mouse_delta = ONE_SEC_FOR_USEC / (now - vars->last_mouse_time);
	if (MOUSE_HZ > mouse_delta)
	{
		mouse_event(vars);
		vars->last_mouse_time = now;
	}
	key_delta = ONE_SEC_FOR_USEC / (now - vars->last_event_time);
	if (KEY_HZ > key_delta)
	{
		vars->event_delta_sum += key_delta;
		vars->event_count++;
		if (vars->last_key_m == 0 && vars->keys[M_ID] == 1)
			vars->is_map = !vars->is_map;
		vars->last_key_m = vars->keys[M_ID];
		player_move(vars, key_delta);
		player_rotate_for_key(vars, key_delta);
		vars->last_event_time = now;
	}
	frame_delta = ONE_SEC_FOR_USEC / (now - vars->last_frame_time);
	if (FRAME_HZ > frame_delta)
	{
		if (vars->last_frame_time)
		{
			printf("loop: %03d, calc: %.1f[Hz], disp: %.2f[Hz]",
				vars->i, vars->event_delta_sum / vars->event_count, frame_delta);
			print_player_status_for_dev(vars);
			vars->i = 0;
			vars->event_count = 0;
			vars->event_delta_sum = 0;
			printf("\n");
		}
		cast_rays(vars);
		colors.ceiling = 0x36300c;
		colors.floor = 0x222222;
		draw_background(vars, colors);
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
	vars->i++;
	return (CNT);
}
