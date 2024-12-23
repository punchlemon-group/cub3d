/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:11:29 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/23 06:43:06 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_vars *vars)
{
	t_cordinate	old;

	if (!vars->mouse_hide)
	{
		vars->mouse_hide = 1;
		mlx_mouse_hide(vars->mlx, vars->win);
		// mlx_mouse_move(vars->mlx, vars->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
	else
	{
		old = vars->mouse;
		vars->mouse.x = x;
		vars->mouse.y = y;
		vars->player.angle_rad += ROTATE_SPEED
			* (float)(old.x - vars->mouse.x);
		// if (x != WINDOW_WIDTH / 2 || y != WINDOW_HEIGHT / 2)
		// 	mlx_mouse_move(vars->mlx, vars->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	}
	while (vars->player.angle_rad < 0)
		vars->player.angle_rad += TPI;
	while (vars->player.angle_rad >= TPI)
		vars->player.angle_rad -= TPI;
	return (0);
}
