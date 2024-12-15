/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:07:31 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/15 16:13:04 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor(t_vars *vars, int color)
{
	t_cordinate	c;
	t_cordinate len;

	c.x = 0;
	c.y = vars->height / 2;
	len.x = vars->width;
	len.y = vars->height / 2;
	ft_rectangle_put_to_image(vars, color, c, len);
}
