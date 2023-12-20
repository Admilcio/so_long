/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:54:33 by ada-mata          #+#    #+#             */
/*   Updated: 2023/12/08 16:41:49 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_map_images(t_map *map)
{
	int		width;
	int		height;

	map->img.wall = mlx_xpm_file_to_image(map->mlx,
			"source/images/wall1_2_.xpm", &width, &height);
	map->img.collectible = mlx_xpm_file_to_image(map->mlx,
			"source/images/collect.xpm", &width, &height);
	map->img.empty = mlx_xpm_file_to_image(map->mlx,
			"source/images/gamebg2.xpm", &width, &height);
	map->img.exit = mlx_xpm_file_to_image(map->mlx,
			"source/images/door-close.xpm", &width, &height);
	map->img.player_left1 = mlx_xpm_file_to_image(map->mlx,
			"source/images/player/back.xpm", &width, &height);
	map->player_frames[0] = mlx_xpm_file_to_image(map->mlx,
			"source/images/player/player02.xpm", &width, &height);
	map->player_frames[1] = mlx_xpm_file_to_image(map->mlx,
			"source/images/player/player01.xpm", &width, &height);
	map->player_frames[2] = mlx_xpm_file_to_image(map->mlx,
			"source/images/player/player4.xpm", &width, &height);
}

void	initialize_functions(t_map *map)
{
	mlx_hook(map->wnd, 2, 1L << 0, movement, map);
	mlx_hook(map->wnd, 3, 1L << 1, key_release, map);
	mlx_hook(map->wnd, 17, 1L << 17, ft_close, map);
	draw_map(map);
	mlx_loop(map->mlx);
}

int	main(int ac, char **av)
{
	t_map		map;
	t_player	player;

	if (ac == 2)
	{
		map_initializer(&map, av);
		map_array(&map);
		player.x = map.player.x;
		player.y = map.player.y;
		if (all_c_accessible(map.array, map.y, map.x, player) 
			&& is_map_viable(map.array, map.y, map.x))
		{
			map.mlx = mlx_init();
			map.wnd = mlx_new_window(map.mlx, map.x * IMG_PXL, map.y * IMG_PXL,
					WND_NAME);
			initialize_map_images(&map);
			initialize_functions(&map);
		}
		else
			error_map(&map);
	}
	else
		error_map_elements(&map);
	ft_close(&map);
	return (0);
}

//cc main.c so_long.a mlx/libmlx.a -lXext -lX11 -g
