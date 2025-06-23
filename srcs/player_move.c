/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:48:58 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/24 00:59:23 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	move_x(t_vars *vars, t_pnt_f p)
{
	if (!check_x(vars, &(t_pnt_f){p.x, 0}))
	{
		vars->player.x += p.x;
		return (1);
	}
	return (0);
}

static int	move_y(t_vars *vars, t_pnt_f p)
{
	if (!check_y(vars, &(t_pnt_f){0, p.y}))
	{
		vars->player.y += p.y;
		return (1);
	}
	return (0);
}

static void	slide_corner(t_vars *vars, t_pnt_f p)
{
	check_corner(vars, &p);
	vars->player.x += p.x;
	vars->player.y += p.y;
}

void	player_move(t_vars *vars, float key_delta)
{
	float	angle;
	float	move_len;
	t_pnt_f	p;

	if (vars->keys[W_ID] != vars->keys[S_ID]
		|| vars->keys[A_ID] != vars->keys[D_ID])
	{
		move_len = (float)KEY_MOVE_SPEED / key_delta;
		angle = vars->player.angle_rad + get_bias_rad(vars->keys);
		p.x = move_len * -sin(angle);
		p.y = move_len * -cos(angle);
		if (!move_x(vars, p))
		{
			if (!move_y(vars, p))
				slide_corner(vars, p);
		}
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
