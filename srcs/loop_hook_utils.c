/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:05:31 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/24 10:22:47 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	vec2_length(float x, float y)
{
	return (sqrt(x * x + y * y));
}

static float	dot(float x1, float y1, float x2, float y2)
{
	return (x1 * x2 + y1 * y2);
}

static void	zero_vec(t_pnt_f *p)
{
	p->x = 0;
	p->y = 0;
}

static void	slide_along_corner_scale(t_pnt_f *p, float orig_speed)
{
	float	slide_speed;
	float	speed_ratio;

	slide_speed = vec2_length(p->x, p->y);
	if (!(slide_speed < 0.001f))
	{
		speed_ratio = orig_speed * 0.8f / slide_speed;
		p->x *= speed_ratio;
		p->y *= speed_ratio;
	}
}

void	slide_along_corner(t_pnt_f *p, float corner_x, float corner_y)
{
	float	len;
	float	orig_speed;
	float	tangent_x;
	float	tangent_y;
	float	dot_tangent;

	orig_speed = vec2_length(p->x, p->y);
	if (orig_speed < 0.001f)
		return ;
	len = vec2_length(corner_x, corner_y);
	if (len < 0.001f)
	{
		zero_vec(p);
		return ;
	}
	corner_x /= len;
	corner_y /= len;
	tangent_x = -corner_y;
	tangent_y = corner_x;
	dot_tangent = dot(p->x, p->y, tangent_x, tangent_y);
	p->x = dot_tangent * tangent_x;
	p->y = dot_tangent * tangent_y;
	slide_along_corner_scale(p, orig_speed);
}
