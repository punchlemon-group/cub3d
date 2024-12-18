/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rectangle_put_to_image.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:50:18 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/18 14:54:54 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rectangle_put_to_image(t_vars *vars, int color, t_cordinate c,
	t_cordinate len)
{
	int	i;
	int	j;
	int	*image_buffer;

	image_buffer = (int *)vars->image_buffer->data;
	i = 0;
	while (i < len.y)
	{
		j = 0;
		while (j < len.x)
		{
			image_buffer[(c.y + i) * WINDOW_WIDTH + (c.x + j)] = color;
			j++;
		}
		i++;
	}
}
