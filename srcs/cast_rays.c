/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:17:04 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/30 14:40:02 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	get_vertical_collision_len(t_vars *vars, float angle)
{
	float		d_y;
	int			y_int;
	int			x_int;
	int			d_x;
	t_ray		result;

	if (sin(angle) > 0)
	{
		result.img = vars->west;
		d_x = -1;
		x_int = (int)vars->player.x;
	}
	else if (sin(angle) < 0)
	{
		result.img = vars->east;
		d_x = 1;
		x_int = (int)vars->player.x + 1;
	}
	else
		return (result.len = INFINITY, result);
	d_y = (x_int - vars->player.x) / tan(angle);
	if (sin(angle) > 0)
		x_int += d_x;
	while (1)
	{
		y_int = (int)(vars->player.y + d_y);
		if (x_int < 0 || x_int >= vars->map_width
			|| y_int < 0 || y_int >= vars->map_height)
			return (result.len = INFINITY, result);
		if (vars->map[y_int][x_int] == '1')
		{
			result.x = (int)((vars->player.y + d_y - y_int) * (result.img->width));
			result.len = d_y / -cos(angle);
			return (result);
		}
		x_int += d_x;
		d_y += d_x / tan(angle);
	}
	return (result.len = INFINITY, result);
}

t_ray	get_horizontal_collision_len(t_vars *vars, float angle)
{
	float		d_x;
	int			y_int;
	int			x_int;
	int			d_y;
	t_ray		result;

	if (cos(angle) > 0)
	{
		result.img = vars->north;
		d_y = -1;
		y_int = (int)vars->player.y;
	}
	else if (cos(angle) < 0)
	{
		result.img = vars->south;
		d_y = 1;
		y_int = (int)vars->player.y + 1;
	}
	else
		return (result.len = INFINITY, result);
	d_x = (y_int - vars->player.y) * tan(angle);
	if (cos(angle) > 0)
		y_int += d_y;
	while (1)
	{
		x_int = (int)(vars->player.x + d_x);
		if (x_int < 0 || x_int >= vars->map_width
			|| y_int < 0 || y_int >= vars->map_height)
			return (result.len = INFINITY, result);
		if (vars->map[y_int][x_int] == '1')
		{
			result.x = (int)((vars->player.x + d_x - x_int) * (result.img->width));
			result.len = d_x / -sin(angle);
			return (result);
		}
		y_int += d_y;
		d_x += d_y * tan(angle);
	}
	return (result.len = INFINITY, result);
}

t_ray	get_ray(t_vars *vars, float angle)
{
	t_ray	horizontal;
	t_ray	vertical;

	horizontal = get_horizontal_collision_len(vars, angle);
	vertical = get_vertical_collision_len(vars, angle);
	if (horizontal.len < vertical.len)
		return (horizontal);
	else
		return (vertical);
}

void	cast_rays(t_vars *vars)
{
	float		angle;
	int			i;

	i = 0;
	angle = vars->player.angle_rad + VIEWING_HORIZONTAL_ANGLE_RAD / 2;
	while (i < WINDOW_WIDTH)
	{
		vars->rays[i] = get_ray(vars, angle);
		angle -= VIEWING_HORIZONTAL_ANGLE_RAD / (float)WINDOW_WIDTH;
		i++;
	}
}
