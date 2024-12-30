/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:18:03 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/28 18:20:19 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_vars *vars)
{
	int	i;

	i = 0;
	if (key == ESC)
		window_close(vars);
	else if (key == W)
		i = W_ID;
	else if (key == S)
		i = S_ID;
	else if (key == D)
		i = D_ID;
	else if (key == A)
		i = A_ID;
	else if (key == RIGHT)
		i = RIGHT_ID;
	else if (key == LEFT)
		i = LEFT_ID;
	else if (key == UP)
		i = UP_ID;
	else if (key == DOWN)
		i = DOWN_ID;
	else if (key == M)
		i = M_ID;
	else
		return (CNT);
	// vars->last_key_press_time[i] = gettime();
	vars->keys[i] = 1;
	return (CNT);
}

int	key_release(int key, t_vars *vars)
{
	int	i;

	if (key == W)
		i = W_ID;
	else if (key == S)
		i = S_ID;
	else if (key == D)
		i = D_ID;
	else if (key == A)
		i = A_ID;
	else if (key == RIGHT)
		i = RIGHT_ID;
	else if (key == LEFT)
		i = LEFT_ID;
	else if (key == UP)
		i = UP_ID;
	else if (key == DOWN)
		i = DOWN_ID;
	else if (key == M)
		i = M_ID;
	else
		return (CNT);
	// vars->last_key_release_time[i] = gettime();
	vars->keys[i] = 0;
	return (CNT);
}
