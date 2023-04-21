/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com >  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:57:04 by svalente          #+#    #+#             */
/*   Updated: 2022/11/30 11:44:35 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# define DEC_BASE "0123456789"
# define HEX_UP_BASE "0123456789ABCDEF"
# define HEX_LOW_BASE "0123456789abcdef"

int		ft_printf(const char *s, ...);
int		ft_putchar(int c);
int		ft_putstr(char *str);
int		ft_verify(const char varf, va_list args);
int		ft_putnbr(long long nb);
size_t	ft_strlen(const char *s);
int		ft_putnbrbase(char *base, long long nbr);
int		ft_putnbrpointer(char *base, unsigned long nb, int checker);

#endif