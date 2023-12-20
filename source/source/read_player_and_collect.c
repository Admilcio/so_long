/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_player_and_collect.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:28:31 by ada-mata          #+#    #+#             */
/*   Updated: 2023/12/08 15:28:56 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

void	read_player_and_collectibles(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (map->array[y][x] == 'P')
			{
				map->player.x = x;
				map->player.y = y;
			}
			else if (map->array[y][x] == 'C')
				map->collectibles_remaining++;
			x++;
		}
		y++;
	}
}

void	display_c_and_moves(t_map *map)
{
	ft_printf("Collectibles remaining: %d\n", map->collectibles_remaining);
	ft_printf("Moves: %d\n", map->moves);
}
