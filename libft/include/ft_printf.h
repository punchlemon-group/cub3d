/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:01:13 by hnakayam          #+#    #+#             */
/*   Updated: 2024/12/06 16:05:57 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"

int		nobu_putstr(char **crr, int *crr_len);
ssize_t	nobu_format(char **crr, int *crr_len, va_list *ap);
int		ft_printf(const char *fmt, ...);
ssize_t	printf_c(char c, int **crr_len);
ssize_t	printf_s(char *str, int **crr_len);
ssize_t	printf_p(void *p, int **crr_len);
ssize_t	printf_d_i(int num, int **crr_len);
ssize_t	printf_u(unsigned int num, int **crr_len);
ssize_t	printf_x(unsigned int num, int **crr_len);
ssize_t	printf_large_x(unsigned int num, int **crr_len);
ssize_t	printf_percent(int **crr_len);
// size_t	ft_strlen(const char *str);
void	calc_digit(unsigned long num, int *count, int base);
int		put_num(unsigned long long num, int digit, int base, char index);

#endif