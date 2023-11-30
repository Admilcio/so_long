#include "../so_long.h"

void open_door(t_var *vars)
{
	int width;
	int height;
	if (vars->collectibles_remaining == 0)
		{
			mlx_destroy_image(vars->mlx, vars->door_close);
			vars->door_close = mlx_xpm_file_to_image(vars->mlx, "images/door-open.xpm", &width, &height);
			draw_map(vars);
		}

}