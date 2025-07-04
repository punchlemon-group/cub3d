/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:00:00 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/23 20:53:36 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "get_next_line.h"

static void	free_config_and_map(t_vars *vars)
{
	int	i;

	if (!vars)
		return ;
	if (vars->config.no_path)
		free(vars->config.no_path);
	if (vars->config.so_path)
		free(vars->config.so_path);
	if (vars->config.we_path)
		free(vars->config.we_path);
	if (vars->config.ea_path)
		free(vars->config.ea_path);
	if (vars->map)
	{
		i = 0;
		while (vars->map[i])
			free(vars->map[i++]);
		free(vars->map);
	}
}

static void	free_mlx_all(t_vars *vars)
{
	if (!vars || !vars->mlx)
		return ;
	if (vars->image_buffer)
		mlx_destroy_image(vars->mlx, vars->image_buffer);
	if (vars->north)
		mlx_destroy_image(vars->mlx, vars->north);
	if (vars->east)
		mlx_destroy_image(vars->mlx, vars->east);
	if (vars->west)
		mlx_destroy_image(vars->mlx, vars->west);
	if (vars->south)
		mlx_destroy_image(vars->mlx, vars->south);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}

void	error_message_and_free(t_vars *vars, char *message, int exit_code)
{
	if (message)
	{
		if (exit_code != 0)
			write(STDERR_FILENO, "Error: ", 7);
		ft_putendl_fd(message, STDERR_FILENO);
		free(message);
	}
	free_config_and_map(vars);
	free_mlx_all(vars);
	cleanup_get_next_line();
	exit(exit_code);
}

void	error_message_and_free_with_line(t_vars *vars, char *message,
		char *line, int exit_code)
{
	if (line)
		free(line);
	error_message_and_free(vars, message, exit_code);
}

int	is_valid_extension(char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strnstr(&filename[len - 4], ".cub", 4) == NULL)
		return (0);
	return (1);
}
