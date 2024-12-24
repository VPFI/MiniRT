/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:28:07 by vperez-f          #+#    #+#             */
/*   Updated: 2024/12/24 16:29:03 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	load_map_scene(t_scene *scene)
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

void	load_standard_scene(t_scene *scene)
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
		recalculate_view(scene);
		scene->back_up_camera = scene->camera;
	}
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
}
