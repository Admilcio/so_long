#include "so_long.h"

void background_img(void *mlx, void *win)
{
    void    *img;
    int     img_width;
    int     img_height;

    char    *img_path = "images/img.xpm";
    img = mlx_xpm_file_to_image(mlx, img_path, &img_width, &img_height);

    if (img == NULL)
    {
        fprintf(stderr, "Error: Failed to load image\n");
        exit(MALLOC_ERROR);
    }

    mlx_put_image_to_window(mlx, win, img, 0, 0);
}

void display_score(t_var *vars)
{
    char *score_str = malloc(20);  // Assuming a reasonable buffer size
    sprintf(score_str, "SCORE: %d", vars->score);
    mlx_string_put(vars->mlx, vars->win, 20, 40, 0xFF0000, score_str);
    free(score_str);
}

void display_collectibles(t_var *vars)
{
    char *collect = malloc(20);  // Assuming a reasonable buffer size
    sprintf(collect, "COLLECTIBLES: %d", vars->collectibles_remaining);
    mlx_string_put(vars->mlx, vars->win,20, 65, 0xFF0000, collect);
    free(collect);
}

void draw_map(t_var *vars)
{
    int x, y;

    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            // Draw player ('P') at its current position using the user image
           if (vars->map[y][x] == 'P')
            {
                mlx_put_image_to_window(vars->mlx, vars->win, vars->user_img, x * TILE_SIZE, y * TILE_SIZE);
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
        }
    }
    display_score(vars);
    display_collectibles(vars);
}

void open_door(t_var *vars)
{
    int width;
    int height;
    if (vars->collectibles_remaining == 0)
        {
            mlx_destroy_image(vars->mlx, vars->door_close);
            vars->door_close = mlx_xpm_file_to_image(vars->mlx, "images/door-open.xpm", &width, &height);
            draw_map(vars);
        }

}
// Function to handle key presses
int key_press(int keycode, t_var *vars)
{
    int new_x = vars->player_x;
    int new_y = vars->player_y;

    // Handle key presses to move the player
    if (keycode == KEY_RIGHT) // Check if it's not a wall
        new_x++;
    else if (keycode == KEY_LEFT)
        new_x--;
    else if (keycode == KEY_UP)
        new_y--;
    else if (keycode == KEY_DOWN)
        new_y++;
    else if (keycode == ESC)
        exit(0);
    else
        return (0);

    // Update the player's position in the map
    if (vars->map[new_y][new_x] == 'C')
    {
        // If it's a collectible, remove it from the map
        vars->collectibles_remaining--;
        vars->map[new_y][new_x] = '0';
        open_door(vars);
    }
    
   
   if (vars->map[new_y][new_x] != 'E' && vars->map[new_y][new_x] != '1')
   {
        vars->score++;
        vars->map[vars->player_y][vars->player_x] = '0';
         vars->map[new_y][new_x] = 'P';
        vars->player_x = new_x;
        vars->player_y = new_y;
   }
    if (vars->collectibles_remaining == 0 && vars->map[new_y][new_x] == 'E')
        {
            vars->map[vars->player_y][vars->player_x] = '0';
            vars->map[new_y][new_x] = 'P';
            vars->player_x = new_x;
            vars->player_y = new_y;
            fprintf(stderr, "Congratulations! You collected all collectibles and exited the game.\n");
            exit(0);
        }
    else if(vars->collectibles_remaining != 0 && vars->map[new_y][new_x] == 'E'){
        fprintf(stderr, "You need to collect all the items before exiting the game!\n");
    }
    //printf("%d\n", vars->score);
    draw_map(vars);
    return (0);
}

void process_map_line(t_var *vars, const char *line, int line_number) {
    // Assuming MAP_WIDTH is known and fixed
    for (int j = 0; j < MAP_WIDTH; j++) 
    {
        vars->map[line_number][j] = line[j];

        // Set the initial player position based on the map
        if (vars->map[line_number][j] == 'P') {
            vars->player_x = j;
            vars->player_y = line_number;
        } else if (vars->map[line_number][j] == 'C') {
            vars->collectibles_remaining++;
        }
    }
}

int is_map_viable(char map[MAP_HEIGHT][MAP_WIDTH]) {
    int player_count = 0;
    int collectible_count = 0;
    int exit_door_count = 0;

    // Check the borders for walls
    for (int i = 0; i < MAP_HEIGHT; i++) {
        if (map[i][0] != '1' || map[i][MAP_WIDTH - 1] != '1') {
            return 0; // Left or right border is not a wall
        }
    }
    for (int j = 0; j < MAP_WIDTH; j++) {
        if (map[0][j] != '1' || map[MAP_HEIGHT - 1][j] != '1') {
            return 0; // Top or bottom border is not a wall
        }
    }

    // Check the interior for other elements
    for (int i = 1; i < MAP_HEIGHT - 1; i++) {
        for (int j = 1; j < MAP_WIDTH - 1; j++) {
            if (map[i][j] == 'P') {
                player_count++;
            } else if (map[i][j] == 'C') {
                collectible_count++;
            } else if (map[i][j] == 'E') {
                exit_door_count++;
            } else if (map[i][j] != '0' && map[i][j] != '1') {
                return 0; // Non-wall and non-open space element found inside the border
            }
        }
    }

    if (player_count != 1 || collectible_count < 1 || exit_door_count != 1) {
        return 0; // Map is not viable
    }

    return 1; // Map is viable
}


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
    vars.user_img = mlx_xpm_file_to_image(vars.mlx, "images/player4.xpm", &width, &height);
    vars.game_bg = mlx_xpm_file_to_image(vars.mlx, "images/gamebg2.xpm", &width, &height);
    vars.door_close = mlx_xpm_file_to_image(vars.mlx, "images/door-close.xpm", &width, &height);
    vars.collectibles = mlx_xpm_file_to_image(vars.mlx, "images/collect.xpm", &width, &height);
    vars.wall_img = mlx_xpm_file_to_image(vars.mlx, "images/wall1_2_.xpm", &width, &height); // Added for the wall image
    vars.score = 0;
    vars.collectibles_remaining = 0;

    while ((line = get_next_line(fd)) != NULL && line_number < MAP_HEIGHT)
    {
        process_map_line(&vars, line, line_number);
        free(line);
        line_number++;
    }
    close(fd);

    if (is_map_viable(vars.map)) 
    {
        vars.win = mlx_new_window(vars.mlx,  TILE_SIZE * MAP_WIDTH,TILE_SIZE * MAP_HEIGHT, "SO_LONG");
        mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);
        background_img(vars.mlx, vars.win);
        draw_map(&vars);
    } 
    else 
    {
        printf("The map is not viable!\n");
    }
    mlx_loop(vars.mlx);
    return 0;
}
