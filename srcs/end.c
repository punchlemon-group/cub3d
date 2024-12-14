/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:48:30 by retanaka          #+#    #+#             */
/*   Updated: 2024/12/14 17:18:51 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	end(t_vars *vars, int status)
{
	if (vars != NULL)
	{
		// free_img(vars);
		// free_map(vars->map);
		if (vars->mlx != NULL && vars->win != NULL)
			mlx_destroy_window(vars->mlx, vars->win);
		if (vars->mlx != NULL)
			mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	exit(status);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map != NULL)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

// void	free_img(t_vars *vars)
// {
// 	if (vars != NULL)
// 	{
// 		if (vars->img_renga != NULL)
// 			mlx_destroy_image(vars->mlx, vars->img_renga);
// 		if (vars->img_grass != NULL)
// 			mlx_destroy_image(vars->mlx, vars->img_grass);
// 		if (vars->img_player->n != NULL)
// 			mlx_destroy_image(vars->mlx, vars->img_player->n);
// 		if (vars->img_player->s != NULL)
// 			mlx_destroy_image(vars->mlx, vars->img_player->s);
// 		if (vars->img_player->e != NULL)
// 			mlx_destroy_image(vars->mlx, vars->img_player->e);
// 		if (vars->img_player->w != NULL)
// 			mlx_destroy_image(vars->mlx, vars->img_player->w);
// 	}
// }

int	window_close(t_vars *vars)
{
	end(vars, 0);
	return (0);
}
