/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:18:06 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 15:26:05 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "mlx/mlx_utils.h"
#include "selection_menu/file_selector.h"
#include "path_tracer/path_tracer.h"
#include "path_tracer/scene/scene.h"
#include "path_tracer/scene/objects/hooks/management/object_management.h"
#include "path_tracer/scene/camera/camera.h"
#include "path_tracer/modes/edit_mode/edit_mode.h"
#include "path_tracer/modes/render_mode/render_mode.h"
#include "path_tracer/thread_management/thread_management.h"
#include "window_management/key_identifiers/key_identifiers.h"
#include "error_management/error_management.h"

static void	resize_file_selector(t_scene *sc)
{
	if (sc->map_count)
	{
		free_buttons(sc->buttons, sc->map_count);
	}
	if (sc->cumulative_image)
	{
		free(sc->cumulative_image);
	}
	sc->cumulative_image = ft_calloc((sc->height * sc->width), sizeof(t_vect));
	if (!sc->cumulative_image)
	{
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	}
	display_file_menu(sc);
}

static void	resize_rendering(t_scene *sc)
{
	stop_and_wait_threads(sc);
	if (sc->cumulative_image)
	{
		free(sc->cumulative_image);
	}
	recalculate_view(&sc->camera, sc->width, sc->height);
	sc->cumulative_image = ft_calloc((sc->height * sc->width), sizeof(t_vect));
	if (!sc->cumulative_image)
	{
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	}
	set_new_image(sc);
	mlx_image_to_window(sc->mlx, sc->image, 0, 0);
	main_loop(sc);
}

void	resize_handle(int32_t width, int32_t height, void *sc)
{
	t_scene	*scene;

	scene = sc;
	scene->height = height;
	scene->width = width;
	if (!scene->choose_file)
	{
		resize_file_selector(scene);
	}
	else
	{
		resize_rendering(scene);
	}
}

void	mouse_handle(mouse_key_t button, action_t action,
			modifier_key_t mods, void *sc)
{
	int32_t	x;
	int32_t	y;
	t_scene	*scen;

	scen = sc;
	(void)mods;
	if (scen->edit_mode == true
		&& button == MLX_MOUSE_BUTTON_LEFT
		&& action == MLX_PRESS)
	{
		stop_and_wait_threads(scen);
		mlx_get_mouse_pos(scen->mlx, &x, &y);
		deselect_objects(scen->objects, scen->lights, &scen->object_selected);
		select_object(scen, x, y);
		main_loop(scen);
	}
	else if (scen->edit_mode == true
		&& button == MLX_MOUSE_BUTTON_RIGHT
		&& action == MLX_PRESS)
	{
		stop_and_wait_threads(scen);
		deselect_objects(scen->objects, scen->lights, &scen->object_selected);
		main_loop(scen);
	}
}

void	key_down(mlx_key_data_t key_data, void *sc)
{
	t_scene	*scene;

	scene = sc;
	if (key_data.key == MLX_KEY_ESCAPE && key_data.action == MLX_PRESS)
	{
		close_mlx(scene);
	}
	else if (!scene->choose_file && scene->map_count
		&& is_movement_key_down(key_data))
	{
		move_menu(scene, key_data.key);
	}
	else if (!scene->choose_file
		&& (key_data.key == MLX_KEY_ENTER && key_data.action == MLX_PRESS))
	{
		select_scene(scene);
	}
	else if (scene->edit_mode == false && scene->choose_file)
		render_mode_hooks(scene, key_data);
	else if (scene->edit_mode == true)
		edit_mode_hooks(scene, key_data);
}
