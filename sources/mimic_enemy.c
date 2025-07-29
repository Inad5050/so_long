/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mimic_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 09:27:04 by dangonz3          #+#    #+#             */
/*   Updated: 2024/07/07 19:06:55 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <unistd.h>

void	sl_memory_mimic(t_game *game);
void	sl_initiate_mimic(t_game *game);
void	sl_activate_mimics(t_game *game);
int		sl_distance(int y, int x, int t_y, int t_x);
void	sl_handle_mimics(t_game *game, int b);

void	sl_memory_mimic(t_game *game)
{
	game->map.mimic = ft_calloc(game->map.mimic_number, sizeof(t_mimic));
	if (!game->map.mimic)
		sl_error("Couldn`t allocate memory for game->map.mimic!\n", game);
	sl_initiate_mimic(game);
}

void	sl_initiate_mimic(t_game *game)
{
	int	y;
	int	x;
	int b;
	
	b = 0;
	y = 0;
	while (y < game->map.axis_y)
	{
		x = 0;
		while (x < game->map.axis_x)
		{
			if (game->map.all[y][x] == MIMIC)
			{
				game->map.mimic[b].position_y = y;
				game->map.mimic[b].position_x = x;
				b++;
			}
			x++;
		}
		y++;
	}
}

void	sl_activate_mimics(t_game *game)
{
	int	b;
	int y;
	int x;
	
	b = 0;
	while (b < game->map.mimic_number)
	{
		y = game->map.mimic[b].position_y;
		x = game->map.mimic[b].position_x;
		if (sl_distance(y, x, game->map.position_y, game->map.position_x) == 1 \
		&& game->map.all[y][x] == MIMIC)
			sl_handle_mimics(game, b);
		b++;
	}
}

void	sl_handle_mimics(t_game *game, int b)
{
	int y;
	int x;
	
	y = game->map.mimic[b].position_y;
	x = game->map.mimic[b].position_x;
	if (game->map.mimic_active % 2 == 0)
	{
		game->map.all[y][x] = BOSSA;
		game->map.boss_a_number++;
		game->map.boss_a[game->map.boss_a_number + 1].position_y = y;
		game->map.boss_a[game->map.boss_a_number + 1].position_x = x;
		game->map.coin_number--;
	}
	else if(game->map.mimic_active % 2 != 0)
		game->map.all[y][x] = COIN;
	game->map.mimic_active = rand();
}
