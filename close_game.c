/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 20:12:47 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/20 13:27:08 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int		sl_close_game(t_game *game);
void	sl_free_all_allocated_memory(t_game *game);
void	sl_destroy_images(t_game *game);
void	sl_free_map(t_game *game);
void	sl_error(char *message, t_game *game);

int	sl_close_game(t_game *game)
{
	ft_printf(COLOR_GREEN "Movements: %d\n" COLOR_RESET, game->movements);
	sl_free_all_allocated_memory(game);
	ft_printf(COLOR_GREEN "GAME CLOSED\n" COLOR_RESET);
	exit (1);
}

void	sl_free_all_allocated_memory(t_game *game)
{
	sl_destroy_images(game);
	sl_free_map(game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free(game);
}

void	sl_destroy_images(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->wall.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->floor.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->coins.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_front.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_left.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_right.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_back.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->exit_open.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->exit_closed.sprite_ptr);
}

void	sl_free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.axis_y)
		free(game->map.all[i++]);
	free(game->map.all);
}

void	sl_error(char *message, t_game *game)
{
	if (game->map_bool == 1)
		sl_free_map(game);
	free(game);
	ft_printf(COLOR_RED "%s\n" COLOR_RESET, message);
	exit (1);
}
