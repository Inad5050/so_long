/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:12:47 by dangonz3          #+#    #+#             */
/*   Updated: 2024/07/07 21:30:58 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int		sl_error(char *message, t_game *game);
int		sl_close_game(t_game *game);
void	sl_free_all_allocated_memory(t_game *game);
void	sl_free_map(t_game *game);
void	sl_free_enemies(t_game *game);
void	sl_destroy_images(t_game *game);

int	sl_error(char *message, t_game *game)
{
	ft_printf(COLOR_RED "\nERROR\n%s\n" COLOR_RESET, message);
	sl_free_all_allocated_memory(game);
	exit (0);
}

int	sl_close_game(t_game *game)
{
	ft_printf(COLOR_GREEN "Movements: %d\n" COLOR_RESET, game->movements);
	ft_printf(COLOR_GREEN "GAME CLOSED\n" COLOR_RESET);
	sl_free_all_allocated_memory(game);
	exit (1);
}

void	sl_free_all_allocated_memory(t_game *game)
{
	if (game->map_bool == 1)
	{
		sl_free_map(game);
		sl_free_enemies(game);
	}
	if (game->images_bool == 1)
		sl_destroy_images(game);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	free(game);
}

void	sl_free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.axis_y)
		free(game->map.all[i++]);
	free(game->map.all);
	free(game->map.element);
	if (game->map.flooded)
	{
		i = 0;
		while (i < game->map.axis_y)
			free(game->map.flooded[i++]);
		free(game->map.flooded);
	}
}

void	sl_free_enemies(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.enemy)
		free(game->map.enemy);
	if (game->map.boss_a_number > 0)
	{
		free(game->map.boss_a);
		i = 0;
		while (i < game->map.boss_a_number)
			free(game->map.boss_a_route[i++]);
	}
	if (game->map.boss_b_number > 0)
	{
		free(game->map.boss_b);
		i = 0;
		while (i < game->map.boss_b_number)
			free(game->map.boss_b_route[i++]);
	}
	if (game->map.mimic)
		free(game->map.mimic);
}
