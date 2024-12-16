/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:50:30 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/16 13:24:25 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rays_2d(t_vars *vars, int color)
{
	t_cordinate	c;
	float		angle;
	int			i;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		angle = vars->player.angle_rad
			+ VIEWING_ANGLE_RAD * (i / (float)WINDOW_WIDTH - 0.5);
		c.x = MAP_SCALE * (vars->rays[i].rate * -sin(angle) + vars->player.x);
		c.y = MAP_SCALE * (vars->rays[i].rate * -cos(angle) + vars->player.y);
		ft_pixel_put_to_image(vars, color, c);
		i++;
	}
}
