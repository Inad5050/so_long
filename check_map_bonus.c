/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:25:48 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/30 19:20:31 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	sl_check_map(t_game *game);
void	sl_check_rows(t_game *game);
void	sl_check_columns(t_game *game);
void	sl_count_map_elements(t_game *game);
void	sl_verify_map_elements(t_game *game);
void	sl_initiate_enemies(t_game *game);

void	sl_check_map(t_game *game)
{
	sl_check_rows(game);
	sl_check_columns(game);
	sl_count_map_elements(game);
	sl_verify_map_elements(game);
	sl_initiate_enemies(game);
}

void	sl_check_rows(t_game *game)
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
}

void	sl_check_columns(t_game *game)
{
	int	i;

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
			else if (game->map.all[y][x] == PLAYER)
			{
				game->map.player_number++;
				game->map.position_x = x;
				game->map.position_y = y;
			}
			else if (game->map.all[y][x] == COINS)
				game->map.coin_number++;
			else if (game->map.all[y][x] == EXIT)
				game->map.exit_number++;
			else if (game->map.all[y][x] == ENEMY)
				game->map.enemy_number++;
			x++;
		}
		y++;
	}
}

void	sl_verify_map_elements(t_game *game)
{
	if (game->map.coin_number < 1)
		sl_error("Invalid Map. There are no Coins!\n", game);
	else if (game->map.exit_number != 1)
		sl_error("Invalid Map. There is no Exit!\n", game);
	else if (game->map.player_number != 1)
		sl_error("Invalid Map. Invalid Player number!\n", game);
}
