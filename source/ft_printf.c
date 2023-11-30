#include "../so_long.h"

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

void	ft_putchar_lenght(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	ft_putstr(char *args, int *len)
{
	int		i;

	i = 0;
	if (!args)
	{
		write(1, "(null)", 6);
		(*len) += 6;
		return ;
	}
	while (args[i])
	{
		ft_putchar_lenght(args[i], len);
		i++;
	}
}

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