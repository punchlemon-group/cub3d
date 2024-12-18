/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:17:04 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/18 14:19:17 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_vertical_collision_len(t_vars *vars, float angle)
{
	(void)vars;
	(void)angle;
	return (INFINITY);
}

float	get_horizontal_collision_len(t_vars *vars, float angle)
{
	float		d_x;
	int			y_int;
	int			x_int;
	int			d_y;

	if (cos(angle) > 0)
	{
		d_y = -1;
		y_int = (int)vars->player.y;
	}
	else if (cos(angle) < 0)
	{
		d_y = 1;
		y_int = (int)vars->player.y + 1;
	}
	else
		return (INFINITY);
	d_x = (y_int - vars->player.y) * tan(angle);
	if (cos(angle) > 0)
		y_int += d_y;
	while (1) // you have to check segmentation fault
	{
		x_int = (int)(vars->player.x + d_x);
		if (vars->map[y_int][x_int] == '1')
			return (d_x / -sin(angle));
		y_int += d_y;
		d_x += d_y * tan(angle);
	}
}

float	get_len(t_vars *vars, float angle)
{
	float	horizontal_len;
	float	vertical_len;

	horizontal_len = get_horizontal_collision_len(vars, angle);
	vertical_len = get_vertical_collision_len(vars, angle);
	if (horizontal_len < vertical_len)
		return (horizontal_len);
	else
		return (vertical_len);
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
		angle -= VIEWING_ANGLE_RAD / (float)WINDOW_WIDTH;
		i++;
	}
}
