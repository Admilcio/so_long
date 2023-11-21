#ifndef SO_LONG_H
# define SO_LONG_H

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

// Keycodes
#define KEY_RIGHT       65363
#define KEY_LEFT        65361
#define KEY_UP          65362
#define KEY_DOWN        65364

// Map symbols
#define PLAYER          'P'
#define WALL            '1'
#define COLLECTIBLE     'C'
#define DOOR            'E'
#define OPEN_SPACE      '0'

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
    void    *game_bg;
} t_var;

// Function prototypes
void background_img(void *mlx, void *win);
void draw_map(t_var *vars);
int key_press(int keycode, t_var *vars);

#endif
