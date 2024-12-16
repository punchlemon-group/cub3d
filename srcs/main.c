/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:08:25 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/16 13:20:50 by retanaka         ###   ########.fr       */
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

void	create_tiles(t_vars *vars)
{
	int	width;
	int	height;

	vars->east = NULL;
	vars->west = NULL;
	vars->south = NULL;
	vars->north = mlx_xpm_file_to_image(vars->mlx, "texture/mario.xpm",
		&width, &height);
	if (!vars->north)
		end(vars, 0);
	vars->east = mlx_xpm_file_to_image(vars->mlx, "texture/oak_log.xpm",
		&width, &height);
	if (!vars->east)
		end(vars, 0);
	vars->west = mlx_xpm_file_to_image(vars->mlx, "texture/pierre_moussu.xpm",
		&width, &height);
	if (!vars->west)
		end(vars, 0);
	vars->south = mlx_xpm_file_to_image(vars->mlx, "texture/renga.xpm",
		&width, &height);
	if (!vars->south)
		end(vars, 0);
}

void	init_rays(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		vars->rays[i].rate = 1;
		vars->rays[i].img = NULL;
		vars->rays[i].x = 0;
		i++;
	}
}

int	init(t_vars *vars)
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
	vars->addr = "maps/test.ber";
	vars->player.x = 5;
	vars->player.y = 5;
	vars->player.angle_rad = 0;
	vars->last_calc_time = 0;
	vars->last_disp_time = 0;
	vars->i = 0;
	return (CNT);
}

char	*ft_join_and_free(char *s1, char *s2)
{
	char	*ans;
	int		i;
	int		j;

	if (s1 == NULL)
		return (NULL);
	ans = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ans == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ans[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		ans[i++] = s2[j++];
	ans[i] = '\0';
	free(s1);
	free(s2);
	return (ans);
}

char	**get_map(char *file)
{
	int		fd;
	char	*crr_line;
	char	*linked_lines;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	linked_lines = ft_strdup("");
	if (!linked_lines)
		return (NULL);
	while (1)
	{
		crr_line = get_next_line(fd);
		if (crr_line == NULL)
			break ;
		linked_lines = ft_join_and_free(linked_lines, crr_line);
		if (linked_lines == NULL)
			return (NULL);
	}
	// get_map_handle_error(crr_line, linked_lines);
	free(crr_line);
	map = ft_split(linked_lines, '\n');
	free(linked_lines);
	return (map);
}

int	main(int argc, char **argv)
{
	t_vars		vars;

	if (check_args(argc, argv) == END)
		return (END);
	if (init(&vars) == END)
		return (END);
	create_tiles(&vars);
	vars.map = get_map(vars.addr);

	mlx_hook(vars.win, KEY_PRESS, 1L << 0, key_press, &vars);
	mlx_hook(vars.win, KEY_RELEASE, 1L << 1, key_release, &vars);
	mlx_hook(vars.win, X_BUTTON, 0, window_close, &vars); // Xボタンに対応
	mlx_loop_hook(vars.mlx, loop_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
