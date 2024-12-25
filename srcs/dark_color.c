/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dark_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 02:39:53 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/25 12:41:32 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	dark_color(int color, float len)
{
	float	rate;

	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = color & 0xFF;
	rate = 5 / pow(len + 0.5, 2);
	rate += 0.2;
	if (rate > 1)
		rate = 1;
	r = (int)(r * rate);
	// if (r > 255)
	// 	r = 255;
	g = (int)(g * rate);
	// if (g > 255)
	// 	g = 255;
	b = (int)(b * rate);
	// if (b > 255)
	// 	b = 255;
	return ((r << 16) | (g << 8) | b);
}
