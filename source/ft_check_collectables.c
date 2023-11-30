#include "../so_long.h"

void flood_fill(char map[MAP_HEIGHT][MAP_WIDTH], int x, int y, int accessible[MAP_HEIGHT][MAP_WIDTH]) {
	if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT || map[y][x] == '1' || accessible[y][x]) {
		return; // Base case: out of bounds or wall or already visited
	}

	// Mark the current position as visited
	accessible[y][x] = 1;

	// Recursive flood fill in all four directions
	flood_fill(map, x + 1, y, accessible);
	flood_fill(map, x - 1, y, accessible);
	flood_fill(map, x, y + 1, accessible);
	flood_fill(map, x, y - 1, accessible);
}

int all_collectibles_accessible(char map[MAP_HEIGHT][MAP_WIDTH]) {
	int accessible[MAP_HEIGHT][MAP_WIDTH] = {0}; // 0 means not accessible, 1 means accessible

	// Find the player ('P') position
	int player_x = -1, player_y = -1;
	int i = 0;
	
	while (i < MAP_HEIGHT && player_x == -1) {
		int j = 0;
		while (j < MAP_WIDTH && player_x == -1) {
			if (map[i][j] == 'P') {
				player_x = j;
				player_y = i;
			}
			j++;
		}
		i++;
	}

	// Perform flood fill starting from the player position
	flood_fill(map, player_x, player_y, accessible);

	// Check if any collectibles ('C') are not accessible
	i = 0;
	while (i < MAP_HEIGHT) {
		int j = 0;
		while (j < MAP_WIDTH) {
			if (map[i][j] == 'C' && !accessible[i][j]) {
				return 0; // Not all collectibles are accessible
			}
			j++;
		}
		i++;
	}

	return 1; // All collectibles are accessible
}