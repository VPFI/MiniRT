/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:49:05 by vpf               #+#    #+#             */
/*   Updated: 2025/01/09 17:03:35 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
			recalculate_view(scene);
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
