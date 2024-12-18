/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_put_to_image.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:59:48 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/18 14:54:44 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put_to_image(t_vars *vars, int color, t_cordinate c)
{
	((int *)vars->image_buffer->data)[c.y * WINDOW_WIDTH + c.x] = color;
}
