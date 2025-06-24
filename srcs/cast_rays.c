/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:17:04 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/23 22:11:15 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ray	get_vlen(t_vars *v, float a)
{
	t_ray			res;
	t_ray_params	p;

	init_vparam(v, a, &res, &p);
	if (sin(a) == 0)
		return (res.len = INFINITY, res);
	p.d_y = (p.x_int - v->player.x) / tan(a);
	if (sin(a) > 0)
		p.x_int += p.d_x;
	if (vloop(v, a, &res, &p))
		return (res);
	return (res.len = INFINITY, res);
}

static t_ray	get_hlen(t_vars *v, float a)
{
	t_ray			res;
	t_ray_params	p;

	init_hparam(v, a, &res, &p);
	if (cos(a) == 0)
		return (res.len = INFINITY, res);
	p.d_x_h = (p.y_int - v->player.y) * tan(a);
	if (cos(a) > 0)
		p.y_int += p.d_y_h;
	if (hloop(v, a, &res, &p))
		return (res);
	return (res.len = INFINITY, res);
}

t_ray	get_ray(t_vars *v, float a)
{
	t_ray	h;
	t_ray	ver;

	h = get_hlen(v, a);
	ver = get_vlen(v, a);
	if (h.len < ver.len)
		return (h);
	return (ver);
}

void	cast_rays(t_vars *v)
{
	float	a;
	int		i;

	i = 0;
	a = v->player.angle_rad + VIEWING_HORIZONTAL_ANGLE_RAD / 2;
	while (i < WINDOW_WIDTH)
	{
		v->rays[i] = get_ray(v, a);
		a -= VIEWING_HORIZONTAL_ANGLE_RAD / (float)WINDOW_WIDTH;
		i++;
	}
}
