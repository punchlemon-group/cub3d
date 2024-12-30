/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circle_put_to_image.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:44:45 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/30 15:17:02 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_circle_put_to_image(t_vars *vars, int color, t_pnt_i c, int r)
{
	int	i;
	int	i2;
	int	j;
	int	r2;
	int	*image;

	image = (int *)vars->image_buffer->data;
	r2 = r * r;
	i = -r;
	while (i <= r)
	{
		i2 = i * i;
		j = -r;
		while (j <= r)
		{
			if (i2 + j * j < r2)
				image[(c.y + i) * WINDOW_WIDTH + (c.x + j)] = color;
			j++;
		}
		i++;
	}
}
