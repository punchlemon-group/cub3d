/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_event_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:15:32 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/24 10:15:59 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_bias_rad(int *keys)
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

static void	check_corner_sub(t_vars *vars, t_pnt_f *p, t_pnt_f xy, t_pnt_i d)
{
	if (vars->map[(int)vars->player.y + d.y][(int)vars->player.x + d.x] == '1')
		slide_along_corner(p, xy.x + d.x, xy.y + d.y);
}

void	check_corner(t_vars *vars, t_pnt_f *p)
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
