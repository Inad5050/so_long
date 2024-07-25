/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:55:01 by dangonz3          #+#    #+#             */
/*   Updated: 2024/07/25 20:41:13 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	sl_flood_map(t_game *game);
void	sl_initiate_flood(t_game *game);
void	sl_element_finder(t_game *game);
void	sl_floodfill(t_game *game, int x, int y, int index);
void	sl_check_flood(t_game *game);

void	sl_flood_map(t_game *game)
{
	sl_initiate_flood(game);
	sl_element_finder(game);
	sl_floodfill(game, game->map.position_y, game->map.position_x, 0);
	sl_check_flood(game);
}

void	sl_initiate_flood(t_game *game)
{
	int	i;

	i = 0;
	game->map.element = ft_calloc(game->map.element_number, sizeof(t_element));
	if (!game->map.element)
		sl_error("Couldn`t allocate memory for game->map.element!\n", game);
	game->map.flooded = (int **)ft_calloc(game->map.axis_y, sizeof(int *));
	if (!game->map.flooded)
		sl_error("Couldn`t alloc game->map.filled_bool!\n", game);
	while (i < game->map.axis_y)
	{
		game->map.flooded[i] = (int *)ft_calloc(game->map.axis_x, sizeof(int));
		if (!game->map.flooded[i])
			sl_error("Couldn`t alloc game->map.filled_bool[i]!\n", game);
		i++;
	}
}

void	sl_element_finder(t_game *game)
{
	int	y;
	int	x;
	int	i;

	y = 0;
	i = 0;
	while (y < game->map.axis_y)
	{
		x = 0;
		while (x < game->map.axis_x)
		{
			game->map.flooded[y][x] = 0;
			if ((game->map.all[y][x] == PLAYER || game->map.all[y][x] == EXIT \
			|| game->map.all[y][x] == COIN) && (i < game->map.element_number))
			{
				game->map.element[i].position_y = y;
				game->map.element[i].position_x = x;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	sl_floodfill(t_game *game, int y, int x, int index)
{
	if (y < 0 || y >= game->map.axis_y || x < 0 || x >= game->map.axis_x \
	|| game->map.flooded[y][x] == 1)
		return ;
	game->map.flooded[y][x] += 1;
	index++;
	if (0 >= y + 1 || y + 1 < game->map.axis_y || 0 > x || x < game->map.axis_x)
		if (game->map.all[y + 1][x] != WALL)
			sl_floodfill(game, y + 1, x, index);
	if (0 >= y - 1 || y - 1 < game->map.axis_y || 0 > x || x < game->map.axis_x)
		if (game->map.all[y - 1][x] != WALL)
			sl_floodfill(game, y - 1, x, index);
	if (0 >= y || y < game->map.axis_y || 0 > x + 1 || x + 1 < game->map.axis_x)
		if (game->map.all[y][x + 1] != WALL)
			sl_floodfill(game, y, x + 1, index);
	if (0 >= y || y < game->map.axis_y || 0 > x - 1 || x - 1 < game->map.axis_x)
		if (game->map.all[y][x - 1] != WALL)
			sl_floodfill(game, y, x - 1, index);
}

void	sl_check_flood(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.element_number)
	{
		if (game->map.flooded[game->map.element[i].position_y] \
		[game->map.element[i].position_x] == 0)
			sl_error("Invalid Map. Can`t reach all elements!\n", game);
		i++;
	}
}
