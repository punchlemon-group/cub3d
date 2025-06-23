/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dark_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 02:39:53 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/23 18:59:03 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	dark_color(int color, float len)
{
	float	rate;
	int		r;
	int		g;
	int		b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	rate = 5.0 / ((len + 0.5) * (len + 0.5));
	rate += 0.3;
	if (rate > 1)
		rate = 1;
	r = (int)(r * rate);
	g = (int)(g * rate);
	b = (int)(b * rate);
	return ((r << 16) | (g << 8) | b);
}
