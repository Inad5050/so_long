/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 12:26:16 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/30 19:49:03 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	sl_initiate_enemies(t_game *game);
void	sl_select_enemy(t_game *game);
void	sl_enemy_direction(t_game *game, int i);
void	sl_enemy_move(t_game *game, int current_y, int current_x, int i);

void	sl_initiate_enemies(t_game *game)
{
	int	y;
	int	x;
	int	i;

	i = 0;
	y = 0;
	ft_printf("enemy_number: %i\n", game->map.enemy_number);
	game->enemy = ft_calloc(game->map.enemy_number, sizeof(t_enemy));
	if (!game->enemy)
		sl_error("ERROR: couldn't allocate memory for enemies.\n", game);
	while (y < game->map.axis_y && i < game->map.enemy_number)
	{
		x = 0;
		while (x < game->map.axis_x)
		{
			x++;
			if (game->map.all[y][x] == ENEMY)
			{
				game->enemy[i].position_y = y;
				game->enemy[i].position_x = x;
				ft_printf("enemy_initial_position: %i %i\n", game->enemy[i].position_y, game->enemy[i].position_x);
				game->enemy[i].direction = 0;
				ft_printf("enemy_initial_direction: %i\n", game->enemy[i].direction);
				i++;
			}
		}
		y++;
	}
}

void	sl_select_enemy(t_game *game)
{
	int	i;

	i = 0;	
	while(i < game->map.enemy_number)
	{
		sl_enemy_direction(game, i);
		i++;
	}
}

void	sl_enemy_direction(t_game *game, int i)
{
	int	current_y;
	int	current_x;
	
	current_y = game->enemy[i].position_y;
	current_x = game->enemy[i].position_x;
	if (game->enemy[i].direction == 0)
		current_x = current_x + 1;
	else if (game->enemy[i].direction == 1)
		current_y = current_y + 1;
	else if  (game->enemy[i].direction == 2)
		current_x = current_x - 1;
	else if  (game->enemy[i].direction == 3)
		current_y = current_y - 1;
	sl_enemy_move(game, current_y, current_x, i);
}

void	sl_enemy_move(t_game *game, int current_y, int current_x, int i)
{
	int	previous_y;
	int	previous_x;
	
	previous_y = game->enemy[i].position_y;
	previous_x = game->enemy[i].position_x;
	if (game->map.all[current_y][current_x] == PLAYER)
		sl_close_game(game);
	else if (game->map.all[current_y][current_x] == WALL \
	|| game->map.all[current_y][current_x] == COINS \
	|| game->map.all[current_y][current_x] == EXIT
	|| game->map.all[current_y][current_x] == ENEMY)
		game->enemy[i].direction = (game->enemy[i].direction + 1) % 4;
	else if (game->map.all[current_y][current_x] == FLOOR)
	{
		game->map.all[current_y][current_x] = ENEMY;
		game->map.all[previous_y][previous_x] = FLOOR;
		game->enemy[i].position_y = current_y;
		game->enemy[i].position_x = current_x;
		sl_render_map(game);
	}
}
