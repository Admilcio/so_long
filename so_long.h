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
# include <stdarg.h>
# include <string.h>


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
    void    *player_frames[3];
    int     score;
    int     current_frame;
    int     animation_enabled;
    int     player_moving;
} t_var;

// Function prototypes
void    background_img(void *mlx, void *win);
void    draw_map(t_var *vars);
void	buffer_clear(char *buffer);
void    process_map_line(t_var *vars, const char *line, int line_number);
void	ft_putnbr(int number, int *len);
void	ft_hexadecimal(unsigned int n, int *len, char x_or_X);
void	ft_pointer(size_t pointer, int *len);
void	ft_unsigned_int(unsigned int u, int *len);
void	ft_putchar_lenght(char c, int *len);
void	ft_putstr(char *args, int *len);
void    open_door(t_var *vars);
void    display_collectibles(t_var *vars);
void    display_score(t_var *vars);
void    flood_fill(char map[MAP_HEIGHT][MAP_WIDTH], int x, int y, int accessible[MAP_HEIGHT][MAP_WIDTH]);

int         key_press(int keycode, t_var *vars);
int     key_release(int keycode, t_var *vars);
int     is_map_viable(char map[MAP_HEIGHT][MAP_WIDTH]);
void	ft_format_checker(char s, va_list *args, int *len, int i);
int	        ft_strlenm(char const *s1);
int         line_updater(char **line, char buffer[]);
int     ft_printf(const char *string, ...);
int     animation_loop(t_var *vars);
int     all_collectibles_accessible(char map[MAP_HEIGHT][MAP_WIDTH]);

char	*buffer_total_clear(int fd, char **buffer, char *line);
char	*ft_strjoinm(char const *s1, char const *s2);
char	*get_next_line(int fd);

#endif
