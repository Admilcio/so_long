#include "../so_long.h"

void read_player_and_collectibles(t_map *map)
{
	int x = 0, y = 0;

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
			{
				//map->c++;
				map->collectibles_remaining++;
			}

			x++;
		}
		y++;
	}
}
