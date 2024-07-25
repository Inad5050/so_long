/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:25:48 by dangonz3          #+#    #+#             */
/*   Updated: 2024/07/25 19:42:12 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	sl_check_map(t_game *game);
void	sl_check_limits(t_game *game);
void	sl_check_rectangular(t_game *game);
void	sl_count_map_elements(t_game *game);
void	sl_sum_map_elements(t_game *game, int y, int x);
void	sl_verify_map_elements(t_game *game);

void	sl_check_map(t_game *game)
{
	sl_check_limits(game);
	sl_check_rectangular(game);
	sl_count_map_elements(game);
	sl_verify_map_elements(game);
}

void	sl_check_limits(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.axis_x)
	{
		if (game->map.all[0][i] != WALL)
			sl_error("Invalid Map. Missing wall on the first row!\n", game);
		else if (game->map.all[game->map.axis_y - 1][i] != WALL)
			sl_error("Invalid Map. Missing wall on the last row!\n", game);
		i++;
	}
	if (i < 3)
		sl_error("Invalid Map. Map too small!\n", game);
	i = 0;
	while (i < game->map.axis_y)
	{
		if (game->map.all[i][0] != WALL)
			sl_error("Invalid Map. Missing wall on the first column!\n", game);
		else if (game->map.all[i][game->map.axis_x - 1] != WALL)
			sl_error("Invalid Map. Missing wall on the last column!\n", game);
		i++;
	}
	if (i < 3)
		sl_error("Invalid Map. Map too small!\n", game);
}

void	sl_check_rectangular(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.axis_y)
	{
		if ((int)ft_strlen(game->map.all[i]) != game->map.axis_x)
			sl_error("Invalid Map. Not a rectangle!\n", game);
		i++;
	}
}

void	sl_count_map_elements(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.axis_y)
	{
		x = 0;
		while (x < game->map.axis_x)
		{
			if (!ft_strchr("10CPEF", game->map.all[y][x]))
				sl_error("Invalid Map. Unexpected map parameter!\n", game);
			sl_sum_map_elements(game, y, x);
			x++;
		}
		y++;
	}
	game->map.element_number = game->map.player_number + \
	game->map.coin_number + game->map.exit_number;
}

void	sl_sum_map_elements(t_game *game, int y, int x)
{
	if (game->map.all[y][x] == PLAYER)
	{
		game->map.player_number++;
		game->map.position_x = x;
		game->map.position_y = y;
	}
	else if (game->map.all[y][x] == COIN)
		game->map.coin_number++;
	else if (game->map.all[y][x] == EXIT)
		game->map.exit_number++;
	else if (game->map.all[y][x] == ENEMY)
		game->map.enemy_number++;
}
