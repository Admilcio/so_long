#include "../so_long.h"

int is_map_viable(char map[MAP_HEIGHT][MAP_WIDTH]) {
	int player_count = 0;
	int collectible_count = 0;
	int exit_door_count = 0;

	// Check the borders for walls
	int i = 0;
	while (i < MAP_HEIGHT) {
		if (map[i][0] != '1' || map[i][MAP_WIDTH - 1] != '1') {
			return (0);
		}
		i++;
	}
	
	int j = 0;
	while (j < MAP_WIDTH) {
		if (map[0][j] != '1' || map[MAP_HEIGHT - 1][j] != '1') {
			return (0);
		}
		j++;
	}

	// Check the interior for other elements
	i = 1;
	while (i < MAP_HEIGHT - 1) {
		j = 1;
		while (j < MAP_WIDTH - 1) {
			if (map[i][j] == 'P') {
				player_count++;
			} else if (map[i][j] == 'C') {
				collectible_count++;
			} else if (map[i][j] == 'E') {
				exit_door_count++;
			} else if (map[i][j] != '0' && map[i][j] != '1') {
				return (0);
			}
			j++;
		}
		i++;
	}

	if (player_count != 1 || collectible_count < 1 || exit_door_count != 1) {
		return 0; 
	}

	return (1);
}

void draw_map(t_var *vars)
{
	int x, y;
	
	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			// Draw player ('P') at its current position using the user image
			if (vars->map[y][x] == 'P')
			{
				if (vars->player_moving == 1)
				{
					mlx_put_image_to_window(vars->mlx, vars->win, vars->player_frames[vars->current_frame], x * TILE_SIZE, y * TILE_SIZE);
				}
				else if(vars->player_moving == 2)
				{
					mlx_put_image_to_window(vars->mlx, vars->win, vars->user_img, x * TILE_SIZE, y * TILE_SIZE);
				}
				else
				{
					// Display a static image (e.g., use the first frame)
					mlx_put_image_to_window(vars->mlx, vars->win, vars->player_frames[1], x * TILE_SIZE, y * TILE_SIZE);
				}
			}
			else if (vars->map[y][x] == '1')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, vars->wall_img, x * TILE_SIZE, y * TILE_SIZE);
			}
			// Draw collectibles ('C') at their positions in yellow
			else if (vars->map[y][x] == 'C')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, vars->collectibles, x * TILE_SIZE, y * TILE_SIZE);
			}
			// Draw door ('E') at its position in blue
			else if (vars->map[y][x] == 'E')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, vars->door_close, x * TILE_SIZE, y * TILE_SIZE);
			}
			// Draw open spaces ('0') in black
			else if (vars->map[y][x] == '0')
			{
				mlx_put_image_to_window(vars->mlx, vars->win, vars->game_bg, x * TILE_SIZE, y * TILE_SIZE);
			}
			
			x++;
		}
		
		y++;
	}

	display_score(vars);
	display_collectibles(vars);
}

void process_map_line(t_var *vars, const char *line, int line_number) {
	int j = 0;
	while (j < MAP_WIDTH) {
		vars->map[line_number][j] = line[j];

		// Set the initial player position based on the map
		if (vars->map[line_number][j] == 'P') {
			vars->player_x = j;
			vars->player_y = line_number;
		} else if (vars->map[line_number][j] == 'C') {
			vars->collectibles_remaining++;
		}

		j++;
	}
}
