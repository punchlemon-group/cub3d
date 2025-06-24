/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:08:25 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/24 13:25:04 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_zero1(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < KEY_NUM)
		vars->keys[i++] = 0;
	vars->mlx = NULL;
	vars->win = NULL;
	vars->north = NULL;
	vars->east = NULL;
	vars->west = NULL;
	vars->south = NULL;
	vars->image_buffer = NULL;
	vars->map = NULL;
}

void	set_zero2(t_vars *vars)
{
	vars->last_event_time = 0;
	vars->last_frame_time = 0;
	vars->last_mouse_time = 0;
	vars->is_in_mouse = 0;
	vars->last_key_m = 0;
	vars->is_map = 0;
	vars->mouse.x = WINDOW_WIDTH / 2;
	vars->mouse.y = WINDOW_HEIGHT / 2;
	vars->config.no_path = NULL;
	vars->config.so_path = NULL;
	vars->config.we_path = NULL;
	vars->config.ea_path = NULL;
	vars->width = 0;
	vars->height = 0;
}

void	set_player_pos(t_vars *vars, int x, int y, char direction)
{
	vars->player.x = x + 0.5;
	vars->player.y = y + 0.5;
	vars->player.z = PLAYER_HEIGHT;
	vars->player.status = NORMAL;
	if (direction == 'N')
		vars->player.angle_rad = 0;
	else if (direction == 'E')
		vars->player.angle_rad = 3 * PI / 2;
	else if (direction == 'W')
		vars->player.angle_rad = PI / 2;
	else if (direction == 'S')
		vars->player.angle_rad = PI;
}

void	get_player(t_vars *vars)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			c = vars->map[i][j];
			if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
			{
				set_player_pos(vars, j, i, c);
				break ;
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_vars		vars;

	set_zero1(&vars);
	set_zero2(&vars);
	validation_and_parse(argc, argv, &vars);
	init(&vars);
	vars.map_width = vars.width;
	vars.map_height = vars.height;
	get_player(&vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_press, &vars);
	mlx_hook(vars.win, KeyRelease, KeyReleaseMask, key_release, &vars);
	mlx_hook(vars.win, DestroyNotify, NoEventMask, window_close, &vars);
	mlx_loop_hook(vars.mlx, loop_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
