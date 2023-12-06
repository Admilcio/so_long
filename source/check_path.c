#include "../so_long.h"

void flood_fill(char **array, int x, int y, int height, int width, int **accessible) {
    if (x < 0 || x >= width || y < 0 || y >= height || array[y][x] == '1' || accessible[y][x]) {
        return;
    }

    accessible[y][x] = 1;

    flood_fill(array, x + 1, y, height, width, accessible);
    flood_fill(array, x - 1, y, height, width, accessible);
    flood_fill(array, x, y + 1, height, width, accessible);
    flood_fill(array, x, y - 1, height, width, accessible);
}

// Function to check if all collectibles are reachable from the player's position
int all_collectibles_accessible(char **array, int height, int width, t_player player) {
    int **accessible = malloc(height * sizeof(int *));
    int i = 0;

    while (i < height) {
        accessible[i] = malloc(width * sizeof(int));
        int j = 0;

        while (j < width) {
            accessible[i][j] = 0;
            j++;
        }
        i++;
    }

    // Perform flood-fill starting from the player's position
    flood_fill(array, player.x, player.y, height, width, accessible);

    // Check if any collectibles ('C') are not accessible
    i = 0;
    while (i < height) {
        int j = 0;

        while (j < width) {
            if (array[i][j] == 'C' && !accessible[i][j]) {
                // Free the memory used for the accessible array
                int k = 0;

                while (k < height) {
                    free(accessible[k]);
                    k++;
                }
                free(accessible);
                return 0;  // Not all collectibles are reachable
            }
            j++;
        }
        i++;
    }
    // Free the memory used for the accessible array
    i = 0;

    while (i < height) {
        free(accessible[i]);
        i++;
    }
    free(accessible);

    return 1;  // All collectibles are reachable
}

// Function to check if the borders of the map have walls ('1')
int are_borders_valid(char **map, int height, int width) {
    int i = 0;

    while (i < height) {
        if (map[i][0] != '1' || map[i][width - 1] != '1') {
            return 0; // Invalid border
        }
        i++;
    }

    int j = 0;

    while (j < width) {
        if (map[0][j] != '1' || map[height - 1][j] != '1') {
            return 0; // Invalid border
        }
        j++;
    }

    return 1; // Borders are valid
}

// Function to check if the interior elements of the map are valid
int are_interior_elements_valid(char **map, int height, int width) {
    int player_count = 0;
    int collectible_count = 0;
    int exit_door_count = 0;

    int i = 1;

    while (i < height - 1) {
        int j = 1;

        while (j < width - 1) {
            if (map[i][j] == 'P') {
                player_count++;
            } else if (map[i][j] == 'C') {
                collectible_count++;
            } else if (map[i][j] == 'E') {
                exit_door_count++;
            } else if (map[i][j] != '0' && map[i][j] != '1') {
                return 0; // Invalid interior element
            }
            j++;
        }
        i++;
    }

    if (player_count != 1 || collectible_count < 1 || exit_door_count != 1) {
        return 0;
    }

    return 1; 
}

int is_map_viable(char **map, int height, int width) {
    if (!are_borders_valid(map, height, width) || !are_interior_elements_valid(map, height, width)) {
        return 0; // Map is not viable
    }

    return 1; // Map is viable
}
