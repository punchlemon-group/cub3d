/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:31:19 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/14 19:31:21 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_player_status(t_player player)
{
	printf("x:%f, y:%f, angle_rad:%f\n", player.x, player.y, player.angle_rad);
}

int	loop_hook(t_vars *vars)
{
	int	bias;

	if (vars->keys[W_ID] || vars->keys[S_ID])
	{
		if (vars->keys[W_ID])
			bias = 90;
		if (vars->keys[S_ID])
			bias = 270;
		if (!(vars->keys[W_ID] && vars->keys[S_ID]))
		{
			vars->player.x += 0.01 * cos(vars->player.angle_rad + bias * PI / 180);
			vars->player.y -= 0.01 * sin(vars->player.angle_rad + bias * PI / 180);
		}
	}
	if (vars->keys[A_ID] || vars->keys[D_ID])
	{
		if (vars->keys[A_ID])
			bias = 180;
		if (vars->keys[D_ID])
			bias = 0;
		if (!(vars->keys[A_ID] && vars->keys[D_ID]))
		{
			vars->player.x += 0.01 * cos(vars->player.angle_rad + bias * PI / 180);
			vars->player.y -= 0.01 * sin(vars->player.angle_rad + bias * PI / 180);
		}
	}
	if (vars->keys[RIGHT_ID] || vars->keys[LEFT_ID])
	{
		if (vars->keys[RIGHT_ID])
			vars->player.angle_rad -= 0.0001;
		if (vars->keys[LEFT_ID])
			vars->player.angle_rad += 0.0001;
	}
	print_player_status(vars->player);
	draw_player_2d(vars, 0xff0000);
	return (CNT);
}
