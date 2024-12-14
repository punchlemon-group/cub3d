/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:18:03 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/14 18:56:16 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_vars *vars)
{
	if (key == ESC)
		return (end(vars, 0), END);
	else if (key == W)
		vars->keys[W_ID] = 1;
	else if (key == S)
		vars->keys[S_ID] = 1;
	else if (key == D)
		vars->keys[D_ID] = 1;
	else if (key == A)
		vars->keys[A_ID] = 1;
	else if (key == RIGHT)
		vars->keys[RIGHT_ID] = 1;
	else if (key == LEFT)
		vars->keys[LEFT_ID] = 1;
	return (CNT);
}

int	key_release(int key, t_vars *vars)
{
	if (key == W)
		vars->keys[W_ID] = 0;
	else if (key == S)
		vars->keys[S_ID] = 0;
	else if (key == D)
		vars->keys[D_ID] = 0;
	else if (key == A)
		vars->keys[A_ID] = 0;
	else if (key == RIGHT)
		vars->keys[RIGHT_ID] = 0;
	else if (key == LEFT)
		vars->keys[LEFT_ID] = 0;
	return (CNT);
}
