/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:28:07 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/17 20:57:04 by vperez-f         ###   ########.fr       */
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

static int	load_map_scene(t_scene *scene, int *relevant_content)
{
	int		map;
	char	*line;
	char	**components;
	int		ln;

	ln = 0;
	map = open(scene->path, O_RDONLY);
	if (map < 0)	
		return (exit_err(ERR_NOFILE_MSG, scene->path, 2), 0);
	line = get_next_line(map);
	while (line)	
	{
		ln++;
		components = format_line(line);
		if (components && components[0])
		{
			*relevant_content = 1;
			printf("Line: %i\n", ln);
			if (parse_components(scene, components))
				return (free(line), ft_free_arr(components),
					exit_err(ERR_EMPTY_MSG, "while loading map", 2), 0);
		}
		free(line);
		ft_free_arr(components);
		line = get_next_line(map);		
	}
	if (!(*relevant_content))
		return (0);
	return (1);
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

void	init_scene(t_scene *sc)
{
	int	relevant_content;

	relevant_content = 0;
	if (sc->path && (!ft_strcmp(".std", sc->path)
		|| !ft_strcmp(".standard", sc->path)))
	{
		load_standard_scene(sc);
	}
	else if (sc->path && sc->choose_file)
	{
		if (!load_map_scene(sc, &relevant_content))
		{
			printf("Possible empty map, opening standard scene...\n");
			load_standard_scene(sc);
			deselect_objects(sc->objects, sc->lights, &sc->object_selected);
			return ;
		}
		recalculate_view(&sc->camera, sc->width, sc->height);
		sc->back_up_camera = sc->camera;
	}
	deselect_objects(sc->objects, sc->lights, &sc->object_selected);
}
