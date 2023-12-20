/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:07:24 by ada-mata          #+#    #+#             */
/*   Updated: 2023/12/08 14:07:28 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

static int	check_extension(const char *filename)
{
	return (ft_strstr(filename, ".ber") != NULL);
}

static void	read_file_lines(t_map *map, int fd)
{
	while (map->line)
	{
		map->file = ft_strjoinfree(map->file, map->line);
		map->x = ft_strlen(map->line);
		free(map->line);
		map->line = get_next_line(fd);
		if (!map->file)
			ft_exit_free(map);
		map->y++;
	}
}

void	map_array(t_map *map)
{
	int	fd;

	map->line = NULL;
	map->file = NULL;
	if (!check_extension(map->filename))
		error_filename();
	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		error_openfile();
	map->line = get_next_line(fd);
	read_file_lines(map, fd);
	close(fd);
	map->array = ft_split(map->file, '\n');
	if (!map->array)
		ft_exit_free(map);
	free(map->file);
	read_player_and_collectibles(map);
}
