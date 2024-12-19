/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:32:20 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/19 08:33:20 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_cell(t_vars *vars, int color, t_cordinate head, int y_end)
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

void	draw_horizontal_line_easy_for_deb(t_vars *vars, int i, t_ray ray, float angle)
{
	int			j;
	int			limit;
	t_cordinate	head;
	float		y;
	float		d_y;
	
	limit = WINDOW_HEIGHT * (((float)SCREEN_RATIO * cos(VIEWING_HORIZONTAL_ANGLE_RAD / 2)) / cos(angle)) / ray.len;
	head.x = i;
	head.y = (WINDOW_HEIGHT - limit) / 2;
	y = head.y;
	d_y = (float)limit / (float)ray.img->height;
	j = 0;
	while (j < (ray.img->height))
	{
		if (head.y >= WINDOW_HEIGHT)
			return ;
		y += d_y;
		if (draw_cell(vars, dark_color(get_img_color(ray.img, ray.x, j), ray.len), head, (int)y) == END)
			return ;
		head.y = (int)y;
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
