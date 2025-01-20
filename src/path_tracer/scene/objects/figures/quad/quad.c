/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:03:19 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:23:16 by vperez-f         ###   ########.fr       */
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

#include "path_tracer/scene/objects/figures/quad/hit/hit.h"
#include "path_tracer/scene/objects/figures/quad/getters/getters.h"
#include "path_tracer/scene/objects/figures/quad\
/transformations/transformations.h"

int	init_quad(t_scene *scene, t_figure f, t_material mat, t_texture *tx)
{
	t_object	*n;

	n = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!n)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	n->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	n->selected = true;
	scene->object_selected = true;
	n->type = QUAD;
	n->figure.quad.center = f.quad.center;
	n->figure.quad.u_vect = f.quad.u_vect;
	n->figure.quad.v_vect = f.quad.v_vect;
	n->figure.quad.normal = unit_vect(vect_cross(f.quad.u_vect, f.quad.v_vect));
	n->texture = tx;
	n->hit_func = hit_quad;
	n->edit_origin = translate_quad;
	n->edit_orientation = rotate_quad;
	n->get_origin = get_origin_quad;
	n->edit_dimensions = resize_quad;
	n->get_visual = get_quad_pattern;
	n->get_normal = get_quad_normal;
	n->next = NULL;
	add_object(&scene->objects, n);
	return (0);
}

void	set_new_fig_quad(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.quad.center = *offset_origin;
	fig.quad.u_vect = scene->camera.u;
	fig.quad.v_vect = scene->camera.v;
	init_quad(scene, fig, mat, NULL);
}
