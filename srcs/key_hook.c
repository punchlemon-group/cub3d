/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:18:03 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/14 17:39:14 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		return (end(vars, 0), END);
	else if (keycode == W)
		vars->player.y -= 0.1;
	else if (keycode == S)
		vars->player.y += 0.1;
	else if (keycode == D)
		vars->player.x += 0.1;
	else if (keycode == A)
		vars->player.x -= 0.1;
	else if (keycode == RIGHT || keycode == LEFT)
	{
		if (keycode == RIGHT)
			vars->player.angle_deg++;
		else
			vars->player.angle_deg--;
		vars->player.angle_rad = vars->player.angle_deg * PI / 180;
	}
	printf("x:%f, y:%f, angle_deg:%d, angle_rad:%f\n", vars->player.x, vars->player.y, vars->player.angle_deg, vars->player.angle_rad);
	return (CNT);
}
