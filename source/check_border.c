/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:28:44 by ada-mata          #+#    #+#             */
/*   Updated: 2023/12/08 13:28:48 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	are_borders_valid(char **map, int height, int width)
{
	int		i;
	int		j;

	i = 0;
	while (++i < height)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
	}
	j = 0;
	while (++j < width)
	{
		if (map[0][j] != '1' || map[height - 1][j] != '1')
			return (0);
	}
	return (1);
}

int	check_element(char element, int *p_count, int *c_count, int *e_door_count)
{
	if (element == 'P')
		(*p_count)++;
	else if (element == 'C')
		(*c_count)++;
	else if (element == 'E')
		(*e_door_count)++;
	else if (element != '0' && element != '1')
		return (0);
	return (1);
}

int	are_interior_elements_valid(char **map, int height, int width)
{
	int		p_count;
	int		c_count;
	int		e_door_count;
	int		i;
	int		j;

	p_count = 0;
	c_count = 0;
	e_door_count = 0;
	i = 1;
	while (i < height - 1)
	{
		j = 1;
		while (j < width - 1)
		{
			if (!check_element(map[i][j], &p_count, &c_count, &e_door_count))
				return (0);
			j++;
		}
		i++;
	}
	if (p_count != 1 || c_count < 1 || e_door_count != 1)
		return (0);
	return (1); 
}

int	is_map_viable(char **map, int height, int width)
{
	if (!are_borders_valid(map, height, width)
		|| !are_interior_elements_valid(map, height, width))
		return (0);
	return (1);
}
