/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:11:08 by dangonz3          #+#    #+#             */
/*   Updated: 2024/07/07 21:50:24 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	sl_initiate_game(int argc, char **argv, t_game *game);
void	sl_check_arguments(int argc, char **argv, t_game *game);
void	sl_init_map(t_game *game, char *argv);
void	sl_check_for_empty_line(char *map, t_game *game);
void	sl_init_vars(t_game *game);

void	sl_initiate_game(int argc, char **argv, t_game *game)
{
	sl_check_arguments(argc, argv, game);
	sl_init_map(game, argv[1]);
	sl_init_vars(game);
}

void	sl_check_arguments(int argc, char **argv, t_game *game)
{
	int	map_parameter_len;

	game->map_bool = 0;
	game->images_bool = 0;
	if (argc > 2)
		sl_error("Too many arguments!\n", game);
	if (argc < 2)
		sl_error("Map file missing!\n", game);
	map_parameter_len = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][map_parameter_len - 4], ".ber", 4))
		sl_error("Wrong map file extention! (Should be .ber).\n", game);
}

void	sl_init_map(t_game *game, char *argv)
{
	char	*map_temp;
	char	*line_temp;
	int		map_fd;

	map_fd = open(argv, O_RDONLY);
	if (map_fd == -1)
		sl_error("Can`t open Map!\n", game);
	map_temp = ft_strdup("");
	game->map.axis_y = 0;
	while (1)
	{
		line_temp = ft_get_next_line(map_fd);
		if (line_temp == NULL)
			break ;
		map_temp = ft_strjoin(map_temp, line_temp);
		free(line_temp);
		game->map.axis_y++;
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
		sl_error("Invalid map. The map has an empty \
			line at the beginning.\n", game);
	}
	else if (map_temp[ft_strlen(map_temp) - 1] == '\n')
	{
		free(map_temp);
		sl_error("Invalid map. The map has an empty line at the end.\n", game);
	}
	while (map_temp[i + 1])
	{
		if (map_temp[i] == '\n' && map_temp[i + 1] == '\n')
		{
			free(map_temp);
			sl_error("Invalid map! The map has an empty line.\n", game);
		}
		i++;
	}
}

void	sl_init_vars(t_game *game)
{
	game->movements = 0;
	game->map.player_number = 0;
	game->map.coin_number = 0;
	game->map.exit_number = 0;
	game->map.enemy_number = 0;
	game->map.boss_a_number = 0;
	game->map.boss_b_number = 0;
	game->map.mimic_number = 0;
	game->map.axis_x = ft_strlen(game->map.all[0]);
	game->player_sprite = FRONT;
	game->map.boss_a_active = 0;
	game->game_loop = 0;
	game->map.mimic_active = 0;
}
