/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnakayam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:09:03 by hnakayam          #+#    #+#             */
/*   Updated: 2024/08/26 11:09:06 by hnakayam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*nobu_strcpy(char *ans, char const *s, int start, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ans[i] = s[start + i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

static void	all_free(char **ans, int i)
{
	while (i > 0)
	{
		i--;
		free(ans[i]);
	}
	free(ans);
}

static int	count_words(char const *s, char c)
{
	int	count;
	int	flag;
	int	i;

	count = 0;
	flag = 0;
	i = 0;
	while (s[i])
	{
		if (flag == 0 && s[i] != c)
		{
			count++;
			flag = 1;
		}
		else if (flag == 1 && s[i] == c)
		{
			flag = 0;
		}
		i++;
	}
	return (count);
}

static char	**rest_of_split(char const *s, char c, char **ans, int count)
{
	int	i;
	int	start;
	int	len;

	start = 0;
	i = 0;
	while (i < count)
	{
		while (s[start] == c)
			start++;
		len = 0;
		while (s[start + len] != c && s[start + len])
			len++;
		ans[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (ans[i] == NULL)
		{
			all_free(ans, i);
			return (NULL);
		}
		nobu_strcpy(ans[i], s, start, len);
		i++;
		start += len;
	}
	ans[i] = NULL;
	return (ans);
}

char	**ft_split(char const *s, char c)
{
	char	**ans;
	int		count;

	if (s == NULL)
		return (NULL);
	count = count_words(s, c);
	ans = (char **)malloc(sizeof(char *) * (count + 1));
	if (ans == NULL)
		return (NULL);
	return (rest_of_split(s, c, ans, count));
}

// int	main(void)
// {
// 	char	**res;
// 	int		i;

// 	i = 0;
// 	res = ft_split(" I my me mine ", ' ');
// 	while (res[i] != NULL)
// 	{
// 		printf("%s\n", res[i]);
// 		i++;
// 	}
// 	return (0);
// }

// #include <libc.h>

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q a.out");
// }
