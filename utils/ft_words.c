/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:05:39 by ada-mata          #+#    #+#             */
/*   Updated: 2023/10/16 12:12:51 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
