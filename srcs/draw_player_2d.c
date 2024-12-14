/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:49:12 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/14 18:14:32 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_2d(t_vars *vars, int color)
{
	mlx_pixel_put(vars->mlx, vars->win, vars->player.x, vars->player.y, color);
}
