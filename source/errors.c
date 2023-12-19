/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:33:46 by ada-mata          #+#    #+#             */
/*   Updated: 2023/12/08 15:45:40 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	error_filename(void)
{
	write(2, "\033[1;31m🛑ERROR: ", 19);
	write(2, "Filename should be a BER extension file\n\033[0m", 45);
	exit(EXIT_FAILURE);
}

void	error_openfile(void)
{
	write(2, "\033[1;31m🛑ERROR: ", 19);
	write(2, "failed open\n\033[0m", 17);
	exit(EXIT_FAILURE);
}

void	error_map(t_map *map)
{
	write(2, "\033[1;31m🛑ERROR: ", 19);
	write(2, "Map not Viable\n\033[0m", 17);
	ft_free_array(map->array, map->y);
	exit(EXIT_FAILURE);
}

void	error_map_elements(t_map *map)
{
	write(2, "\033[1;31m🛑ERROR: ", 19);
	write(2, "failed number of elements\n\033[0m", 30);
	ft_free_array(map->array, map->y);
	exit(EXIT_FAILURE);
}

void	error_opendoor(void)
{
	write(2, "\033[1;31m🛑ERROR: ", 19);
	write(2, "You need to collect all the C first\n\033[0m", 41);
}
