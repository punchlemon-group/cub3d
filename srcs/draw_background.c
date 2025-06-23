/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 02:34:10 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/23 18:57:10 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling_and_floor(t_vars *vars, t_colors colors, float len,
	t_pnt_i c)
{
	int	x;
	int	y;

	x = c.x;
	y = c.y;
	ft_pixel_put_to_image(vars, dark_color(colors.ceiling, len), c);
	c.x = WINDOW_WIDTH - 1 - x;
	ft_pixel_put_to_image(vars, dark_color(colors.ceiling, len), c);
	c.y = WINDOW_HEIGHT - 1 - y;
	ft_pixel_put_to_image(vars, dark_color(colors.floor, len), c);
	c.x = x;
	ft_pixel_put_to_image(vars, dark_color(colors.floor, len), c);
}

void	draw_background(t_vars *vars, t_colors	colors)
{
	float		horizontal_angle;
	float		vertical_angle;
	int			i;
	int			j;
	t_pnt_i		c;

	i = 0;
	horizontal_angle = VIEWING_HORIZONTAL_ANGLE_RAD / 2;
	while (i < (WINDOW_WIDTH) / 2)
	{
		c.x = i;
		vertical_angle = VIEWING_VERTICAL_ANGLE_RAD / 2;
		j = 0;
		while (j < (WINDOW_HEIGHT) / 2)
		{
			c.y = j;
			draw_ceiling_and_floor(vars, colors, 0.5 / sin(vertical_angle)
				/ cos(horizontal_angle), c);
			vertical_angle -= VIEWING_VERTICAL_ANGLE_RAD / (float)WINDOW_HEIGHT;
			j++;
		}
		horizontal_angle -= VIEWING_HORIZONTAL_ANGLE_RAD / (float)WINDOW_WIDTH;
		i++;
	}
}
