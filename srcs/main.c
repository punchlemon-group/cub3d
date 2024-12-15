/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:08:25 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/15 10:38:14 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	check_args(int argc, char **argv)
{
	if (argc != 2)
		return (printf("Invalid args\n"), END);
	if (*(argv[1]) != 'a') // ファイルが開けるかどうかチェックする
		return (printf("Invalid args\n"), END);
	return (CNT);
}

int	init(t_vars *vars, int **map)
{
	int	i;

	i = 0;
	while (i < KEY_NUM)
		vars->keys[i++] = 0;
	vars->width = 1920;
	vars->height = 1080;
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (END);
	vars->win = mlx_new_window(vars->mlx, vars->width, vars->height, "cub3d");
	if (!vars->win)
		return (mlx_destroy_display(vars->mlx), END);
	vars->image_buffer = mlx_new_image(vars->mlx, vars->width, vars->height);
	if (!vars->image_buffer)
		return (mlx_destroy_window(vars->mlx, vars->win),
			mlx_destroy_display(vars->mlx), END);
	vars->addr = "./maps/test.ber";
	vars->map = map; // 本当はvars->addrから展開する関数を呼び出す
	vars->player.x = 6;
	vars->player.y = 6;
	vars->player.angle_rad = 0;
	vars->last_calc_time = 0;
	vars->last_disp_time = 0;
	return (CNT);
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	static int	map[8][8] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
	};

	if (check_args(argc, argv) == END)
		return (END);
	if (init(&vars, (int **)map) == END)
		return (END);

	mlx_hook(vars.win, KEY_PRESS, 1L << 0, key_press, &vars);
	mlx_hook(vars.win, KEY_RELEASE, 1L << 1, key_release, &vars);

	mlx_hook(vars.win, X_BUTTON, 0, window_close, &vars); // Xボタンに対応

	mlx_loop_hook(vars.mlx, loop_hook, &vars);

	mlx_loop(vars.mlx);
	return (0);
}
