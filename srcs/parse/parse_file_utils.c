/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:45:41 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/23 19:17:25 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_empty_line(char *line, int in_map_section, t_vars *vars, t_parse_data *data)
{
	free(line);
	if (in_map_section)
	{
		if (data && data->raw_map)
			cleanup_raw_map(data->raw_map, data->height);
		error_message_and_free(vars, ft_strdup("Map should not have an empty line"), 1);
	}
}
