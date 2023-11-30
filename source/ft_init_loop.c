#include "../so_long.h"

void custom_delay(int microseconds) {
	volatile int i = 0;
	while (i < microseconds * 100) {
		i++;
	}
}

int animation_loop(t_var *vars)
{
	if (vars->animation_enabled) 
	{
		vars->current_frame++;

		if (vars->current_frame >= 3) {
			vars->current_frame = 0;
		}
		draw_map(vars);
		custom_delay(1000000);  // 100,000 microseconds = 0.1 seconds
	}
	return 0;
}

void start_animation(t_var *vars)
{
	vars->animation_enabled = 1;  // Set the animation flag to true
	mlx_loop_hook(vars->mlx, (int (*)())animation_loop, vars);  // Start animation loop
}

void stop_animation(t_var *vars) {
	vars->animation_enabled = 0;
	mlx_loop_hook(vars->mlx, NULL, NULL);
}

int key_release(int keycode, t_var *vars)
{
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT || keycode == KEY_UP || keycode == KEY_DOWN) {
		stop_animation(vars);
		vars->player_moving = 0;
	}
	return (0);
}

// Function to handle key presses
int key_press(int keycode, t_var *vars)
{
	int new_x = vars->player_x;
	int new_y = vars->player_y;

   if (keycode == KEY_RIGHT) {
		start_animation(vars);
		 vars->player_moving = 1;
		  new_x++;
	}
	else if (keycode == KEY_LEFT){
		start_animation(vars);
		 vars->player_moving = 2;
		 new_x--;
	}
	else if (keycode == KEY_UP)
		new_y--;
	else if (keycode == KEY_DOWN)
		new_y++;
	else if (keycode == ESC)
		exit(0);
	else
		return (0);


	if (vars->map[new_y][new_x] == 'C')
	{
		vars->collectibles_remaining--;
		vars->map[new_y][new_x] = '0';
		open_door(vars);
	}
   
   if (vars->map[new_y][new_x] != 'E' && vars->map[new_y][new_x] != '1')
   {
		vars->score++;
		vars->map[vars->player_y][vars->player_x] = '0';
		 vars->map[new_y][new_x] = 'P';
		vars->player_x = new_x;
		vars->player_y = new_y;
   }
	if (vars->collectibles_remaining == 0 && vars->map[new_y][new_x] == 'E')
		{
			vars->map[vars->player_y][vars->player_x] = '0';
			vars->map[new_y][new_x] = 'P';
			vars->player_x = new_x;
			vars->player_y = new_y;
			ft_printf( "Congratulations! You collected all collectibles and exited the game.\n");
			exit(0);
		}
	else if(vars->collectibles_remaining != 0 && vars->map[new_y][new_x] == 'E'){
		ft_printf("You need to collect all the items before exiting the game!\n");
	}
	draw_map(vars);
	return (0);
}