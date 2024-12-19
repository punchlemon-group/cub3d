/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:50:30 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/19 02:32:29 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays_2d(t_vars *vars, int color)
{
	t_cordinate	c;
	float		angle;
	int			i;

	i = 0;
	angle = vars->player.angle_rad + VIEWING_HORIZONTAL_ANGLE_RAD / 2;
	while (i < WINDOW_WIDTH)
	{
		c.x = MAP_SCALE * (-sin(angle) * vars->rays[i].len + vars->player.x);
		c.y = MAP_SCALE * (-cos(angle) * vars->rays[i].len + vars->player.y);
		ft_pixel_put_to_image(vars, color, c);
		angle -= VIEWING_HORIZONTAL_ANGLE_RAD / (float)WINDOW_WIDTH;
		i++;
	}
}
