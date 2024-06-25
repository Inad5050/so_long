/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:32:20 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/25 16:22:35 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char	**argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_printf("ERROR: couldn't assign memory for game.\n"), 1);
    sl_check_arguments(argc, argv, game); //initiate_map
	sl_init_map(game, argv[1]); //initiate_map
	sl_init_vars(game); //initiate_game
	sl_check_map(game); //check_map
	sl_init_mlx(game); //initiate_game
	sl_init_sprites(game); //initiate_game
	sl_render_map(game); //render_map
	mlx_hook(game->win_ptr, ON_KEYDOWN, 1L<<0, sl_handle_input, (void *)&game); //handle_input
	mlx_hook(game->win_ptr, ON_DESTROY, 1L<<17, sl_close_game, (void *)&game); //close_game
	mlx_hook(game->win_ptr, ON_EXPOSE, 1L<<15, sl_render_map, (void *)&game); //render_map
	mlx_loop(game->mlx_ptr);
	sl_free_all_allocated_memory(game); //close_game
	return (0);
}
