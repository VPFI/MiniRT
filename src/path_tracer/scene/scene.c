/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:28:07 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 00:54:58 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/path_tracer/scene/scene.h"

void	change_scene_settings(t_scene *scene, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_COMMA)
	{
		scene->amb_light -= 0.05;
		if (scene->amb_light < 0.0)
			scene->amb_light = 0.0;
		printf("Ambient light intensity: %f\n", scene->amb_light);
	}
	else if (key_data.key == MLX_KEY_PERIOD)
	{
		scene->amb_light += 0.05;
		printf("Ambient light intensity: %f\n", scene->amb_light);
	}
	else if (key_data.key == MLX_KEY_RIGHT_SHIFT)
		deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	return ;
}

void	init_sky_sphere(t_scene *scene, char *path)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	new_obj->material = new_standard_material();
	new_obj->type = SPHERE;
	new_obj->figure.sphere.center = scene->camera.origin;
	new_obj->texture = get_texture(path, 1);
	new_obj->figure.sphere.radius = new_obj->texture->texture->width / (M_PI * 2.0);
	new_obj->hit_func = hit_sphere;
	new_obj->edit_origin = translate_sphere;
	new_obj->edit_orientation = rotate_sphere;
	new_obj->get_origin = get_origin_sphere;
	new_obj->edit_dimensions = resize_sphere;
	new_obj->get_visual = get_sphere_pattern;
	new_obj->get_normal = get_sphere_normal;
	new_obj->next = NULL;
	add_object(&scene->sky_sphere, new_obj);
}

static void	load_map_scene(t_scene *scene)
{
	int		map;
	char	*line;
	char	**components;

	map = open(scene->path, O_RDONLY);
	if (map < 0)	
		return (exit_err(ERR_NOFILE_MSG, scene->path, 2));
	line = get_next_line(map);
	while (line)	
	{
		components = format_line(line);
		if (components && components[0])
		{
			if (parse_components(scene, components))
			{
				free(line);
				free_arr(components);
				return (exit_err(ERR_EMPTY_MSG, "while loading map", 2));
			}
		}
		free(line);
		free_arr(components);
		line = get_next_line(map);		
	}
}

static void	load_standard_scene(t_scene *scene)
{
	scene->amb_light = AMB_LIGHT;
	scene->amb_color = AMB_COLOR;
	scene->max_depth = MAX_DEPTH;
	scene->samples = SPP;
	init_camera(&scene->camera, scene->width, scene->height);
	scene->back_up_camera = scene->camera;
	init_sky_sphere(scene, STD_SKYSPHERE);
}

void	init_scene(t_scene *scene)
{
	if (scene->path && (!ft_strcmp(".std", scene->path) || !ft_strcmp(".standard", scene->path)))
	{
		load_standard_scene(scene);
	}
	else if (scene->path && scene->choose_file)
	{
		load_map_scene(scene);
		recalculate_view(&scene->camera, scene->width, scene->height);
		scene->back_up_camera = scene->camera;
	}
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
}
