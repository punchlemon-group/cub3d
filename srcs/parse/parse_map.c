/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:44:12 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/23 22:49:21 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	start_map_section(char *line, t_parse_data *data, t_vars *vars)
{
	if (!validate_all_configs(vars))
		return (0);
	data->raw_map = allocate_raw_map();
	if (!data->raw_map)
		return (0);
	if (!is_valid_map_line(line))
	{
		cleanup_raw_map(data->raw_map, data->height);
		error_message_and_free(vars,
			ft_strdup("Invalid character in map"), 1);
	}
	if (ft_strlen(line) > MAX_MAP_WIDTH)
	{
		cleanup_raw_map(data->raw_map, data->height);
		error_message_and_free(vars, ft_strdup("Map size exceeds maximum allowed"), 1);
	}
	if (data->height >= MAX_MAP_HEIGHT)
	{
		cleanup_raw_map(data->raw_map, data->height);
		error_message_and_free(vars, ft_strdup("Map size exceeds maximum allowed"), 1);
	}
	data->raw_map[data->height] = ft_strdup(line);
	if (ft_strlen(line) > (size_t)data->max_width)
		data->max_width = ft_strlen(line);
	data->height++;
	return (1);
}

void	handle_map_line(char *line, t_parse_data *data)
{
	if (ft_strlen(line) > 0)
	{
		if (ft_strlen(line) > MAX_MAP_WIDTH)
		{
			cleanup_raw_map(data->raw_map, data->height);
			error_message_and_free(NULL, ft_strdup("Map size exceeds maximum allowed"), 1);
		}
		if (data->height >= MAX_MAP_HEIGHT)
		{
			cleanup_raw_map(data->raw_map, data->height);
			error_message_and_free(NULL, ft_strdup("Map size exceeds maximum allowed"), 1);
		}
		data->raw_map[data->height] = ft_strdup(line);
		if (ft_strlen(line) > (size_t)data->max_width)
			data->max_width = ft_strlen(line);
		data->height++;
	}
}

void	process_map_line(t_vars *vars, char **line, t_parse_data *data)
{
	if (data->height >= MAX_MAP_HEIGHT)
	{
		cleanup_raw_map(data->raw_map, data->height);
		error_message_and_free(vars, ft_strdup("Map size exceeds maximum allowed"), 1);
	}
	if (ft_strlen(*line) == 0 || is_valid_map_line(*line))
	{
		if (ft_strlen(*line) == 0 && data->height > 0)
		{
			cleanup_raw_map(data->raw_map, data->height);
			free(*line);
			*line = NULL;
			error_message_and_free(vars,
				ft_strdup("Map should not have an empty line"), 1);
		}
		if (ft_strlen(*line) > 0)
			handle_map_line(*line, data);
	}
	else
	{
		cleanup_raw_map(data->raw_map, data->height);
		free(*line);
		*line = NULL;
		error_message_and_free(vars, ft_strdup("Invalid character in map"), 1);
	}
}
