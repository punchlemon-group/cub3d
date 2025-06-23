/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:08:27 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/23 22:09:34 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vparam(t_vars *v, float a, t_ray *r, t_ray_params *p)
{
	if (sin(a) > 0)
	{
		r->img = v->west;
		p->d_x = -1;
		p->x_int = (int)v->player.x;
	}
	else if (sin(a) < 0)
	{
		r->img = v->east;
		p->d_x = 1;
		p->x_int = (int)v->player.x + 1;
	}
}

void	init_hparam(t_vars *v, float a, t_ray *r, t_ray_params *p)
{
	if (cos(a) > 0)
	{
		r->img = v->north;
		p->d_y_h = -1;
		p->y_int = (int)v->player.y;
	}
	else if (cos(a) < 0)
	{
		r->img = v->south;
		p->d_y_h = 1;
		p->y_int = (int)v->player.y + 1;
	}
}

int	vloop(t_vars *v, float a, t_ray *r, t_ray_params *p)
{
	int	y_int;

	while (1)
	{
		y_int = (int)(v->player.y + p->d_y);
		if (p->x_int < 0 || p->x_int >= v->map_width
			|| y_int < 0 || y_int >= v->map_height)
			return (0);
		if (v->map[y_int][p->x_int] == '1')
		{
			r->x = (int)((v->player.y + p->d_y - y_int)
					* (r->img->width));
			r->len = p->d_y / -cos(a);
			return (1);
		}
		p->x_int += p->d_x;
		p->d_y += p->d_x / tan(a);
	}
	return (0);
}

int	hloop(t_vars *v, float a, t_ray *r, t_ray_params *p)
{
	int	x_int;

	while (1)
	{
		x_int = (int)(v->player.x + p->d_x_h);
		if (x_int < 0 || x_int >= v->map_width
			|| p->y_int < 0 || p->y_int >= v->map_height)
			return (0);
		if (v->map[p->y_int][x_int] == '1')
		{
			r->x = (int)((v->player.x + p->d_x_h - x_int)
					* (r->img->width));
			r->len = p->d_x_h / -sin(a);
			return (1);
		}
		p->y_int += p->d_y_h;
		p->d_x_h += p->d_y_h * tan(a);
	}
	return (0);
}
