#include "so_long.h"

void draw_map(t_map *map)
{
	int x, y;

	for (y = 0; y < map->y; y++)
	{
		for (x = 0; x < map->x; x++)
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
					// Display a static image (e.g., use the first frame)
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
		}
	}
}

// LOOP STARTS HERE

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
			{
				//map->c++;
				map->collectibles_remaining--;
				map->array[new_y][new_x] = '0';
				open_door(map);
			}

		if (map->array[new_y][new_x] != 'E' && map->array[new_y][new_x] != '1')
		{
			// Move the player
			map->array[map->player.y][map->player.x] = '0';
			map->array[new_y][new_x] = 'P';
			map->player.x = new_x;
			map->player.y = new_y;
			map->moves++;
		}

		if (map->collectibles_remaining == 0 && map->array[new_y][new_x] == 'E')
			{
				map->array[map->player.y][map->player.x] = '0';
				map->array[new_y][new_x] = 'P';
				map->player.x = new_x;
				map->player.y = new_y;
				printf( "Congratulations! You collected all collectibles and exited the game.\n");
				exit(0);
			}
			// Redraw the map after the player's movement
			mlx_clear_window(map->mlx, map->wnd);
			draw_map(map);
		
	return (0);
}

void read_player_and_collectibles(t_map *map)
{
	int x, y;

	for (y = 0; y < map->y; y++)
	{
		for (x = 0; x < map->x; x++)
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
		}
	}
}

void flood_fill(char **array, int x, int y, int height, int width, int **accessible) {
    if (x < 0 || x >= width || y < 0 || y >= height || array[y][x] == '1' || accessible[y][x]) {
        return;
    }

    accessible[y][x] = 1;

    flood_fill(array, x + 1, y, height, width, accessible);
    flood_fill(array, x - 1, y, height, width, accessible);
    flood_fill(array, x, y + 1, height, width, accessible);
    flood_fill(array, x, y - 1, height, width, accessible);
}

// Function to check if all collectibles are reachable from the player's position
int all_collectibles_accessible(char **array, int height, int width, t_player player) {
    int **accessible = malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++) {
        accessible[i] = malloc(width * sizeof(int));
        for (int j = 0; j < width; j++) {
            accessible[i][j] = 0;
        }
    }

    // Perform flood-fill starting from the player's position
    flood_fill(array, player.x, player.y, height, width, accessible);

    // Check if any collectibles ('C') are not accessible
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (array[i][j] == 'C' && !accessible[i][j]) {
                // Free the memory used for the accessible array
                for (int k = 0; k < height; k++) {
                    free(accessible[k]);
                }
                free(accessible);
                return 0;  // Not all collectibles are reachable
            }
        }
    }

    // Free the memory used for the accessible array
    for (int i = 0; i < height; i++) {
        free(accessible[i]);
    }
    free(accessible);

    return 1;  // All collectibles are reachable
}

int is_map_viable(char **map, int height, int width) {
    int player_count = 0;
    int collectible_count = 0;
    int exit_door_count = 0;

    // Check the borders for walls
    for (int i = 0; i < height; i++) {
        if (map[i][0] != '1' || map[i][width - 1] != '1') {
            return 0;
        }
    }

    for (int j = 0; j < width; j++) {
        if (map[0][j] != '1' || map[height - 1][j] != '1') {
            return 0;
        }
    }

    // Check the interior for other elements
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            if (map[i][j] == 'P') {
                player_count++;
            } else if (map[i][j] == 'C') {
                collectible_count++;
            } else if (map[i][j] == 'E') {
                exit_door_count++;
            } else if (map[i][j] != '0' && map[i][j] != '1') {
                return 0;
            }
        }
    }

    if (player_count != 1 || collectible_count < 1 || exit_door_count != 1) {
        return 0;
    }

    return 1;
}


void map_array(t_map *map)
{
	int fd;

	map->line = NULL;  // Initialize map->line to NULL
	map->file = NULL;
	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		error_openfile();
	while ((map->line = get_next_line(fd)))
	{
		map->file = ft_strjoinfree(map->file, map->line);
        map->x = ft_strlen(map->line);
		free(map->line);
		if (!map->file)
			ft_exit_free(map);
		map->y++;	
	}
	printf("%d\n", map->y);
	printf("%d\n", map->x); 
	close(fd);

	// Split the file content into arrays
	map->array = ft_split(map->file, '\n');
	map->copy = ft_split(map->file, '\n');
	if (!map->array || !map->copy)
		ft_exit_free(map);
	free(map->file);
	read_player_and_collectibles(map);
}


void map_initializer(t_map *map, char **av)
{
    map->filename = av[1];
    map->moves = 0;
    map->e = 0;
    map->c = 0;
    map->p = 0;
    map->y = 0;
    map->x = 0; 
    map->player.y = 0;
    map->player.x = 0;
    map->exit = 0;
	map->collectibles_remaining = 0;
	map->animation_on = 0;
	map->player_moving = 0;
	map->current_frame = 0;
    map->array = NULL;
}

int	main(int ac, char **av)
{
	t_map	map;
    int width;
    int height;

	if (ac == 2)
	{
		map_initializer(&map, av);
        map_array(&map);
		// map_checker(&map);
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
			//mlx_loop_hook(map.mlx, (int (*)())animation_loop, &map);
			// file_to_image(&map);
			//map_printer(&map);
			// mlx_hook(map.wnd, 17, 0, ft_close, &map);
			// mlx_key_hook(map.wnd, key_hook, &map);
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