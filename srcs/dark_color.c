/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dark_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 02:39:53 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/19 15:24:34 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	dark_color(int color, float len)
{
	float	rate;

	int r = (color >> 16) & 0xFF;
	int g = (color >> 8) & 0xFF;
	int b = color & 0xFF;
	rate = (LIGHT_DEAD_LEN_POW_2 - pow(len, 2)) / LIGHT_DEAD_LEN_POW_2;
	if (rate < 0.1)
		rate = 0.1;
	r = (int)(r * rate);
	g = (int)(g * rate);
	b = (int)(b * rate);
	return ((r << 16) | (g << 8) | b);
}
