/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:17:04 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/17 16:21:16 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_len(t_vars *vars, float angle)
{
	float		y_;
	float		d_x;
	int			y_int;
	int			x_int;

	y_int = (int)vars->player.y;
	y_ = vars->player.y - y_int;
	d_x = y_ * tan(angle);
	while (y_int--)
	{
		x_int = (int)(vars->player.x - d_x);
		if (vars->map[y_int][x_int] == '1')
			return (sqrt(pow(vars->player.y - y_int - 1, 2) + pow(d_x, 2)));
		d_x += tan(angle);
	}
	return (0);
}

void	cast_rays(t_vars *vars)
{
	float		angle;
	int			i;
	t_ray		*ray;

	i = 0;
	angle = vars->player.angle_rad + VIEWING_ANGLE_RAD / 2;
	while (i < WINDOW_WIDTH)
	{
		ray = &(vars->rays[i]);
		ray->len = get_len(vars, angle);
		ray->rate = 1; // here should be calculated
		angle -= VIEWING_ANGLE_RAD / (float)WINDOW_WIDTH;
		i++;
	}
}
