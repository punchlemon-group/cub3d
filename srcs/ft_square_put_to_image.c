/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square_put_to_image.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:50:18 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/15 14:58:21 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_square_put_to_image(t_vars *vars, int color, t_cordinate c, int a)
{
	int	i;
	int	j;
	int	*image_buffer;

	image_buffer = (int *)vars->image_buffer->data;
	i = 0;
	while (i < a)
	{
		j = 0;
		while (j < a)
		{
			image_buffer[(c.y + i) * vars->width + (c.x + j)] = color;
			j++;
		}
		i++;
	}
}
