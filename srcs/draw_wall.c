/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:32:20 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/23 20:56:49 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_cell(t_vars *vars, int color, t_pnt_i head, int y_end)
{
	while (head.y < y_end)
	{
		if (head.y >= WINDOW_HEIGHT)
			return (END);
		if (head.y >= 0)
			ft_pixel_put_to_image(vars, color, head);
		head.y++;
	}
	return (CNT);
}

static void	init_wall_draw_vars(t_wall_draw_vars *v, int i, t_ray ray,
			float angle)
{
	v->limit = WINDOW_HEIGHT * (((float)SCREEN_RATIO
				* cos(VIEWING_HORIZONTAL_ANGLE_RAD / 2))
			/ cos(angle)) / ray.len;
	v->head.x = i;
	v->head.y = (WINDOW_HEIGHT - v->limit) / 2;
	v->d_y = (float)v->limit / (float)ray.img->height;
	if (v->head.y < 0)
	{
		v->j = (int)(-(float)v->head.y / v->d_y);
		v->head.y = 0;
	}
	else
		v->j = 0;
	v->y = (float)(WINDOW_HEIGHT - v->limit) / 2.0
		+ ((float)(v->j + 1)) * v->d_y;
}

static int	draw_wall_column(t_vars *vars, t_ray ray, t_wall_draw_vars *v)
{
	if (v->head.y >= WINDOW_HEIGHT)
		return (0);
	if (draw_cell(vars,
			dark_color(get_img_color(ray.img, ray.x, v->j), ray.len),
			v->head, (int)v->y) == END)
		return (0);
	v->head.y = (int)v->y;
	v->y += v->d_y;
	return (1);
}

void	draw_horizontal_line_easy_for_deb(t_vars *vars, int i, t_ray ray,
			float angle)
{
	t_wall_draw_vars	v;

	init_wall_draw_vars(&v, i, ray, angle);
	while (v.j < (ray.img->height))
	{
		if (!draw_wall_column(vars, ray, &v))
			break ;
		v.j++;
	}
}

void	draw_wall(t_vars *vars)
{
	float	angle;
	int		i;

	i = 0;
	angle = VIEWING_HORIZONTAL_ANGLE_RAD / 2;
	while (i < WINDOW_WIDTH)
	{
		draw_horizontal_line_easy_for_deb(vars, i, vars->rays[i], angle);
		angle -= VIEWING_HORIZONTAL_ANGLE_RAD / (float)WINDOW_WIDTH;
		i++;
	}
}
