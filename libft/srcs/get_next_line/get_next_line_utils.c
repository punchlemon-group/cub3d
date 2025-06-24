/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <hnakayam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:43:57 by hnakayam          #+#    #+#             */
/*   Updated: 2025/06/24 14:20:16 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	cleanup_get_next_line(void)
{
	char	**mem;

	mem = get_static_mem_addr();
	if (*mem)
	{
		free(*mem);
		*mem = NULL;
	}
}

char	*nobu_strjoin(char const *s1, char const *s2, ssize_t n)
{
	int		total_len;
	char	*ans;
	char	*put;
	ssize_t	i;

	total_len = (int)ft_strlen(s1) + n + 1;
	put = (char *)malloc(sizeof(char) * total_len);
	if (put == NULL)
		return (NULL);
	ans = put;
	i = 0;
	while (*s1)
		*put++ = *s1++;
	while (i < n)
	{
		*put++ = *s2++;
		i++;
	}
	*put = '\0';
	return (ans);
}

ssize_t	nobu_strchar(const char *s, char c)
{
	ssize_t	len;

	len = 0;
	if (!s)
		return (len);
	while (s[len])
	{
		if (s[len] == c)
		{
			len++;
			return (len);
		}
		len++;
	}
	return (len);
}
