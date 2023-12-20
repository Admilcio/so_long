/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:05:39 by ada-mata          #+#    #+#             */
/*   Updated: 2023/12/07 15:46:19 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_format_checker(char s, va_list *args, int *len, int i)
{
	if (s == 's')
		ft_putstr(va_arg(*args, char *), len);
	else if (s == 'd' || s == 'i')
		ft_putnbr(va_arg(*args, int), len);
	else if (s == 'u')
		ft_unsigned_int(va_arg(*args, unsigned int), len);
	else if (s == 'x')
		ft_hexadecimal(va_arg(*args, unsigned int), len, 'x');
	else if (s == 'X')
		ft_hexadecimal(va_arg(*args, unsigned int), len, 'X');
	else if (s == 'p')
		ft_pointer(va_arg(*args, size_t), len);
	else if (s == 'c')
		ft_putchar_lenght(va_arg(*args, int), len);
	else if (s == '%')
		ft_putchar_lenght('%', len);
	else 
		i--;
}

int	ft_printf(const char *string, ...)
{
	int			i;
	int			len;
	va_list		args;

	i = 0;
	len = 0;
	va_start(args, string);
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			i++;
			ft_format_checker(string[i], &args, &len, i);
			i++;
		}
		else
		{
			ft_putchar_lenght(string[i], &len);
			i++;
		}
	}
	va_end(args);
	return (len);
}
/* 
#include <stdio.h>
int main ()
{
	char *line;
	int i;
	int i2;

	line = NULL;
	i = ft_printf ("%%, %c, agora e uma string %s, %d, %i,
	 %u, %x, %X, %p, %p\n", 'c', line, 42, -42, 2147483647, 15, 15, &line, line);
	i2 = printf ("%%, %c, agora e uma string %s, %d, %i, 
	%u, %x, %X, %p, %p\n", 'c', line, 42, -42, 2147483647, 15, 15, &line, line);

	printf ("i = %i\n", i);
	printf ("i = %i\n", i2);
}*/ 
