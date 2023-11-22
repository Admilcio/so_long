// #include <unistd.h>

// int main (int ac, char ** av)
// {    
//     int i = 0;
//     char *str = av[1];
//     int flag = 0;

//     if (ac == 2)
//     {
//         while(str[i])
//         {
//             while(str[i] && (str[i] == 32 || str[i] == 9))
//                 i++;
//             if(flag == 1 && str[i])
//                 write(1, "   ", 1);
//             flag = 0;
//             while(str[i] && (str[i] != 32 && str[i] != 9))
//             {
//                 write(1, &str[i], 1);
//                 i++;
//                 flag = 1;
//             }
//         }
//     }
//     //write(1, "\n", 1);

// }


#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MALLOC_ERROR    1
#define WIN_WIDTH       850
#define WIN_HEIGHT      850
#define TILE_SIZE       85
#define MAP_WIDTH       10
#define MAP_HEIGHT      10
//#define NUM_COLLECTIBLES 6

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
    void    *wall_img;
    void    *user_img;
}               t_var;

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
                mlx_put_image_to_window(vars->mlx, vars->win, vars->door, x * TILE_SIZE, y * TILE_SIZE);
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
    return(0);
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
    vars.win = mlx_new_window(vars.mlx,  TILE_SIZE * MAP_WIDTH,TILE_SIZE * MAP_HEIGHT, "My window");
    int width, height;
    vars.user_img = mlx_xpm_file_to_image(vars.mlx, "images/player4.xpm", &width, &height);
    vars.game_bg = mlx_xpm_file_to_image(vars.mlx, "images/gamebg2.xpm", &width, &height);
    vars.door = mlx_xpm_file_to_image(vars.mlx, "images/door2.xpm", &width, &height);
    vars.collectibles = mlx_xpm_file_to_image(vars.mlx, "images/collect.xpm", &width, &height);
    vars.wall_img = mlx_xpm_file_to_image(vars.mlx, "images/wall1_2_.xpm", &width, &height); // Added for the wall image
    vars.player_x = 1; // Initial X position of the player
    vars.player_y = 2; // Initial Y position of the player
    vars.collectibles_remaining = 8; // Initialize collectibles count

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
    draw_map(&vars);

    mlx_loop(vars.mlx);
    return 0;
}

