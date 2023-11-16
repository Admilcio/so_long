#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define MALLOC_ERROR    1
#define WIDTH       400
#define HEIGHT      400

int main()
{
    void *mlx_connection;
    void *mlx_window;

    void	*img;
	char	*relative_path = "./img_bg.xpm";
	int		img_width = 30;
	int		img_height = 30;



    mlx_connection = mlx_init();
    img = mlx_xpm_file_to_image(mlx_connection, relative_path, &img_width, &img_height);
    
    if(NULL == mlx_connection)
        return(MALLOC_ERROR);
    
    mlx_window = mlx_new_window(mlx_connection, HEIGHT, WIDTH,"MY window");
    if (NULL == mlx_window)
    {
        mlx_destroy_display(mlx_connection);
        free(mlx_connection);
        return (MALLOC_ERROR);
    }

    mlx_loop(mlx_connection);
    mlx_clear_window(mlx_connection, mlx_window);
    mlx_destroy_display(mlx_window);
    free(mlx_connection);
}