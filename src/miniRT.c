/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:26 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 22:18:23 by vperez-f         ###   ########.fr       */
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

static void	init_minirt(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
	scene->width = WINW;
	scene->height = WINH;
	scene->amb_color = AMB_COLOR;
	scene->amb_light = -1;
	scene->aspect_ratio = scene->width / (float)scene->height;
	scene->choose_file = 0;
	scene->current_file = 0;
	scene->mlx = mlx_init(scene->width, scene->height, "miniRT", true);
	scene->image = mlx_new_image(scene->mlx, scene->width, scene->height);
	if (!scene->image)
		return (exit_err(ERR_MEM_MSG, "while loading mlx image", 2));
	scene->cumulative_image = ft_calloc((scene->height * scene->width), sizeof(t_vect));
	if (!scene->cumulative_image)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	scene->state = (uint32_t)(scene->height * scene->width * mlx_get_time());
	ft_memset(scene->threads_backup, 0, sizeof(t_thread_backup) * THREADS);
	pthread_mutex_init(&scene->stop_mutex, NULL);
	scene->stop = false;
	scene->edit_mode = false;
	scene->do_backup = false;
	scene->object_selected = false;
	scene->path = NULL;
	scene->menu_tx = get_texture("./assets/textures/menu/Sad_face1.png", 1);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
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
	wait_for_threads(scene.threads);
	clean_memory(&scene);
	return (0);
}
