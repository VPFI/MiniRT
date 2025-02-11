/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:03:19 by vpf               #+#    #+#             */
/*   Updated: 2025/01/22 13:30:12 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "path_tracer/scene/scene.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "path_tracer/scene/objects/figures/figures.h"
#include "path_tracer/scene/objects/material/material.h"
#include "path_tracer/scene/objects/texture/texture_objects.h"
#include "path_tracer/scene/objects/hooks/management/object_management.h"
#include "error_management/error_management.h"

#include "path_tracer/scene/objects/figures/cone/getters/getters.h"
#include "path_tracer/scene/objects/figures/cone/hit/hit.h"
#include "path_tracer/scene/objects/figures/cone\
/transformations/transformations.h"
#include "path_tracer/scene/objects/figures/cone/utils/utils.h"

int	init_cone(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = CONE;
	new_obj->figure.cone.normal = unit_vect(fig.cone.normal);
	new_obj->figure.cone.radius = fig.cone.radius;
	new_obj->figure.cone.height = fig.cone.height;
	new_obj->figure.cone.center = vect_add(fig.cone.center,
			vect_simple_mult(fig.cone.normal, -fig.cone.height / 2));
	new_obj->texture = tx;
	new_obj->hit_func = hit_cone;
	new_obj->edit_origin = translate_cone;
	new_obj->edit_orientation = rotate_cone;
	new_obj->get_origin = get_origin_cone;
	new_obj->edit_dimensions = resize_cone;
	new_obj->get_visual = get_cone_pattern;
	new_obj->get_normal = get_cone_normal;
	new_obj->next = NULL;
	return (add_object(&scene->objects, new_obj));
}

void	set_new_fig_cone(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.cone.center = *offset_origin;
	fig.cone.normal = scene->camera.v;
	fig.cone.radius = 0.5;
	fig.cone.height = 2.0;
	init_cone(scene, fig, mat, NULL);
}
