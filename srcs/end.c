/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:48:30 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/23 19:51:05 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"
# include "get_next_line.h"

void	free_map(t_vars *vars)
{
	int	i;

	if (vars->map)
	{
		i = 0;
		while (vars->map[i])
			free(vars->map[i++]);
		free(vars->map);
	}
}

void	free_images(t_vars *vars)
{
	if (vars->north)
		mlx_destroy_image(vars->mlx, vars->north);
	if (vars->east)
		mlx_destroy_image(vars->mlx, vars->east);
	if (vars->west)
		mlx_destroy_image(vars->mlx, vars->west);
	if (vars->south)
		mlx_destroy_image(vars->mlx, vars->south);
	if (vars->image_buffer)
		mlx_destroy_image(vars->mlx, vars->image_buffer);
}

void	end(t_vars *vars, int status, const char *message)
{
	if (message)
		printf("Error\n%s", message);
	if (vars)
	{
		if (vars->mlx)
		{
			if (vars->win)
				mlx_destroy_window(vars->mlx, vars->win);
			free_images(vars);
			mlx_destroy_display(vars->mlx);
			free(vars->mlx);
		}
		free_map(vars);
	}
	cleanup_get_next_line();
	exit(status);
}

int	window_close(t_vars *vars)
{
	end(vars, 0, NULL);
	return (0);
}
