#include "../so_long.h"

void	ft_putchar_lenght(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}