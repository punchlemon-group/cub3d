/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:19:01 by retanaka          #+#    #+#             */
/*   Updated: 2025/06/23 04:33:25 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	**get_map(const char *file)
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
	free(crr_line);
	map = ft_split(linked_lines, '\n');
	free(linked_lines);
	return (map);
}
