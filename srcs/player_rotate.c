/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:11:29 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/23 04:08:06 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_event(t_vars *vars)
{
	t_pnt_i		n;

	mlx_mouse_get_pos(vars->mlx, vars->win, &n.x, &n.y);
	if (n.x < 0 || n.x >= WINDOW_WIDTH || n.y < 0 || n.y >= WINDOW_HEIGHT)
	{
		if (vars->is_in_mouse)
		{
			mlx_mouse_show(vars->mlx, vars->win);
			vars->is_in_mouse = 0;
		}
	}
	else
	{
		if (vars->is_in_mouse)
			player_rotate_for_mouse(vars, &n);
		else
		{
			vars->is_in_mouse = 1;
			mlx_mouse_hide(vars->mlx, vars->win);
			mlx_mouse_move(vars->mlx, vars->win,
				WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
			vars->mouse.x = WINDOW_WIDTH / 2;
			vars->mouse.y = WINDOW_HEIGHT / 2;
		}
	}
}

void	player_rotate_for_mouse(t_vars *vars, t_pnt_i *new)
{
	if (new->x != WINDOW_WIDTH / 2 || new->y != WINDOW_HEIGHT / 2)
	{
		vars->player.angle_rad += MOUSE_ROTATE_SPEED
			* (float)(vars->mouse.x - new->x);
		mlx_mouse_move(vars->mlx, vars->win,
			WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		vars->mouse.x = WINDOW_WIDTH / 2;
		vars->mouse.y = WINDOW_HEIGHT / 2;
		while (vars->player.angle_rad < 0)
			vars->player.angle_rad += TPI;
		while (vars->player.angle_rad >= TPI)
			vars->player.angle_rad -= TPI;
	}
}

int	mouse_move(int x, int y, t_vars *vars)
{
	t_pnt_i	new;
	float	delta_x;

	new.x = x;
	new.y = y;
	if (vars->is_in_mouse)
	{
		delta_x = (float)(vars->mouse.x - new.x);
		vars->player.angle_rad += MOUSE_ROTATE_SPEED_EVENT * delta_x;
		while (vars->player.angle_rad < 0)
			vars->player.angle_rad += TPI;
		while (vars->player.angle_rad >= TPI)
			vars->player.angle_rad -= TPI;
		vars->mouse.x = new.x;
		vars->mouse.y = new.y;
	}
	else
	{
		vars->is_in_mouse = 1;
		mlx_mouse_hide(vars->mlx, vars->win);
		vars->mouse.x = new.x;
		vars->mouse.y = new.y;
	}
	return (0);
}
