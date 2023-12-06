#include "../so_long.h"

void custom_delay(int microseconds) {
	volatile int i = 0;
	while (i < microseconds * 100) {
		i++;
	}
}

int animation_loop(t_map *map)
{
	if (map->animation_on == 1)
	{
		map->current_frame++;

		if (map->current_frame >= 3)
			map->current_frame = 0;
		draw_map(map);
		custom_delay(1000000); 
	}
	return (0);
}

void start_animation(t_map *map)
{
	map->animation_on = 1;  // Set the animation flag to true
	mlx_loop_hook(map->mlx, (int (*)())animation_loop, map);  // Start animation loop
}

void stop_animation(t_map *map) {
	map->animation_on = 0;
	mlx_loop_hook(map->mlx, NULL, NULL);
}

int key_release(int keycode, t_map *map)
{
	if (keycode == RIGHT || keycode == LEFT || keycode == UP || keycode == DOWN) {
		stop_animation(map);
		map->player_moving = 0;
	}
	return (0);
}