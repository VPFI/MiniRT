/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:03:19 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 19:35:52 by vperez-f         ###   ########.fr       */
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
#include <math.h>

#include "path_tracer/scene/objects/figures/sphere/hit/hit.h"
#include "path_tracer/scene/objects/figures/sphere/getters/getters.h"
#include "path_tracer/scene/objects/figures/sphere\
/transformations/transformations.h"

void	init_sky_sphere(t_scene *scene, char *path)
{
	t_object	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	new_obj->material = new_standard_material();
	new_obj->type = SPHERE;
	new_obj->figure.sphere.center = scene->camera.origin;
	new_obj->texture = get_texture(path, 1);
	new_obj->figure.sphere.radius = new_obj->texture->texture->width
		/ (M_PI * 2.0);
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

int	init_sphere(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = SPHERE;
	new_obj->figure.sphere.center = fig.sphere.center;
	new_obj->figure.sphere.radius = fig.sphere.radius;
	new_obj->texture = tx;
	new_obj->hit_func = hit_sphere;
	new_obj->edit_origin = translate_sphere;
	new_obj->edit_orientation = rotate_sphere;
	new_obj->get_origin = get_origin_sphere;
	new_obj->edit_dimensions = resize_sphere;
	new_obj->get_visual = get_sphere_pattern;
	new_obj->get_normal = get_sphere_normal;
	new_obj->next = NULL;
	add_object(&scene->objects, new_obj);
	return (0);
}

void	set_new_fig_sphere(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.sphere.center = *offset_origin;
	fig.sphere.radius = 0.5;
	init_sphere(scene, fig, mat, NULL);
}
