#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MALLOC_ERROR    1
#define WIN_WIDTH       1200
#define WIN_HEIGHT      800
#define TILE_SIZE       80
#define MAP_WIDTH       10
#define MAP_HEIGHT      10
#define NUM_COLLECTIBLES 6

typedef struct s_var
{
    void    *mlx;
    void    *win;
    int     player_x;
    int     player_y;
    int     width;
    int     height;
    char    map[MAP_HEIGHT][MAP_WIDTH];
    int     collectibles_remaining;
    void    *user_img;
}               t_var;

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

void draw_map(t_var *vars)
{
    int x, y;

    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            // Draw player ('P') at its current position using the user image
            if (x == vars->player_x && y == vars->player_y)
            {
                mlx_put_image_to_window(vars->mlx, vars->win, vars->user_img, x * TILE_SIZE, y * TILE_SIZE);
            }

            else if (vars->map[y][x] == '1')
            {
                for (int i = 0; i < TILE_SIZE; i++)
                {
                    for (int j = 0; j < TILE_SIZE; j++)
                    {
                        mlx_pixel_put(vars->mlx, vars->win, x * TILE_SIZE + i, y * TILE_SIZE + j, 0xffffff); // Yellow color for collectibles
                    }
                }
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
                for (int i = 0; i < TILE_SIZE; i++)
                {
                    for (int j = 0; j < TILE_SIZE; j++)
                    {
                        mlx_pixel_put(vars->mlx, vars->win, x * TILE_SIZE + i, y * TILE_SIZE + j, 0x000000); // Black color for open spaces
                    }
                }
            }
        }
    }
}


// Function to initialize collectibles in random positions
void initialize_collectibles(t_var *vars)
{
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Place collectibles ('C') in random positions on the map
    for (int i = 0; i < NUM_COLLECTIBLES; i++)
    {
        int rand_x, rand_y;
        do
        {
            rand_x = rand() % MAP_WIDTH;
            rand_y = rand() % MAP_HEIGHT;
        } while (vars->map[rand_y][rand_x] != '0'); // Repeat if the chosen position is not an open space

        vars->map[rand_y][rand_x] = 'C';
    }
}

// Function to handle key presses
int key_press(int keycode, t_var *vars)
{
    int new_x = vars->player_x;
    int new_y = vars->player_y;

    // Handle key presses to move the player
    if (keycode == 65363) // Right arrow key
        new_x = (vars->player_x + 1) % MAP_WIDTH;
    else if (keycode == 65361) // Left arrow key
        new_x = (vars->player_x - 1 + MAP_WIDTH) % MAP_WIDTH;
    else if (keycode == 65362) // Up arrow key
        new_y = (vars->player_y - 1 + MAP_HEIGHT) % MAP_HEIGHT;
    else if (keycode == 65364) // Down arrow key
        new_y = (vars->player_y + 1) % MAP_HEIGHT;

    // Check if the new position is an open space ('0'), a collectible ('C'), or a door ('E')
    if (vars->map[new_y][new_x] == '0' || vars->map[new_y][new_x] == 'C' || vars->map[new_y][new_x] == 'E')
    {
        // If it's a collectible, remove it from the map
        if (vars->map[new_y][new_x] == 'C')
        {
            vars->map[new_y][new_x] = '0';
            vars->collectibles_remaining++;
        }

        // Update the player's position
        vars->player_x = new_x;
        vars->player_y = new_y;

        mlx_clear_window(vars->mlx, vars->win);
        background_img(vars->mlx, vars->win);
        draw_map(vars);

        // Check if all collectibles have been collected and the player is at the door, exit the game
        if (vars->collectibles_remaining == NUM_COLLECTIBLES && vars->map[new_y][new_x] == 'E')
        {
            fprintf(stderr, "Congratulations! You collected all collectibles and exited the game.\n");
            exit(0);
        }
    }

    return (0);
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
    vars.user_img = mlx_xpm_file_to_image(vars.mlx, "images/front.xpm", &width, &height);
    vars.player_x = 1; // Initial X position of the player
    vars.player_y = 1; // Initial Y position of the player
    vars.collectibles_remaining = 0; // Initialize collectibles count

    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            fscanf(file, " %c", &vars.map[i][j]);
            if (vars.map[i][j] == 'C')
            {
                vars.collectibles_remaining++;
            }
        }
    }

    fclose(file);

    // Initialize collectibles in random positions
    initialize_collectibles(&vars);

    mlx_hook(vars.win, 2, 1L << 0, key_press, &vars);

    background_img(vars.mlx, vars.win);
    draw_map(&vars);

    mlx_loop(vars.mlx);

    return 0;
}
