/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:05:39 by ada-mata          #+#    #+#             */
/*   Updated: 2023/10/16 12:12:51 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <stdarg.h>

void		ft_putchar_lenght(char c, int *len);
void		ft_putstr(char *args, int *len);

void		ft_putnbr(int number, int *len);
void		ft_hexadecimal(unsigned int n, int *len, char x_or_X);
void		ft_pointer(size_t pointer, int *len);
void		ft_unsigned_int(unsigned int u, int *len);

int			ft_printf(const char *fmt, ...);

#endif
