/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:46:35 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 00:11:07 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/libft/libft.h"
#include "src/path_tracer/scene/scene.h"
#include "src/path_tracer/scene/objects/objects.h"
#include "src/path_tracer/scene/objects/material/material.h"
#include "src/path_tracer/scene/objects/hooks/management/object_management.h"
#include "src/error_management/error_management.h"

static void	init_copy(t_scene *scene, t_object *selected_obj)
{
	t_figure	fig;
	t_texture	*tx;
	t_material	mat;

	tx = NULL;
	if (selected_obj->texture)
		tx = get_texture(selected_obj->texture->path, selected_obj->texture->texture_dim);
	fig = selected_obj->figure;
	mat = selected_obj->material;
	if (selected_obj->type == SPHERE)
		init_sphere(scene, fig, mat, tx);
	else if (selected_obj->type == PLANE)
		init_plane(scene, fig, mat, tx);
	else if (selected_obj->type == QUAD)
		init_quad(scene, fig, mat, tx);
	else if (selected_obj->type == BOX)
		init_box(scene, fig, mat, tx);
	else if (selected_obj->type == DISK)
		init_disk(scene, fig, mat, tx);
	else if (selected_obj->type == CYLINDER)
		init_cylinder(scene, fig, mat, tx);
	else if (selected_obj->type == CONE)
		init_cone(scene, fig, mat, tx);
	else if (selected_obj->type == LIGHT)
		init_p_light(scene, fig, mat);
}

void	copy_world_object(t_scene *scene, mlx_key_data_t key_data, t_vect *offset_origin)
{
	t_object	*selected_obj;
	t_material	mat;

	mat = new_standard_material();
	selected_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!selected_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	if (key_data.key == MLX_KEY_N && scene->object_selected)
	{
		selected_obj = ft_memcpy(selected_obj, get_selected_object(scene->objects, scene->lights), sizeof(t_object));
		selected_obj->edit_origin(selected_obj, vect_subtract(*offset_origin, selected_obj->get_origin(selected_obj)));
		init_copy(scene, selected_obj);
	}
	free(selected_obj);
}
