/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:45:41 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/23 20:23:39 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_empty_line(char *line, int in_map_section, t_vars *vars)
{
	free(line);
	if (in_map_section)
		error_message_and_free(vars,
			ft_strdup("Map should not have an empty line"), 1);
}
