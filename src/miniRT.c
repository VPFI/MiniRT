/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:26 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/23 20:44:12 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "mlx/MLX42/include/MLX42/MLX42.h"
#include "mlx/mlx_utils.h"
#include "parser/map_file/parse_map_path.h"
#include "path_tracer/path_tracer.h"
#include "path_tracer/thread_management/thread_management.h"
#include "path_tracer/memory_management/memory_management.h"
#include "window_management/window_management.h"
#include "error_management/error_management.h"
#include "selection_menu/file_selector.h"
#include <stdint.h>
#include <stdio.h>

static void	init_minirt(t_scene *sc)
{
	ft_bzero(sc, sizeof(t_scene));
	sc->width = WINW;
	sc->height = WINH;
	sc->amb_color = AMB_COLOR;
	sc->amb_light = -1;
	sc->aspect_ratio = sc->width / (float)sc->height;
	sc->choose_file = 0;
	sc->current_file = 0;
	sc->mlx = mlx_init(sc->width, sc->height, "miniRT", true);
	sc->image = mlx_new_image(sc->mlx, sc->width, sc->height);
	if (!sc->image)
		return (exit_err(ERR_MEM_MSG, "while loading mlx image", 2));
	sc->cumulative_image = ft_calloc((sc->height * sc->width), sizeof(t_vect));
	if (!sc->cumulative_image)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	sc->state = (uint32_t)(sc->height * sc->width * mlx_get_time());
	ft_memset(sc->threads_backup, 0, sizeof(t_thread_backup) * THREADS);
	pthread_mutex_init(&sc->stop_mutex, NULL);
	sc->stop = false;
	sc->edit_mode = false;
	sc->do_backup = false;
	sc->object_selected = false;
	sc->path = NULL;
	sc->menu_tx = get_texture("./assets/textures/menu/Sad_face1.png", 1);
	mlx_image_to_window(sc->mlx, sc->image, 0, 0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	init_minirt(&scene);
	if (parse_map_path(&scene, argc, argv))
		display_file_menu(&scene);
	init_scene(&scene);
	main_loop(&scene);
	mlx_close_hook(scene.mlx, close_mlx, &scene);
	mlx_key_hook(scene.mlx, key_down, &scene);
	mlx_mouse_hook(scene.mlx, mouse_handle, &scene);
	mlx_resize_hook(scene.mlx, resize_handle, &scene);
	mlx_loop(scene.mlx);
	printf("END: %f\n", mlx_get_time() - scene.time);
	if (scene.choose_file)
		wait_for_threads(scene.threads);
	clean_memory(&scene);
	return (0);
}
