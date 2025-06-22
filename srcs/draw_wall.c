/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:32:20 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/23 04:38:31 by retanaka         ###   ########.fr       */
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

void	draw_horizontal_line_easy_for_deb(t_vars *vars, int i, t_ray ray,
			float angle)
{
	int			j;
	int			limit;
	t_pnt_i		head;
	float		y;
	float		d_y;

	limit = WINDOW_HEIGHT * (((float)SCREEN_RATIO
				* cos(VIEWING_HORIZONTAL_ANGLE_RAD / 2))
			/ cos(angle)) / ray.len;
	head.x = i;
	head.y = (WINDOW_HEIGHT - limit) / 2;
	d_y = (float)limit / (float)ray.img->height;
	if (head.y < 0)
	{
		j = (int)(-(float)head.y / d_y);
		head.y = 0;
	}
	else
		j = 0;
	y = (float)(WINDOW_HEIGHT - limit) / 2.0 + ((float)(j + 1)) * d_y;
	while (j < (ray.img->height))
	{
		if (head.y >= WINDOW_HEIGHT)
			break ;
		if (draw_cell(vars, dark_color(get_img_color(ray.img, ray.x, j),
					ray.len), head, (int)y) == END)
			break ;
		head.y = (int)y;
		y += d_y;
		j++;
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
