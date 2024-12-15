/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:43:26 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/15 15:07:53 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map_2d(t_vars *vars, int floor_color, int wall_color)
{
	int	i;
	int	j;
	t_cordinate	c;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			c.x = j * MAP_SCALE;
			c.y = i * MAP_SCALE;
			if (vars->map[i][j] == '1')
				ft_square_put_to_image(vars, floor_color, c, MAP_SCALE);
			else
				ft_square_put_to_image(vars, wall_color, c, MAP_SCALE);
			j++;
		}
		i++;
	}
}
