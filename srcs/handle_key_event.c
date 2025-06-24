/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:10:54 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/24 10:16:41 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	handle_key_event(t_vars *vars, long now)
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
