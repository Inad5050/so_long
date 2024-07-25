/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:32:20 by dangonz3          #+#    #+#             */
/*   Updated: 2024/07/07 21:51:50 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char	**argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_printf("\nERROR\nCouldn't assign memory for game.\n"), 1);
	sl_initiate_game(argc, argv, game);
	sl_check_map(game);
	sl_flood_map(game);
	sl_init_mlx(game);
	sl_init_sprites(game);
	if (game->map.enemy_number > 0)
		sl_initiate_enemies(game);
	if (game->map.boss_a_number > 0 || game->map.mimic_number > 0)
		sl_memory_boss_a(game);
	if (game->map.boss_b_number > 0)
		sl_memory_boss_b(game);
	if (game->map.mimic_number > 0)
		sl_memory_mimic(game);
	sl_render_map(game);
	mlx_hook(game->win_ptr, ON_KEYDOWN, 1L << 0, sl_handle_input, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
