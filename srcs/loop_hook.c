/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:31:19 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/24 10:42:11 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	rgb_to_int(int rgb[3])
{
	return (((rgb[0] & 0xFF) << 16) | ((rgb[1] & 0xFF) << 8) | (rgb[2] & 0xFF));
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

static void	handle_frame_event(t_vars *vars, long now)
{
	float		frame_delta;
	t_colors	colors;

	frame_delta = ONE_SEC_FOR_USEC / (now - vars->last_frame_time);
	if (FRAME_HZ > frame_delta)
	{
		cast_rays(vars);
		colors.ceiling = rgb_to_int(vars->config.ceil_color);
		colors.floor = rgb_to_int(vars->config.floor_color);
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
