/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:03:19 by vpf               #+#    #+#             */
/*   Updated: 2025/01/23 21:57:57 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "path_tracer/scene/scene.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/hooks/management/object_management.h"
#include "path_tracer/scene/objects/material/material.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "error_management/error_management.h"
#include "path_tracer/scene/objects/figures/box/getters/getters.h"
#include "path_tracer/scene/objects/figures/box/hit/hit.h"
#include "path_tracer/scene/objects/figures/box\
/transformations/transformations.h"
#include "path_tracer/scene/objects/figures/box/utils/utils.h"

static void	set_second_half_faces(t_object *box, t_material mat,
	t_vect dims, t_vect normal)
{
	t_figure	fig;
	t_vect		anti_normal;

	anti_normal = vect_simple_mult(normal, -1);
	fig.quad.u_vect = vect_simple_mult(anti_normal, dims.z);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, -1 * dims.y);
	fig.quad.center = vect_add(box->figure.box.center,
		vect_simple_mult(box->figure.box.u_vect, -1 * dims.x * 0.5));
	add_box_face(box, fig, mat);
	fig.quad.u_vect = vect_simple_mult(anti_normal, dims.z);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.u_vect, -1 * dims.x);
	fig.quad.center = vect_add(box->figure.box.center,
		vect_simple_mult(box->figure.box.v_vect, dims.y * 0.5));
	add_box_face(box, fig, mat);
	fig.quad.u_vect = vect_simple_mult(anti_normal, dims.z);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.u_vect, dims.x);
	fig.quad.center = vect_add(box->figure.box.center,
		vect_simple_mult(box->figure.box.v_vect, -1 * dims.y * 0.5));
	add_box_face(box, fig, mat);	
}

static void	set_first_half_faces(t_object *box, t_material mat,
	t_vect dims, t_vect normal)
{
	t_figure	fig;
	t_vect		anti_normal;

	anti_normal = vect_simple_mult(normal, -1);
	fig.quad.u_vect = vect_simple_mult(box->figure.box.u_vect, dims.x);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, dims.y);
	fig.quad.center = vect_add(box->figure.box.center,
		vect_simple_mult(normal, dims.z * 0.5));
	add_box_face(box, fig, mat);
	fig.quad.u_vect = vect_simple_mult(box->figure.box.u_vect, dims.x);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, -1 * dims.y);
	fig.quad.center = vect_add(box->figure.box.center,
		vect_simple_mult(anti_normal, dims.z * 0.5));
	add_box_face(box, fig, mat);
	fig.quad.u_vect = vect_simple_mult(anti_normal, dims.z);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, dims.y);
	fig.quad.center = vect_add(box->figure.box.center,
		vect_simple_mult(box->figure.box.u_vect, dims.x * 0.5));
	add_box_face(box, fig, mat);
}

static void	init_faces(t_object *o, t_material mat, t_vect dimensions)
{
	t_vect		normal;

	normal = unit_vect(vect_cross(o->figure.box.u_vect, o->figure.box.v_vect));
	set_first_half_faces(o, mat, dimensions, normal);
	set_second_half_faces(o, mat, dimensions, normal);
}

int	init_box(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = BOX;
	new_obj->figure.box = fig.box;
	new_obj->figure.box.faces = NULL;
	new_obj->texture = tx;
	new_obj->hit_func = hit_box;
	new_obj->edit_origin = translate_box;
	new_obj->edit_orientation = rotate_box;
	new_obj->get_origin = get_origin_box;
	new_obj->edit_dimensions = resize_box;
	new_obj->get_visual = get_box_pattern;
	new_obj->get_normal = get_box_normal;
	new_obj->next = NULL;
	init_faces(new_obj, new_obj->material, new_obj->figure.box.dimensions);
	return (add_object(&scene->objects, new_obj));
}

void	set_new_fig_box(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.box.center = *offset_origin;
	fig.box.u_vect = scene->camera.u;
	fig.box.v_vect = scene->camera.v;
	fig.box.dimensions = new_vect(1.0, 1.0, 1.0);
	init_box(scene, fig, mat, NULL);
}
