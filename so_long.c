/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:32:20 by dangonz3          #+#    #+#             */
/*   Updated: 2024/06/18 18:29:04 by dangonz3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char	**argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	sl_check_arguments(argc, argv, game); //initiate_map
	sl_init_map(game, argv[1]); //initiate_map
	sl_init_vars(game); //initiate_game
	sl_check_map(game); //check_map
	sl_init_mlx(game); //initiate_game
	sl_init_sprites(game); //initiate_game
	sl_render_map(game); //render_map
	mlx_hook(game->win_ptr, ON_KEYDOWN, 1L<<0, sl_handle_input, game); //handle_input
	mlx_hook(game->win_ptr, ON_DESTROY, 1L<<17, sl_close_game, game); //close_game
	mlx_hook(game->win_ptr, ON_EXPOSE, 1L<<15, sl_render_map, game); //render_map
	mlx_loop(game->mlx_ptr);
	sl_free_all_allocated_memory(game);
}

// An Expose event (12) occurs when part or all of a window needs to be redrawn.
// The ExposureMask ((1L<<15)) is used to specify that an application wants to receive Expose events.

//HOOKS

//void mlx_hook(list_t *win_ptr, int x_event, int x_mask, int (*f)(), void *param)

/* 
Hooking         event	code	Prototype
ON_KEYDOWN	    2	int (*f)(int keycode, void *param)
ON_KEYUP*	    3	int (*f)(int keycode, void *param)
ON_MOUSEDOWN*	4	int (*f)(int button, int x, int y, void *param)
ON_MOUSEUP	    5	int (*f)(int button, int x, int y, void *param)
ON_MOUSEMOVE	6	int (*f)(int x, int y, void *param)
ON_EXPOSE*	    12	int (*f)(void *param)
ON_DESTROY	    17	int (*f)(void *param)
*/

/* 
Mask	    Description	 		
0L	        NoEventMask	 	    
(1L<<0)	    KeyPressMask	 	
(1L<<1)	    KeyReleaseMask	 	
(1L<<2)	    ButtonPressMask	 	
(1L<<3)	    ButtonReleaseMask
(1L<<15)	ExposureMask
(1L<<17)	StructureNotifyMask
*/

/* 
mlx_key_hook function is an alias of mlx_hook on key up event (3). mlx_key_hook(game.mlx_win, (*f)(), &game);
mlx_mouse_hook function is an alias of mlx_hook on mouse down event (4).
*/

//IMAGES

//void *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);
//int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);

//LOOPS
//mlx_loop(game.mlx); ejecuta loops designados con mlx_loop_hook(mlx, render_next_frame, YourStruct);
