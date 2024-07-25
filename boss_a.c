/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:16:47 by dangonz3          #+#    #+#             */
/*   Updated: 2024/07/08 10:08:10 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	sl_memory_boss_a(t_game *game);
void	sl_boss_a(t_game *game);
void	sl_initiate_boss_a(t_game *game);
void	sl_refill_boss_a_matrix(t_game *game);
void	sl_boss_a_floodfill(t_game *game, int initial_y, int initial_x, \
int target_y, int target_x, int loop, int index);
int		sl_distance(int a_y, int a_x, int b_y, int b_x);
void	sl_boss_a_direction(t_game *game, int loop, int b);
void	sl_boss_a_direction_alternative(t_game *game, int loop, int b);
void	sl_boss_a_move(t_game *game, int y, int x, int b);

void	sl_memory_boss_a(t_game *game)
{
	int	i;

	i = 0;
	game->map.boss_a = ft_calloc(game->map.boss_a_number + game->map.mimic_number, sizeof(t_boss_a));
	if (!game->map.boss_a)
		sl_error("Couldn`t allocate memory for game->map.boss_a!\n", game);
	game->map.boss_a_route = (int **)calloc(game->map.axis_y, sizeof(int *));
	if (!game->map.boss_a_route)
		sl_error("Couldn`t alloc game->map.boss_a_route!\n", game);
	while (i < game->map.axis_y)
	{
		game->map.boss_a_route[i] = (int *)calloc(game->map.axis_x, sizeof(int));
		if (!game->map.boss_a_route[i])
			sl_error("Couldn`t alloc game->map.boss_a_route[i]!\n", game);
		i++;
	}
}

void	sl_boss_a(t_game *game)
{
	int	b;

	b = 0;
	sl_initiate_boss_a(game);
	while (b < game->map.boss_a_number)
	{
		sl_refill_boss_a_matrix(game);
		sl_boss_a_floodfill(game, game->map.boss_a[b].position_y, \
		game->map.boss_a[b].position_x, game->map.position_y, game->map.position_x, 0, 0);
		sl_boss_a_floodfill(game, game->map.position_y, game->map.position_x, \
		game->map.boss_a[b].position_y, game->map.boss_a[b].position_x, 1, 0);
		if (game->map.boss_a[b].direction % 2 == 0)
		{
			sl_boss_a_direction(game, 2, b);
			game->map.boss_a[b].direction = 0;
		}
		else
		{
			sl_boss_a_direction_alternative(game, 2, b);
			game->map.boss_a[b].direction = 1;
		}
		b++;
	}
}

void	sl_initiate_boss_a(t_game *game)
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
			if (game->map.all[y][x] == BOSSA)
			{
				game->map.boss_a[b].position_y = y;
				game->map.boss_a[b].position_x = x;
				b++;
			}
			x++;
		}
		y++;
	}
}

void	sl_refill_boss_a_matrix(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.axis_y)
	{
		x = 0;
		while (x < game->map.axis_x)
		{
			game->map.boss_a_route[y][x] = 0;			
			x++;
		}
		y++;
	}
}

void	sl_boss_a_floodfill(t_game *game, int y, int x, \
int target_y, int target_x, int loop, int index)
{
    if (y < 0 || game->map.axis_y <= y || x < 0 || game->map.axis_x <= x \
	|| game->map.boss_a_route[target_y][target_x] == loop + 1\
	|| MAX_MOVES < index || game->map.boss_a_route[y][x] == loop + 1)
        return ;
    game->map.boss_a_route[y][x] += 1;
	index++;
	if (0 >= y + 1 || y + 1 < game->map.axis_y || 0 > x || x < game->map.axis_x)
		if (game->map.all[y + 1][x] != WALL && game->map.boss_a_route[y + 1][x] == loop)
			sl_boss_a_floodfill(game, y + 1, x, target_y, target_x, loop, index);
	if (0 >= y - 1 || y - 1 < game->map.axis_y || 0 > x || x < game->map.axis_x)
		if (game->map.all[y - 1][x] != WALL && game->map.boss_a_route[y - 1][x] == loop)
    		sl_boss_a_floodfill(game, y - 1, x, target_y, target_x, loop, index);
	if (0 >= y || y < game->map.axis_y || 0 > x + 1 || x + 1 < game->map.axis_x)
		if (game->map.all[y][x + 1] != WALL && game->map.boss_a_route[y][x + 1] == loop)
   			sl_boss_a_floodfill(game, y, x + 1, target_y, target_x, loop, index);
	if (0 >= y || y < game->map.axis_y || 0 > x - 1 || x - 1 < game->map.axis_x)
		if (game->map.all[y][x - 1] != WALL && game->map.boss_a_route[y][x - 1] == loop)
    		sl_boss_a_floodfill(game, y, x - 1, target_y, target_x, loop, index);
}


void	sl_boss_a_direction(t_game *game, int loop, int b)
{
	int	y;
	int	x;
	int	t_y;
	int	t_x;
	
	y = game->map.boss_a[b].position_y;
	x = game->map.boss_a[b].position_x;
	t_y = game->map.position_y;
	t_x = game->map.position_x;
	if (game->map.boss_a_route[y][x - 1] == loop && sl_distance(y, x - 1, t_y, t_x) \
	<= sl_distance(y, x, t_y, t_x) && (game->map.all[y][x - 1] == FLOOR \
	|| game->map.all[y][x - 1] == PLAYER || game->map.all[y][x - 1] == TERRAIN))
		sl_boss_a_move(game, y, x - 1, b);
	else if (game->map.boss_a_route[y][x + 1] == loop && sl_distance(y, x + 1, t_y, t_x) \
	<= sl_distance(y, x, t_y, t_x) && (game->map.all[y][x + 1] == \
	FLOOR || game->map.all[y][x + 1] == PLAYER || game->map.all[y][x + 1] == TERRAIN))
		sl_boss_a_move(game, y, x + 1, b);
	else if (game->map.boss_a_route[y - 1][x] == loop && sl_distance(y - 1, x, t_y, t_x) \
	<= sl_distance(y, x, t_y, t_x) && (game->map.all[y - 1][x] == \
	FLOOR || game->map.all[y - 1][x] == PLAYER || game->map.all[y - 1][x] == TERRAIN))
		sl_boss_a_move(game, y - 1, x, b);
	else if (game->map.boss_a_route[y + 1][x] == loop && sl_distance(y + 1, x, t_y, t_x) \
	<= sl_distance(y, x, t_y, t_x) && (game->map.all[y + 1][x] == \
	FLOOR || game->map.all[y + 1][x] == PLAYER || game->map.all[y + 1][x] == TERRAIN))		
		sl_boss_a_move(game, y + 1, x, b);
	else
		return ;
}

void	sl_boss_a_direction_alternative(t_game *game, int loop, int b)
{
	int	y;
	int	x;
	int	t_y;
	int	t_x;
	
	y = game->map.boss_a[b].position_y;
	x = game->map.boss_a[b].position_x;
	t_y = game->map.position_y;
	t_x = game->map.position_x;

	if (game->map.boss_a_route[y][x + 1] == loop && sl_distance(y, x + 1, t_y, t_x) \
	<= sl_distance(y, x, t_y, t_x) && (game->map.all[y][x + 1] == \
	FLOOR || game->map.all[y][x + 1] == PLAYER || game->map.all[y][x + 1] == TERRAIN))
		sl_boss_a_move(game, y, x + 1, b);
	else if (game->map.boss_a_route[y - 1][x] == loop && sl_distance(y - 1, x, t_y, t_x) \
	<= sl_distance(y, x, t_y, t_x) && (game->map.all[y - 1][x] == \
	FLOOR || game->map.all[y - 1][x] == PLAYER || game->map.all[y - 1][x] == TERRAIN))
		sl_boss_a_move(game, y - 1, x, b);
	else if (game->map.boss_a_route[y + 1][x] == loop && sl_distance(y + 1, x, t_y, t_x) \
	<= sl_distance(y, x, t_y, t_x) && (game->map.all[y + 1][x] == \
	FLOOR || game->map.all[y + 1][x] == PLAYER || game->map.all[y + 1][x] == TERRAIN))	
		sl_boss_a_move(game, y + 1, x, b);
	else if (game->map.boss_a_route[y][x - 1] == loop && sl_distance(y, x - 1, t_y, t_x) \
	<= sl_distance(y, x, t_y, t_x) && (game->map.all[y][x - 1] == FLOOR \
	|| game->map.all[y][x - 1] == PLAYER || game->map.all[y][x - 1] == TERRAIN))
		sl_boss_a_move(game, y, x - 1, b);
	else
		return ;
}

void	sl_boss_a_move(t_game *game, int y, int x, int b)
{
	int	previous_y;
	int	previous_x;
	
	previous_y = game->map.boss_a[b].position_y;
	previous_x = game->map.boss_a[b].position_x;
	if (game->map.all[y][x] == PLAYER)
		sl_close_game(game);
	game->map.all[y][x] = BOSSA;
	game->map.all[previous_y][previous_x] = FLOOR;
	game->map.boss_a[b].position_y = y;
	game->map.boss_a[b].position_x = x;
	sl_render_map(game);
}
