#ifndef SO_LONG_H
# define SO_LONG_H

// Get_next_line BUFFER
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

#include "minilibx-linux/mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <fcntl.h> 

#define MALLOC_ERROR    1
//#define WIN_WIDTH       850
//#define WIN_HEIGHT      850
#define TILE_SIZE       85
#define MAP_WIDTH       21
#define MAP_HEIGHT      8

// Keycodes
#define KEY_RIGHT       65363
#define KEY_LEFT        65361
#define KEY_UP          65362
#define KEY_DOWN        65364
#define ESC             65307 

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
    void    *collectibles;
    void    *door_close;
    int     score;
} t_var;

// Function prototypes
void    background_img(void *mlx, void *win);
void    draw_map(t_var *vars);
void	*ft_calloc(size_t count, size_t size);
void	buffer_clear(char *buffer);
void	*ft_memset(void *b, int c, size_t len);
void    process_map_line(t_var *vars, const char *line, int line_number);

int         key_press(int keycode, t_var *vars);
static int  ft_nbrlen(int n);
int	        ft_strlenm(char const *s1);
int         line_updater(char **line, char buffer[]);

char	*ft_itoa(int n);
char	*ft_itoa(int n);
char	*buffer_total_clear(int fd, char **buffer, char *line);
char	*ft_strjoinm(char const *s1, char const *s2);
char	*get_next_line(int fd);

#endif
