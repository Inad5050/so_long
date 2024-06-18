/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:11:08 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/18 18:36:10 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_check_arguments(int argc, char **argv, t_game *game);
void	sl_initiate_map(t_game *game, char *argv);
void	sl_check_for_empty_line(char *map, t_game *game);
char	*sl_strappend(char **s1, const char *s2);

void	sl_check_arguments(int argc, char **argv, t_game *game)
{
	int	map_parameter_len;

	game->map_bool = 0;
	if (argc > 2)
		sl_error("Too many arguments! (Only 2 needed).", game);
	if (argc < 2)
		sl_error("Map file missing!", game);
	map_parameter_len = ft_strlen(argv[1]);
	if (!sl_strnstr(&argv[1][map_parameter_len - 4], ".ber", 4))
		sl_error("Wrong map file extention! (Should be .ber).", game);
}

void	sl_initiate_map(t_game *game, char *argv)
{
	char	*map_temp;
	char	*line_temp;
	int		map_fd;

	map_fd = open(argv, O_RDONLY);
	if (map_fd == -1)
		sl_error("Can`t open Map!", game);
	game->map.axis_x = 0;
	while (1)
	{
		line_temp = get_next_line(map_fd);
		if (line_temp == NULL)
			break ;
		map_temp = gnl_strjoin(map_temp, line_temp);
		free(line_temp);
		game->map.axis_x++;
	}
	close(map_fd);
	sl_check_for_empty_line(map_temp, game);
	game->map.all = ft_split(map_temp, '\n');
	game->map_bool = 1;
	free(map_temp);
}

void	sl_check_for_empty_line(char *map_temp, t_game *game)
{
	int	i;

	i = 0;
	if (map_temp[0] == '\n')
	{
		free(map_temp);
		sl_error("Invalid map. The map has an empty line at the beginning.", game);
	}
	else if (map_temp[ft_strlen(map_temp) - 1] == '\n')
	{
		free(map_temp);
		sl_error("Invalid map. The map has an empty line at the end.", game);
	}
	while (map_temp[i + 1])
	{
		if (map_temp[i] == '\n' && map_temp[i + 1] == '\n')
		{
			free(map_temp);
			sl_error("Invalid map! The map has an empty line.", game);
		}
		i++;
	}
}
