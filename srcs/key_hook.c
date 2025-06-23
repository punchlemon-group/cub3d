/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:18:03 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/23 19:03:44 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_to_id(int key)
{
	if (key == W)
		return (W_ID);
	if (key == S)
		return (S_ID);
	if (key == D)
		return (D_ID);
	if (key == A)
		return (A_ID);
	if (key == RIGHT)
		return (RIGHT_ID);
	if (key == LEFT)
		return (LEFT_ID);
	if (key == UP)
		return (UP_ID);
	if (key == DOWN)
		return (DOWN_ID);
	if (key == M)
		return (M_ID);
	return (-1);
}

int	key_press(int key, t_vars *vars)
{
	int	i;

	if (key == ESC)
		window_close(vars);
	i = key_to_id(key);
	if (i < 0)
		return (CNT);
	vars->keys[i] = 1;
	return (CNT);
}

int	key_release(int key, t_vars *vars)
{
	int	i;

	i = key_to_id(key);
	if (i < 0)
		return (CNT);
	vars->keys[i] = 0;
	return (CNT);
}
