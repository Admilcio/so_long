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
// Add this function prototype in your so_long.h file

void game_background(t_var *vars)
{
    void *img;
    int img_width, img_height;

    char *img_path = "images/gamebg.xpm";
    img = mlx_xpm_file_to_image(vars->mlx, img_path, &img_width, &img_height);

    if (img == NULL)
    {
        fprintf(stderr, "Error: Failed to load background image\n");
        exit(MALLOC_ERROR);
    }

    mlx_put_image_to_window(vars->mlx, vars->win, img, 0, 0);
}

void draw_map(t_var *vars)
{
    game_background(vars);
    int x, y;

    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            // Draw player ('P') at its current position using the user image
            if (x == vars->player_x && y == vars->player_y)
            {
                mlx_put_image_to_window(vars->mlx, vars->win, vars->user_img, x * TILE_SIZE - 5, y * TILE_SIZE - 10);
            }

            else if (vars->map[y][x] == '1')
            {
                mlx_put_image_to_window(vars->mlx, vars->win, vars->wall_img, x * TILE_SIZE, y * TILE_SIZE);
            }

            // Draw collectibles ('C') at their positions in yellow
            else if (vars->map[y][x] == 'C')
            {
                for (int i = 0; i < TILE_SIZE; i++)
                {
                    for (int j = 0; j < TILE_SIZE; j++)
                    {
                        mlx_pixel_put(vars->mlx, vars->win, x * TILE_SIZE + i, y * TILE_SIZE + j, 0xFFFF00); // Yellow color for collectibles
                    }
                }
            }
            // Draw door ('E') at its position in blue
            else if (vars->map[y][x] == 'E')
            {
                for (int i = 0; i < TILE_SIZE; i++)
                {
                    for (int j = 0; j < TILE_SIZE; j++)
                    {
                        mlx_pixel_put(vars->mlx, vars->win, x * TILE_SIZE + i, y * TILE_SIZE + j, 0x0000FF); // Blue color for door
                    }
                }
            }
            // Draw open spaces ('0') in black
            else if (vars->map[y][x] == '0')
            {
                mlx_put_image_to_window(vars->mlx, vars->win, vars->game_bg, x * TILE_SIZE, y * TILE_SIZE);
            }
        }
    }
}

// Function to handle key presses
int key_press(int keycode, t_var *vars)
{
    int new_x = vars->player_x;
    int new_y = vars->player_y;

    // Handle key presses to move the player
    if (keycode == KEY_RIGHT)
        new_x++;
    else if (keycode == KEY_LEFT)
        new_x--;
    else if (keycode == KEY_UP)
        new_y--;
    else if (keycode == KEY_DOWN)
        new_y++;

    // Check if the new position is an open space ('0'), a collectible ('C'), or a door ('E')
    if (vars->map[new_y][new_x] == '0' || vars->map[new_y][new_x] == 'C' || vars->map[new_y][new_x] == 'E')
    {
        // If it's a collectible, remove it from the map
        if (vars->map[new_y][new_x] == 'C')
        {
            vars->collectibles_remaining--;
            vars->map[new_y][new_x] = '0';
        }

        // Update the player's position
        vars->player_x = new_x;
        vars->player_y = new_y;

        draw_map(vars);

        // Check if all collectibles have been collected and the player is at the door, exit the game
        if (vars->collectibles_remaining == 0 && vars->map[new_y][new_x] == 'E')
        {
            fprintf(stderr, "Congratulations! You collected all collectibles and exited the game.\n");
            exit(0);
        }
    }
}

int main()
{
    t_var vars;
    const char *map_filename = "map"; // Specify the map file name
    FILE *file = fopen(map_filename, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Error: Failed to open map file\n");
        exit(1);
    }

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "My window");
    int width, height;
    vars.user_img = mlx_xpm_file_to_image(vars.mlx, "images/player.xpm", &width, &height);
    vars.game_bg = mlx_xpm_file_to_image(vars.mlx, "images/space.xpm", &width, &height);
    vars.wall_img = mlx_xpm_file_to_image(vars.mlx, "images/wall1_2_.xpm", &width, &height); // Added for the wall image
    vars.player_x = 1; // Initial X position of the player
    vars.player_y = 1; // Initial Y position of the player
    vars.collectibles_remaining = 3; // Initialize collectibles count

    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            fscanf(file, " %c", &vars.map[i][j]);
        }
    }
    fclose(file);

    mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);

    background_img(vars.mlx, vars.win);
    game_background(&vars);
    draw_map(&vars);

    mlx_loop(vars.mlx);
    return 0;
}
