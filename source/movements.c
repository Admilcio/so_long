#include "../so_long.h"

void open_door(t_map *map)
{
	int width;
	int height;
	if (map->collectibles_remaining == 0)
		{
			mlx_destroy_image(map->mlx, map->img.exit);
			map->img.exit = mlx_xpm_file_to_image(map->mlx, "images/door-open.xpm", &width, &height);
			draw_map(map);
		}
}

void move_player(t_map *map, int new_x, int new_y)
{
	map->array[map->player.y][map->player.x] = '0';
	map->array[new_y][new_x] = 'P';
	map->player.x = new_x;
	map->player.y = new_y;
}

void exit_game(t_map *map, int new_x, int new_y)
{
	map->array[map->player.y][map->player.x] = '0';
	map->array[new_y][new_x] = 'P';
	map->player.x = new_x;
	map->player.y = new_y;
	ft_win(map);
	exit(0);
}

void check_collectibles(t_map *map, int new_x, int new_y)
{
			map->collectibles_remaining--;
			map->array[new_y][new_x] = '0';
			open_door(map);
}

int movement(int keycode, t_map *map)
{
	int new_x = map->player.x;
	int new_y = map->player.y;

	if (keycode == UP)
		new_y--;
	else if (keycode == DOWN)
		new_y++;
	else if (keycode == LEFT)
	{
		new_x--;
		start_animation(map);
		map->player_moving = 2;
	}
	else if (keycode == RIGHT)
	{
		new_x++;
		start_animation(map);
		map->player_moving = 1;
	}
	else if (keycode == ESC)
		exit(0);

	if (map->array[new_y][new_x] == 'C')
		check_collectibles(map, new_x, new_y);
	if (map->array[new_y][new_x] != 'E' && map->array[new_y][new_x] != '1')
		move_player(map, new_x, new_y);
	if (map->collectibles_remaining == 0 && map->array[new_y][new_x] == 'E')
		exit_game(map, new_x, new_y);
	else if (map->collectibles_remaining != 0 && map->array[new_y][new_x] == 'E')
		error_opendoor();
	mlx_clear_window(map->mlx, map->wnd);
	draw_map(map);		
	return (0);
}