/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_two_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:22:51 by dangonz3          #+#    #+#             */
/*   Updated: 2024/07/25 19:42:15 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	sl_verify_map_elements(t_game *game)
{
	if (game->map.coin_number < 1)
		sl_error("Invalid Map. There are no Coins!\n", game);
	else if (game->map.exit_number != 1)
		sl_error("Invalid Map. Invalid Exit number!\n", game);
	else if (game->map.player_number != 1)
		sl_error("Invalid Map. Invalid Player number!\n", game);
}
