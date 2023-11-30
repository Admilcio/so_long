#include "../so_long.h"

void display_score(t_var *vars)
{
	char *score_str = malloc(20);  // Assuming a reasonable buffer size
	sprintf(score_str, "SCORE: %d", vars->score);
	mlx_string_put(vars->mlx, vars->win, 20, 40, 0xFF0000, score_str);
	free(score_str);
}

void display_collectibles(t_var *vars)
{
	char *collect = malloc(20);  // Assuming a reasonable buffer size
	sprintf(collect, "COLLECTIBLES: %d", vars->collectibles_remaining);
	mlx_string_put(vars->mlx, vars->win,20, 65, 0xFF0000, collect);
	free(collect);
}