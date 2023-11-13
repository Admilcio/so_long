#include "minilibx-linux/mlx.h"
#include "minilibx-linux/mlx_int.h"
#include <stdio.h>
#include <stdlib.h>

#define MALLOC_ERROR    1
#define WIDTH       400
#define HEIGHT      400

typedef struct	s_vars {
	void	*mlx_ptr;
	void	*win;
}				t_vars;

int handle_input(int keysym, t_vars *data)
{
    if(keysym == XK_Escape)
    {
        printf("The %d key (ESC) has been pressed \n\n", keysym);
        mlx_destroy_window(data->mlx_ptr, data->win); 
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
        exit(1);
     }
     printf("The %d key (ESC) has been pressed \n\n", keysym);
     return(0);
}
 
int main(void){
   t_vars data;

   data.mlx_ptr = mlx_init();
   if(data.mlx_ptr == NULL)
        return (1);
   data.win = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "My first window") ;

   if (data.win == NULL)
   {
     mlx_destroy_display(data.mlx_ptr);
     return (1);
   }

  mlx_key_hook(data.win, handle_input, &data);

  mlx_loop(data.mlx_ptr);

}
