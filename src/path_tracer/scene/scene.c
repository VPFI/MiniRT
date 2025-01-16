/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:28:07 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 22:19:02 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "mlx/MLX42/include/MLX42/MLX42.h"

#include "parser/parser.h"
#include "parser/utils/lexical_utils.h"
#include "path_tracer/scene/scene.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "selection_menu/buttons/buttons.h"
#include "path_tracer/scene/camera/camera.h"
#include "error_management/error_management.h"
#include "path_tracer/scene/objects/figures/sphere/sphere.h"
#include "path_tracer/scene/objects/hooks/management/object_management.h"
#include "path_tracer/thread_management/thread_management.h"
#include <stdbool.h>
#include <stdint.h>

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
				ft_free_arr(components);
				return (exit_err(ERR_EMPTY_MSG, "while loading map", 2));
			}
		}
		free(line);
		ft_free_arr(components);
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
