/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 04:10:40 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/23 04:31:46 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define MINIMUM_FILE_NAME_LEN 1

int	is_valid_filename(const char *src, const char *extention)
{
	size_t		i;
	size_t		src_len;
	size_t		extention_len;
	const char	*dot_p;

	src_len = ft_strlen(src);
	extention_len = ft_strlen(extention);
	i = 0;
	while (i < src_len)
		i++;
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
	if (argc != 1)
		end(NULL, -1, "Number of arguments is wrong\n");
	is_valid_filename_result = is_valid_filename(argv[0], "cub");
	if (is_valid_filename_result == TOO_SHORT)
		end(NULL, -1, "File name is too short\n");
	if (is_valid_filename_result == NO_EXTENTION)
		end(NULL, -1, "No extention\n");
}

void	create_tiles(t_vars *vars)
{
	int	width;
	int	height;

	vars->north = mlx_xpm_file_to_image(vars->mlx, vars->config.no_path,
			&width, &height);
	if (!vars->north)
		end(vars, -1, "Failed to load north texture");
	vars->east = mlx_xpm_file_to_image(vars->mlx, vars->config.ea_path,
			&width, &height);
	if (!vars->east)
		end(vars, -1, "Failed to load east texture");
	vars->west = mlx_xpm_file_to_image(vars->mlx, vars->config.we_path,
			&width, &height);
	if (!vars->west)
		end(vars, -1, "Failed to load west texture");
	vars->south = mlx_xpm_file_to_image(vars->mlx, vars->config.so_path,
			&width, &height);
	if (!vars->south)
		end(vars, -1, "Failed to load south texture");
}

void	init(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		end(vars, -1, "mlx_init failed\n");
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub2d");
	if (!vars->win)
		end(vars, -1, "mlx_new_window failed\n");
	vars->image_buffer = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!vars->image_buffer)
		end(vars, -1, "\"Image buffer\" was not generated\n");
	create_tiles(vars);
}
