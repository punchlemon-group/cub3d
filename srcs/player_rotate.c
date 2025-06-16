/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:11:29 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/30 15:17:02 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_event(t_vars *vars)
{
	t_pnt_i		new;

	mlx_mouse_get_pos(vars->mlx, vars->win, &new.x, &new.y);
	// printf("Mouse pos: %d, %d (is_in_mouse: %d)\n", new.x, new.y, vars->is_in_mouse); // Debug
	if (new.x < 0 || new.x >= WINDOW_WIDTH
		|| new.y < 0 || new.y >= WINDOW_HEIGHT)
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
			player_rotate_for_mouse(vars, &new);
		else
		{
			vars->is_in_mouse = 1;
			mlx_mouse_hide(vars->mlx, vars->win);
			mlx_mouse_move(vars->mlx, vars->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
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
		mlx_mouse_move(vars->mlx, vars->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		vars->mouse.x = WINDOW_WIDTH / 2;
		vars->mouse.y = WINDOW_HEIGHT / 2;
		while (vars->player.angle_rad < 0)
			vars->player.angle_rad += TPI;
		while (vars->player.angle_rad >= TPI)
			vars->player.angle_rad -= TPI;
	}
}
