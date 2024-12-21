/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:08:25 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/21 12:46:38 by retanaka         ###   ########.fr       */
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
	vars->north = mlx_xpm_file_to_image(vars->mlx, "texture/isi.xpm",
		&width, &height);
	if (!vars->north)
		end(vars, 0);
	vars->east = mlx_xpm_file_to_image(vars->mlx, "texture/koke_isirenga.xpm",
		&width, &height);
	if (!vars->east)
		end(vars, 0);
	vars->west = mlx_xpm_file_to_image(vars->mlx, "texture/koke_maruisi.xpm",
		&width, &height);
	if (!vars->west)
		end(vars, 0);
	vars->south = mlx_xpm_file_to_image(vars->mlx, "texture/kuro_isirenga.xpm",
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
		vars->rays[i].img = NULL;
		vars->rays[i].x = 0;
		vars->rays[i].len = 1;
		i++;
	}
}

int	init(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < KEY_NUM)
		vars->keys[i++] = 0;
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (END);
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	if (!vars->win)
		return (mlx_destroy_display(vars->mlx), END);
	vars->image_buffer = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!vars->image_buffer)
		return (mlx_destroy_window(vars->mlx, vars->win),
			mlx_destroy_display(vars->mlx), END);
	vars->addr = "maps/test.cub";
	vars->last_calc_time = 0;
	vars->last_disp_time = 0;
	vars->i = 0;
	vars->event_count = 0;
	vars->event_delta_sum = 0;
	return (CNT);
}

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
	get_map_size(&vars);
	get_player(&vars);

	mlx_hook(vars.win, KeyPress, KeyPressMask, key_press, &vars);
	mlx_hook(vars.win, KeyRelease, KeyReleaseMask, key_release, &vars);
	mlx_hook(vars.win, DestroyNotify, NoEventMask, window_close, &vars);
	mlx_loop_hook(vars.mlx, loop_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
