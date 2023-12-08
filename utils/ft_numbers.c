/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:06:05 by ada-mata          #+#    #+#             */
/*   Updated: 2023/11/13 15:26:34 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int number, int *len)
{
	if (number == -2147483648)
	{
		write (1, "-2147483648", 11);
		(*len) += 11;
		return ;
	}
	if (number < 0)
	{
		number *= -1;
		ft_putchar_lenght('-', len);
		ft_putnbr(number, len);
	}
	else
	{
		if (number >= 10) 
			ft_putnbr((number / 10), len);
		ft_putchar_lenght((number % 10 + '0'), len);
	}
}

void	ft_hexadecimal(unsigned int n, int *len, char x_or_X)
{
	char	*base;
	char	string[25];
	int		i;

	if (x_or_X == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	i = 0;
	if (n == 0)
	{
		ft_putchar_lenght('0', len);
		return ;
	}
	while (n != 0)
	{
		string[i] = base [n % 16];
		n = n / 16;
		i++;
	}
	while (i--)
	{
		ft_putchar_lenght(string[i], len);
	}
}

void	ft_pointer(size_t pointer, int *len)
{
	char	*base;
	char	string[25];
	int		i;

	base = "0123456789abcdef";
	i = 0;
	if (pointer == 0)
	{
		write(1, "(nil)", 5);
		(*len) += 5;
		return ;
	}
	write(1, "0x", 2);
	(*len) += 2;
	while (pointer != 0)
	{
		string[i] = base[pointer % 16];
		pointer = pointer / 16;
		i++;
	}
	while (i--)
	{
		ft_putchar_lenght(string[i], len);
	}
}

void	ft_unsigned_int(unsigned int u, int *len)
{
	if (u >= 10)
		ft_unsigned_int(u / 10, len);
	ft_putchar_lenght((u % 10 + '0'), len);
}
