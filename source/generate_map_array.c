#include "../so_long.h"

void map_array(t_map *map)
{
	int fd;

	map->line = NULL;  // Initialize map->line to NULL
	map->file = NULL;
	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		error_openfile();
	while ((map->line = get_next_line(fd)))
	{
		map->file = ft_strjoinfree(map->file, map->line);
        map->x = ft_strlen(map->line);
		free(map->line);
		if (!map->file)
			ft_exit_free(map);
		map->y++;	
	}
	printf("%d\n", map->y);
	printf("%d\n", map->x); 
	close(fd);

	// Split the file content into arrays
	map->array = ft_split(map->file, '\n');
	map->copy = ft_split(map->file, '\n');
	if (!map->array || !map->copy)
		ft_exit_free(map);
	free(map->file);
	read_player_and_collectibles(map);
}