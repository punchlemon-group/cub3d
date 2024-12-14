/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:18:03 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/14 17:45:49 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player(int key, t_player *player)
{
	if (key == W)
		player->y -= 0.1;
	else if (key == S)
		player->y += 0.1;
	else if (key == D)
		player->x += 0.1;
	else if (key == A)
		player->x -= 0.1;
	else if (key == RIGHT || key == LEFT)
	{
		if (key == RIGHT)
			player->angle_deg++;
		else
			player->angle_deg--;
		player->angle_rad = player->angle_deg * PI / 180;
	}
}

void	print_player_status(t_player player)
{
	printf("x:%f, y:%f, angle_deg:%d, angle_rad:%f\n", player.x, player.y,
		player.angle_deg, player.angle_rad);
}

int	key_hook(int key, t_vars *vars)
{
	if (key == ESC)
		return (end(vars, 0), END);
	else if (key == W || key == S || key == D || key == A
		|| key == RIGHT || key == LEFT)
		update_player(key, &(vars->player));
	print_player_status(vars->player);
	return (CNT);
}
