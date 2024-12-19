/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 02:34:10 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/19 03:15:45by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line_easy_for_deb(t_vars *vars, int color, int i)
{
	int			j;
	t_cordinate	c;
	
	j = 0;
	while (j < WINDOW_WIDTH)
	{
		c.y = i;
		c.x = j;
		ft_pixel_put_to_image(vars, color, c);
		j++;
	}
}

void	draw_background(t_vars *vars, int ceiling_color, int floor_color)
{
	float	angle;
	int		i;
	int		darked_color;

	i = 0;
	angle = VIEWING_VERTICAL_ANGLE_RAD / 2;
	while (i < WINDOW_HEIGHT)
	{
		if (sin(angle) > 0)
			darked_color = dark_color(ceiling_color, fabs(0.5 / sin(angle)));
		else
			darked_color = dark_color(floor_color, fabs(0.5 / sin(angle)));
		draw_vertical_line_easy_for_deb(vars, darked_color, i);
		angle -= VIEWING_VERTICAL_ANGLE_RAD / (float)WINDOW_HEIGHT;
		i++;
	}
}
