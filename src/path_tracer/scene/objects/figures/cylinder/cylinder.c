/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:03:19 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:32:34 by vperez-f         ###   ########.fr       */
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

#include "path_tracer/scene/objects/figures/cylinder/hit/hit.h"
#include "path_tracer/scene/objects/figures/cylinder/utils/utils.h"
#include "path_tracer/scene/objects/figures/cylinder/getters/getters.h"
#include "path_tracer/scene/objects/figures/cylinder\
/transformations/transformations.h"

int	init_cylinder(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = CYLINDER;
	new_obj->figure.cylinder.center = fig.cylinder.center;
	new_obj->figure.cylinder.normal = unit_vect(fig.cylinder.normal);
	new_obj->figure.cylinder.radius = fig.cylinder.radius;
	new_obj->figure.cylinder.height = fig.cylinder.height;
	new_obj->texture = tx;
	new_obj->hit_func = hit_cylinder;
	new_obj->edit_origin = translate_cylinder;
	new_obj->edit_orientation = rotate_cylinder;
	new_obj->get_origin = get_origin_cylinder;
	new_obj->edit_dimensions = resize_cylinder;
	new_obj->get_visual = get_cylinder_pattern;
	new_obj->get_normal = get_cylinder_normal;
	new_obj->next = NULL;
	add_object(&scene->objects, new_obj);
	return (0);
}

void	set_new_fig_cylinder(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.cylinder.center = *offset_origin;
	fig.cylinder.normal = scene->camera.v;
	fig.cylinder.radius = 0.5;
	fig.cylinder.height = 2.0;
	init_cylinder(scene, fig, mat, NULL);
}
