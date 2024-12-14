/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_2d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:49:12 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/14 21:04:08 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_2d(t_vars *vars, int color)
{
	ft_pixel_put_to_image(vars, color, vars->player.x, vars->player.y);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image_buffer, 0, 0);
	// mlx_pixel_put(vars->mlx, vars->win, vars->player.x, vars->player.y, color);
}
