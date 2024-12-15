/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_2d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:49:12 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/15 16:04:11 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_2d(t_vars *vars, int base_color, int nose_color)
{
	t_cordinate	c;

	c.x = vars->player.x * MAP_SCALE;
	c.y = vars->player.y * MAP_SCALE;
	ft_circle_put_to_image(vars, base_color, c, PLAYER_SIZE);
	c.x -= PLAYER_SIZE * sin(vars->player.angle_rad);
	c.y -= PLAYER_SIZE * cos(vars->player.angle_rad);
	ft_circle_put_to_image(vars, nose_color, c, PLAYER_SIZE / 2);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image_buffer, 0, 0);
	// mlx_pixel_put(vars->mlx, vars->win, vars->player.x, vars->player.y, color);
}
