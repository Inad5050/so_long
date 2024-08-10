/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:29:34 by dangonz3          #+#    #+#             */
/*   Updated: 2024/07/25 16:41:42 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	sl_destroy_images(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->wall_sprite.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->floor_sprite.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->coin_sprite.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_front.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_left.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_right.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_back.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->exit_open.sprite_ptr);
	mlx_destroy_image(game->mlx_ptr, game->exit_closed.sprite_ptr);
}
