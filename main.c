/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:32:20 by dangonz3          #+#    #+#             */
/*   Updated: 2024/08/05 19:03:08 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char	**argv)
{
	t_game	*game;

	game = ft_calloc(sizeof(t_game), 1);
	if (!game)
		return (ft_printf("\nERROR\nCouldn't assign memory for game.\n"), 1);
	sl_initiate_game(argc, argv, game);
	sl_check_map(game);
	sl_flood_map(game);
	sl_init_mlx(game);
	sl_init_sprites(game);
	sl_render_map(game);
	ft_printf("1game->map_bool = %i\n", game->map_bool);
	mlx_hook(game->win_ptr, ON_KEYDOWN, 1L << 0, sl_handle_input, game);
	/* mlx_hook(game->win_ptr, ON_DESTROY, 1L << 17, sl_close_game, game); */
	ft_printf("2game->map_bool = %i\n", game->map_bool);
	mlx_loop(game->mlx_ptr);
	ft_printf("3game->map_bool = %i\n", game->map_bool);
	return (0);
}
