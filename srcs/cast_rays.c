/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:17:04 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/16 15:17:53 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_rays(t_vars *vars)
{
	int	len;
	float		angle;
	int	i;

	i = 0;
	(void)len;
	angle = vars->player.angle_rad + VIEWING_ANGLE_RAD / 2;
	while (i < WINDOW_WIDTH)
	{
		vars->rays[i].rate = 1; // here should be calculated
		angle -= VIEWING_ANGLE_RAD / (float)WINDOW_WIDTH;
		i++;
	}
}
