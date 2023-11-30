#include "so_long.h"

int main()
{
	t_var vars;

	const char *map_filename = "map.ber";
	int fd = open(map_filename, O_RDONLY);
	if (fd == -1) {
		perror("Error opening map file");
		return 1;
	}
	char *line;
	int line_number = 0;

	vars.mlx = mlx_init();
	int width, height;
	vars.user_img = mlx_xpm_file_to_image(vars.mlx, "images/player/back.xpm", &width, &height);
	vars.game_bg = mlx_xpm_file_to_image(vars.mlx, "images/gamebg2.xpm", &width, &height);
	vars.door_close = mlx_xpm_file_to_image(vars.mlx, "images/door-close.xpm", &width, &height);
	vars.collectibles = mlx_xpm_file_to_image(vars.mlx, "images/collect.xpm", &width, &height);
	vars.wall_img = mlx_xpm_file_to_image(vars.mlx, "images/wall1_2_.xpm", &width, &height);
	// Load animation frames
	vars.player_frames[0] = mlx_xpm_file_to_image(vars.mlx, "images/player/player02.xpm", &width, &height);
	vars.player_frames[1] = mlx_xpm_file_to_image(vars.mlx, "images/player/player01.xpm", &width, &height);
	vars.player_frames[2] = mlx_xpm_file_to_image(vars.mlx, "images/player/player4.xpm", &width, &height);
	vars.current_frame = 0;
	
	vars.score = 0;
	vars.collectibles_remaining = 0;
	vars.animation_enabled = 0;
	vars.player_moving = 0;

	while ((line = get_next_line(fd)) != NULL && line_number < MAP_HEIGHT)
	{
		process_map_line(&vars, line, line_number);
		free(line);
		line_number++;
	}
	close(fd);

	if (is_map_viable(vars.map) && all_collectibles_accessible(vars.map))
	{
		vars.win = mlx_new_window(vars.mlx,  TILE_SIZE * MAP_WIDTH,TILE_SIZE * MAP_HEIGHT, "SO_LONG");
		mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);
		mlx_hook(vars.win, 3, 1L << 1, key_release, &vars);
		draw_map(&vars);
		mlx_loop_hook(vars.mlx, (int (*)())animation_loop, &vars);
		mlx_loop(vars.mlx);
	} 
	else 
	{
		ft_printf("The map is not viable!\n");
	}
	return 0;
}
