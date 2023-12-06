#include "so_long.h"

int	main(int ac, char **av)
{
	t_map	map;
    int width;
    int height;

	if (ac == 2)
	{
		map_initializer(&map, av);
        map_array(&map);
		map.mlx = mlx_init();
		map.wnd = mlx_new_window(map.mlx, map.x
				* IMG_PXL, map.y * IMG_PXL, WND_NAME);

		t_player player = {map.player.x, map.player.y};

        map.img.wall = mlx_xpm_file_to_image(map.mlx, "images/wall1_2_.xpm", &width, &height);
		map.img.player_up1 = mlx_xpm_file_to_image(map.mlx, "images/player/player4.xpm", &width, &height);
		map.img.collectible = mlx_xpm_file_to_image(map.mlx, "images/collect.xpm", &width, &height);
		map.img.empty = mlx_xpm_file_to_image(map.mlx, "images/gamebg2.xpm", &width, &height);
		map.img.exit = mlx_xpm_file_to_image(map.mlx, "images/door-close.xpm", &width, &height);
		map.img.player_left1 = mlx_xpm_file_to_image(map.mlx, "images/player/back.xpm", &width, &height);
		map.player_frames[0] = mlx_xpm_file_to_image(map.mlx, "images/player/player02.xpm", &width, &height);
		map.player_frames[1] = mlx_xpm_file_to_image(map.mlx, "images/player/player01.xpm", &width, &height);
		map.player_frames[2] = mlx_xpm_file_to_image(map.mlx, "images/player/player4.xpm", &width, &height);
        
		if(all_collectibles_accessible(map.array, map.y, map.x, player) && is_map_viable(map.array, map.y, map.x))
		{
			mlx_hook(map.wnd, 2, 1L << 0, movement, &map);
			mlx_hook(map.wnd, 3, 1L << 1, key_release, &map);
			draw_map(&map);
			mlx_loop(map.mlx);
		}
		else {
        write(1, "The map is not viable!\n", 24);
    }
	}
	else
	{
		write(2, "\033[1;31m🛑ERROR:", 18);
		write(2, "Usage: ./so_long mapfile\n\033[0m", 30);
		exit(EXIT_FAILURE);
	}
}
