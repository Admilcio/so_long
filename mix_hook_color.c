#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include <stdio.h>
#include <stdlib.h>

#define MALLOC_ERROR    1
#define WIDTH       800
#define HEIGHT      800

typedef struct	s_vars {
	void	*mlx_ptr;
	void	*win;
    int     color;
}				t_vars;

int f(int keysym, t_vars *data)
{
    printf("Pressed %d\n", keysym);
    sleep(1);
    return (1);
}

int change_color(t_vars *data)
{
    mlx_string_put(data->mlx_ptr, data-> win, 150, 150, data->color, "Color Changing Window");

    if (data->color == 0xFF0000)        // If it's red
        data->color = 0x00FF00;        // Change to green
    else if (data->color == 0x00FF00)   // If it's green
        data->color = 0x0000FF;        // Change to blue
    else
        data->color = 0xFF0000;        // Otherwise, go back to red

    return (0);
}

int     main(void)
{
    t_vars  data;

    data.mlx_ptr = mlx_init();
    data.win = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "Sample Window");
    data.color = 0xFF0000;  // Start with red color  

    mlx_key_hook(data.win,f, &data);
    mlx_loop_hook(data.mlx_ptr, change_color, &data);


    mlx_loop(data.mlx_ptr);
    mlx_clear_window(data.mlx_ptr, data.win);
    mlx_destroy_display(data.win);
    free(data.mlx_ptr);
    return (0);
}