#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include <stdio.h>
#include <stdlib.h>

#define MALLOC_ERROR    1
#define WIDTH       400
#define HEIGHT      400

typedef struct  s_data
{
    void        *mlx_ptr;
    void        *win_ptr;
}               t_data;

int     button_press(int button, int x, int y, t_data *data)
{
    if (button == 1)
        printf("Left mouse button pressed at (%d, %d)!\n", x, y);
    else if (button == 3)
        printf("Right mouse button pressed at (%d, %d)!\n", x, y);

    return (0);
}

int     main(void)
{
    t_data  data;

    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "MLX Window");
    mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, &button_press, &data);

    mlx_loop(data.mlx_ptr);
    mlx_clear_window(data.mlx_ptr, data.win_ptr);
    mlx_destroy_display(data.win_ptr);
    free(data.mlx_ptr);
    return (0);
}