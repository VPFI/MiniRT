/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:49:05 by vpf               #+#    #+#             */
/*   Updated: 2025/01/15 00:55:21 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/path_tracer/path_tracer.h"
#include "src/path_tracer/scene/scene.h"
#include "src/window_management/window_management.h"
#include "src/path_tracer/thread_management/mutex_utils.h"
#include "src/path_tracer/scene/camera/utils/camera_utils.h"
#include "src/path_tracer/thread_management/thread_management.h"
#include "src/window_management/key_identifiers/extra_keys.h"
#include "src/window_management/key_identifiers/settings_keys.h"
#include "src/path_tracer/scene/objects/hooks/management/object_management.h"

void	edit_mode_hooks(t_scene *scene, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_R && is_press_and_ctrl(key_data))
	{
		set_stop_status(scene);
		wait_for_threads(scene);
		scene->stop = false;
		scene->edit_mode = false;
		deselect_objects(scene->objects, scene->lights, &scene->object_selected);
		main_loop(scene);
	}
	else if (is_num_key_down(key_data) || is_copy_delete_key_down(key_data))
	{
		set_stop_status(scene);
		wait_for_threads(scene);
		scene->stop = false;
		manage_world_objects(scene, key_data);
		main_loop(scene);
	}
	else if (is_camera_key_down(key_data))
	{
		set_stop_status(scene);
		wait_for_threads(scene);
		scene->stop = false;
		if (scene->object_selected)
			transform_object(scene->objects, scene->lights, scene, key_data);
		else
		{
			move_camera(&scene->camera, &scene->back_up_camera, scene->sky_sphere, key_data);
			recalculate_view(&scene->camera, scene->width, scene->height);
		}
		main_loop(scene);
	}
	else if (is_scene_settings_key_down(key_data))
	{
		set_stop_status(scene);
		wait_for_threads(scene);
		scene->stop = false;
		change_scene_settings(scene, key_data);
		main_loop(scene);
	}
}
