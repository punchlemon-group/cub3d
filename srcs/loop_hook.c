/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:31:19 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/24 00:50:56 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	get_bias_rad(int *keys)
{
	float	bias_rad;

	bias_rad = 0.0f;
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
			bias_rad = bias_rad / 2.0f;
			if (keys[W_ID] && keys[D_ID])
				bias_rad = 7 * PI / 4;
		}
	}
	return (bias_rad);
}

static int	check_y(t_vars *vars, t_pnt_f *p)
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

static int	check_x(t_vars *vars, t_pnt_f *p)
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

static float	vec2_length(float x, float y)
{
	return (sqrt(x * x + y * y));
}

static float	dot(float x1, float y1, float x2, float y2)
{
	return (x1 * x2 + y1 * y2);
}

static int	is_too_small(float v)
{
	return (v < 0.001f);
}

static void	zero_vec(t_pnt_f *p)
{
	p->x = 0;
	p->y = 0;
}

static void	slide_along_corner_scale(t_pnt_f *p, float orig_speed)
{
	float	slide_speed;
	float	speed_ratio;

	slide_speed = vec2_length(p->x, p->y);
	if (!is_too_small(slide_speed))
	{
		speed_ratio = orig_speed * 0.8f / slide_speed;
		p->x *= speed_ratio;
		p->y *= speed_ratio;
	}
}

static void	slide_along_corner(t_pnt_f *p, float corner_x, float corner_y)
{
	float	len;
	float	orig_speed;
	float	tangent_x;
	float	tangent_y;
	float	dot_tangent;

	orig_speed = vec2_length(p->x, p->y);
	if (is_too_small(orig_speed))
		return ;
	len = vec2_length(corner_x, corner_y);
	if (is_too_small(len))
	{
		zero_vec(p);
		return ;
	}
	corner_x /= len;
	corner_y /= len;
	tangent_x = -corner_y;
	tangent_y = corner_x;
	dot_tangent = dot(p->x, p->y, tangent_x, tangent_y);
	p->x = dot_tangent * tangent_x;
	p->y = dot_tangent * tangent_y;
	slide_along_corner_scale(p, orig_speed);
}

static void	check_corner_sub(t_vars *vars, t_pnt_f *p, t_pnt_f xy, t_pnt_i d)
{
	if (vars->map[(int)vars->player.y + d.y][(int)vars->player.x + d.x] == '1')
		slide_along_corner(p, xy.x + d.x, xy.y + d.y);
}

static void	check_corner(t_vars *vars, t_pnt_f *p)
{
	float	x_;
	float	y_;
	float	r2;
	float	x2;
	float	y2;

	x_ = vars->player.x - (int)vars->player.x + p->x;
	y_ = vars->player.y - (int)vars->player.y + p->y;
	r2 = PLAYER_RADIUS * PLAYER_RADIUS;
	x2 = x_ * x_;
	y2 = y_ * y_;
	if (x2 + y2 < r2)
		check_corner_sub(vars, p, (t_pnt_f){x_, y_}, (t_pnt_i){-1, -1});
	else if (x2 + (1 - y_) * (1 - y_) < r2)
		check_corner_sub(vars, p, (t_pnt_f){x_, y_ - 1}, (t_pnt_i){-1, 1});
	else if ((1 - x_) * (1 - x_) + y2 < r2)
		check_corner_sub(vars, p, (t_pnt_f){x_ - 1, y_}, (t_pnt_i){1, -1});
	else if ((1 - x_) * (1 - x_) + (1 - y_) * (1 - y_) < r2)
		check_corner_sub(vars, p, (t_pnt_f){x_ - 1, y_ - 1}, (t_pnt_i){1, 1});
}

static void	player_move(t_vars *vars, float key_delta)
{
	float	angle;
	float	move_len;
	int		flag;
	t_pnt_f	p;

	move_len = 0.0f;
	angle = 0.0f;
	flag = 0;
	p.x = 0.0f;
	p.y = 0.0f;
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

static void	player_rotate_for_key(t_vars *vars, float key_delta)
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

static void	handle_mouse_event(t_vars *vars, long now)
{
	float	mouse_delta;

	mouse_delta = ONE_SEC_FOR_USEC / (now - vars->last_mouse_time);
	if (MOUSE_HZ > mouse_delta)
	{
		mouse_event(vars);
		vars->last_mouse_time = now;
	}
}

static void	handle_key_event(t_vars *vars, long now)
{
	float	key_delta;

	key_delta = ONE_SEC_FOR_USEC / (now - vars->last_event_time);
	if (KEY_HZ > key_delta)
	{
		if (vars->last_key_m == 0 && vars->keys[M_ID] == 1)
			vars->is_map = !vars->is_map;
		vars->last_key_m = vars->keys[M_ID];
		player_move(vars, key_delta);
		player_rotate_for_key(vars, key_delta);
		vars->last_event_time = now;
	}
}

static void	handle_frame_event(t_vars *vars, long now)
{
	float		frame_delta;
	t_colors	colors;

	frame_delta = ONE_SEC_FOR_USEC / (now - vars->last_frame_time);
	if (FRAME_HZ > frame_delta)
	{
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
}

int	loop_hook(t_vars *vars)
{
	long	now;

	now = gettime();
	handle_mouse_event(vars, now);
	handle_key_event(vars, now);
	handle_frame_event(vars, now);
	return (CNT);
}
