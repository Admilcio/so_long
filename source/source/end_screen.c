/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:31:35 by ada-mata          #+#    #+#             */
/*   Updated: 2023/12/08 13:31:38 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

int	ft_free_array(char **ret, int i)
{
	while (i > 0)
		free(ret[--i]);
	free(ret);
	return (0);
}

void	ft_exit_free(t_map *map)
{
	if (map->array)
		free(map->array);
	if (map->file)
		free(map->file);
	if (map->line)
		free(map->file);
	exit(EXIT_FAILURE);
}

int	ft_close(t_map *map)
{
	mlx_destroy_window(map->mlx, map->wnd);
	mlx_destroy_image(map->mlx, map->img.wall);
	mlx_destroy_image(map->mlx, map->img.collectible);
	mlx_destroy_image(map->mlx, map->img.empty);
	mlx_destroy_image(map->mlx, map->img.exit);
	mlx_destroy_image(map->mlx, map->img.player_left1);
	mlx_destroy_image(map->mlx, map->player_frames[0]);
	mlx_destroy_image(map->mlx, map->player_frames[1]);
	mlx_destroy_image(map->mlx, map->player_frames[2]);
	ft_free_array(map->array, map->y);
	mlx_destroy_display(map->mlx);
	free(map->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

void	ft_win(t_map *map)
{
	mlx_destroy_window(map->mlx, map->wnd);
	mlx_destroy_image(map->mlx, map->img.wall);
	mlx_destroy_image(map->mlx, map->img.collectible);
	mlx_destroy_image(map->mlx, map->img.empty);
	mlx_destroy_image(map->mlx, map->img.exit);
	mlx_destroy_image(map->mlx, map->img.player_left1);
	mlx_destroy_image(map->mlx, map->player_frames[0]);
	mlx_destroy_image(map->mlx, map->player_frames[1]);
	mlx_destroy_image(map->mlx, map->player_frames[2]);
	ft_free_array(map->array, map->y);
	mlx_destroy_display(map->mlx);
	free(map->mlx);
	write(1, "\n", 1);
	write(1, "\x1b[32;01m", 9);
	write(1, "🏆🏆YOU WON!!🏆🏆\n", 27);
	write(1, "\x1b[0m", 5);
	exit(EXIT_SUCCESS);
}
