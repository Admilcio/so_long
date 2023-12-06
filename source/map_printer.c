#include "../so_long.h"

void draw_map(t_map *map)
{
	int x;
    int y;

    y = 0;
    x = 0;

	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (map->array[y][x] == '1')
			{
				mlx_put_image_to_window(map->mlx, map->wnd, map->img.wall, x * IMG_PXL, y * IMG_PXL);
			}
			else if (map->array[y][x] == 'P')
			{
				if (map->player_moving == 1)
				{
					mlx_put_image_to_window(map->mlx, map->wnd, map->player_frames[map->current_frame], x * IMG_PXL, y * IMG_PXL);
				}
				else if(map->player_moving == 2)
				{
					mlx_put_image_to_window(map->mlx, map->wnd, map->img.player_left1, x * IMG_PXL, y * IMG_PXL);
				}
				else
				{
					mlx_put_image_to_window(map->mlx, map->wnd, map->player_frames[1], x * IMG_PXL, y * IMG_PXL);
				}
			}
			else if (map->array[y][x] == 'C')
			{
				mlx_put_image_to_window(map->mlx, map->wnd, map->img.collectible, x * IMG_PXL, y * IMG_PXL);
			}
			else if (map->array[y][x] == 'E')
			{
				mlx_put_image_to_window(map->mlx, map->wnd, map->img.exit, x * IMG_PXL, y * IMG_PXL);
			}
			else if (map->array[y][x] == '0')
			{
				mlx_put_image_to_window(map->mlx, map->wnd, map->img.empty, x * IMG_PXL, y * IMG_PXL);
			}

			x++;
		}
		y++;
	}
}
