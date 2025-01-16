/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:18:06 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:15:21 by vperez-f         ###   ########.fr       */
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

static void	resize_file_selector(t_scene *scene)
{
	if (scene->map_count)
	{
		free_buttons(scene->buttons, scene->map_count);
	}
	if (scene->cumulative_image)
	{
		free(scene->cumulative_image);
	}
	scene->cumulative_image = ft_calloc((scene->height * scene->width), sizeof(t_vect));
	if (!scene->cumulative_image)
	{
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	}
	display_file_menu(scene);
}

static void	resize_rendering(t_scene *scene)
{
	set_stop_status(scene);
	wait_for_threads(scene->threads);
	scene->stop = false;
	if (scene->cumulative_image)
	{
		free(scene->cumulative_image);
	}
	recalculate_view(&scene->camera, scene->width, scene->height);
	scene->cumulative_image = ft_calloc((scene->height * scene->width), sizeof(t_vect));
	if (!scene->cumulative_image)
	{
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	}
	set_new_image(scene);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	main_loop(scene);
}

void	resize_handle(int32_t width, int32_t height, void *sc)
{
	t_scene *scene;

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

void	mouse_handle(mouse_key_t button, action_t action, modifier_key_t mods, void *sc)
{
	int32_t	x;
	int32_t	y;
	t_scene *scene;

	scene = sc;
	(void)mods;
	if (scene->edit_mode == true
		&& button == MLX_MOUSE_BUTTON_LEFT
		&& action == MLX_PRESS)
	{
		mlx_get_mouse_pos(scene->mlx, &x, &y);
		deselect_objects(scene->objects, scene->lights, &scene->object_selected);
		select_object(scene, x, y);
	}
	else if (scene->edit_mode == true
		&& button == MLX_MOUSE_BUTTON_RIGHT
		&& action == MLX_PRESS)
	{
		deselect_objects(scene->objects, scene->lights, &scene->object_selected);
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
