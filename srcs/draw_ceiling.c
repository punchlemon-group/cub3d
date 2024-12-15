/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:07:33 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/15 16:10:28 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_vars *vars, int color)
{
	t_cordinate	c;
	t_cordinate len;

	c.x = 0;
	c.y = 0;
	len.x = vars->width;
	len.y = vars->height / 2;
	ft_rectangle_put_to_image(vars, color, c, len);
}
