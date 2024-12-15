/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:48:30 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/15 16:52:17 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	free_tiles(t_vars *vars)
{
	if (vars->north)
		mlx_destroy_image(vars->mlx, vars->north);
	if (vars->east)
		mlx_destroy_image(vars->mlx, vars->east);
	if (vars->west)
		mlx_destroy_image(vars->mlx, vars->west);
	if (vars->south)
		mlx_destroy_image(vars->mlx, vars->south);
}

void	end(t_vars *vars, int status)
{
	free_map(vars->map);
	free_tiles(vars);
	mlx_destroy_image(vars->mlx, vars->image_buffer);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(status);
}

int	window_close(t_vars *vars)
{
	end(vars, 0);
	return (0);
}
