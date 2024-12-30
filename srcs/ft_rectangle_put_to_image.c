/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rectangle_put_to_image.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:50:18 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/30 15:17:02 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rectangle_put_to_image(t_vars *vars, int color, t_pnt_i c,
	t_pnt_i len)
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
