/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:08:25 by retanaka          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/12/21 17:41:43 by retanaka         ###   ########.fr       */
=======
/*   Updated: 2024/12/23 06:43:13 by retanaka         ###   ########.fr       */
>>>>>>> fb1e0612c933ed21879d3ef84a946a2a7c7eb17f
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MINIMUM_FILE_NAME_LEN 1

enum
{
	OK = 0,
	TOO_SHORT,
	NO_EXTENTION,
};

// int	is_filename_char(const char c)
// {

// }

int	is_valid_filename(const char *src, const char *extention)
{
	size_t	i;
	size_t	src_len;
	size_t	extention_len;
	const char	*dot_p;

	src_len = ft_strlen(src);
	extention_len = ft_strlen(extention);
	i = 0;
	while (i < src_len)
	{
		// is_filename_char(src[i]);
		i++;
	}
	if (src_len < (MINIMUM_FILE_NAME_LEN + 1 + extention_len))
		return (TOO_SHORT);
	dot_p = ft_strrchr(src, '.');
	if (!dot_p)
		return (NO_EXTENTION);
	return (OK);
}

void	check_args(int argc, char **argv, t_vars *vars)
{
	int	is_valid_filename_result;

	(void)vars;
	if (argc != 2)
		end(NULL, 0, "Number of arguments is wrong\n");
	is_valid_filename_result = is_valid_filename(argv[1], "cub");
	if (is_valid_filename_result == TOO_SHORT)
		end(NULL, 0, "File name is too short\n");
	if (is_valid_filename_result == NO_EXTENTION)
		end(NULL, 0, "No extention\n");
}

void	create_tiles(t_vars *vars)
{
	int	width;
	int	height;

	vars->north = mlx_xpm_file_to_image(vars->mlx, "texture/isi.xpm",
		&width, &height);
	if (!vars->north)
		end(vars, 0, "");
	vars->east = mlx_xpm_file_to_image(vars->mlx, "texture/koke_isirenga.xpm",
		&width, &height);
	if (!vars->east)
		end(vars, 0, "");
	vars->west = mlx_xpm_file_to_image(vars->mlx, "texture/koke_maruisi.xpm",
		&width, &height);
	if (!vars->west)
		end(vars, 0, "");
	vars->south = mlx_xpm_file_to_image(vars->mlx, "texture/kuro_isirenga.xpm",
		&width, &height);
	if (!vars->south)
		end(vars, 0, "");
}

void	set_zero(t_vars *vars)
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

	vars->last_calc_time = 0;
	vars->last_disp_time = 0;
	vars->i = 0;
	vars->event_count = 0;
	vars->event_delta_sum = 0;
	vars->mouse_hide = 0;
}

void	init(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		end(vars, 0, "mlx_init failed\n");
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (!vars->win)
		end(vars, 0, "mlx_new_window failed\n");
	vars->image_buffer = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!vars->image_buffer)
		end(vars, 0, "\"Image buffer\" was not generated\n");
	create_tiles(vars);
	vars->addr = "maps/test.cub";
	vars->map = get_map(vars->addr);
	if (!vars->map)
		end(vars, 0, "");
}

// todo end関数のmessageを全部決める

void	get_map_size(t_vars *vars)
{
	int		i;
	int		j;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
			j++;
		i++;
	}
	vars->map_width = j;
	vars->map_height = i;
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
				vars->player.x = j + 0.5;
				vars->player.y = i + 0.5;
				vars->player.z = PLAYER_HEIGHT;
				vars->player.status = NORMAL;
				if (c == 'N')
					vars->player.angle_rad = 0;
				else if (c == 'E')
					vars->player.angle_rad = 3 * PI / 2;
				else if (c == 'W')
					vars->player.angle_rad = PI / 2;
				else if (c == 'S')
					vars->player.angle_rad = PI;
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

	set_zero(&vars);
	(void)argc;
	(void)argv;
	// check_args(argc, argv, &vars);
	init(&vars);
	get_map_size(&vars);
	get_player(&vars);

	mlx_hook(vars.win, KeyPress, KeyPressMask, key_press, &vars);
	mlx_hook(vars.win, KeyRelease, KeyReleaseMask, key_release, &vars);
	mlx_hook(vars.win, DestroyNotify, NoEventMask, window_close, &vars);
	mlx_hook(vars.win, MotionNotify, PointerMotionMask, mouse_move, &vars);
	mlx_loop_hook(vars.mlx, loop_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
