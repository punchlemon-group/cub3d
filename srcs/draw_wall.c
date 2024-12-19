/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:32:20 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/19 03:48:52 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_horizontal_line_easy_for_deb(t_vars *vars, int color, int i, float len, float angle)
{
	int			j;
	int			limit;
	t_cordinate	c;
	
	limit = WINDOW_HEIGHT * (((float)SCREEN_RATIO * cos(VIEWING_HORIZONTAL_ANGLE_RAD / 2)) / cos(angle)) / len;
	if (limit > WINDOW_HEIGHT)
		limit = WINDOW_HEIGHT;
	j = (WINDOW_HEIGHT - limit) / 2;
	while (j < ((WINDOW_HEIGHT + limit) / 2))
	{
		c.x = i;
		c.y = j;
		ft_pixel_put_to_image(vars, color, c);
		j++;
	}
}

void	draw_wall(t_vars *vars, int color)
{
	float	angle;
	int		i;
	int		darked_color;

	i = 0;
	angle = VIEWING_HORIZONTAL_ANGLE_RAD / 2;
	while (i < WINDOW_WIDTH)
	{
		darked_color = dark_color(color, vars->rays[i].len);
		draw_horizontal_line_easy_for_deb(vars, darked_color, i, vars->rays[i].len, angle);
		angle -= VIEWING_HORIZONTAL_ANGLE_RAD / (float)WINDOW_WIDTH;
		i++;
	}
}
