/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:00:40 by ada-mata          #+#    #+#             */
/*   Updated: 2023/12/08 16:00:42 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <stdarg.h>
# include <limits.h>

# define UP      65362
# define DOWN    65364
# define LEFT    65361
# define RIGHT   65363
# define ESC     65307
# define IMG_PXL 85
# define WND_NAME "so_long"

typedef struct s_player
{
	int	y;
	int	x;

}t_player;

typedef struct s_img
{
	void	*empty;
	void	*collectible;
	void	*wall;
	void	*exit;
	void	*player_left1;
	void	*player_right1;
}t_img;

typedef struct s_map
{
	int			fd;
	char		*line;
	char		*file;
	char		**array;
	char		**accessible;
	char		*filename;
	int			y;
	int			x;
	int			width;
	int			height;
	int			collectibles_remaining;
	int			animation_on;
	int			current_frame;
	int			player_moving;
	int			exit;
	int			moves;
	void		*mlx;
	void		*wnd;
	void		*player_frames[3];
	t_img		img;
	t_player	player;

}t_map;

void	error_openfile(void);
void	error_map(t_map *map);
void	error_openfile(void);
void	custom_delay(int microseconds);
void	start_animation(t_map *map);
void	error_map_elements(t_map *map);
void	ft_putchar_lenght(char c, int *len);
void	stop_animation(t_map *map);
void	ft_win(t_map *map);
void	map_initializer(t_map *map, char **av);
void	read_player_and_collectibles(t_map *map);
void	map_array(t_map *map);
void	draw_map(t_map *map);
void	open_door(t_map *map);
void	ft_exit_free(t_map *map);
void	error_opendoor(void);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	display_c_and_moves(t_map *map);
void	ft_putchar_lenght(char c, int *len);
void	ft_putstr(char *args, int *len);
void	ft_putnbr(int number, int *len);
void	ft_hexadecimal(unsigned int n, int *len, char x_or_X);
void	ft_pointer(size_t pointer, int *len);
void	ft_unsigned_int(unsigned int u, int *len);
void	ft_format_checker(char s, va_list *args, int *len, int i);
void	flood_fill(int x, int y, t_map *map);
void	open_door(t_map *map);
void	move_player(t_map *map, int new_x, int new_y);
void	exit_game(t_map *map, int new_x, int new_y);
void	check_collectibles(t_map *map, int new_x, int new_y);

char	*ft_strjoinfree(char *s1, char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);

int		ft_close(t_map *map);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_printf(const char *string, ...);
int		movement(int keycode, t_map *map);
int		is_map_viable(char **map, int height, int width);
int		animation_loop(t_map *map);
int		key_release(int keycode, t_map *map);
int		ft_free_array(char **ret, int i);
int		all_c_accessible(char **array, int height, int width, t_player player);

size_t	ft_strlen(const char *str);
#endif
