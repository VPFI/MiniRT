/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:46:35 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 00:46:36 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "path_tracer/scene/scene.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/material/material.h"
#include "path_tracer/scene/objects/hooks/management/object_management.h"
#include "error_management/error_management.h"

#include "path_tracer/scene/objects/figures/sphere/sphere.h"
#include "path_tracer/scene/objects/figures/plane/plane.h"
#include "path_tracer/scene/objects/figures/quad/quad.h"
#include "path_tracer/scene/objects/figures/box/box.h"
#include "path_tracer/scene/objects/figures/disk/disk.h"
#include "path_tracer/scene/objects/figures/cylinder/cylinder.h"
#include "path_tracer/scene/objects/figures/cone/cone.h"
#include "path_tracer/scene/objects/figures/p_light/p_light.h"

static void	init_copy(t_scene *scene, t_object *tar_obj)
{
	t_figure	fig;
	t_texture	*tx;
	t_material	mat;

	tx = NULL;
	if (tar_obj->texture)
		tx = get_texture(tar_obj->texture->path, tar_obj->texture->texture_dim);
	fig = tar_obj->figure;
	mat = tar_obj->material;
	if (tar_obj->type == SPHERE)
		init_sphere(scene, fig, mat, tx);
	else if (tar_obj->type == PLANE)
		init_plane(scene, fig, mat, tx);
	else if (tar_obj->type == QUAD)
		init_quad(scene, fig, mat, tx);
	else if (tar_obj->type == BOX)
		init_box(scene, fig, mat, tx);
	else if (tar_obj->type == DISK)
		init_disk(scene, fig, mat, tx);
	else if (tar_obj->type == CYLINDER)
		init_cylinder(scene, fig, mat, tx);
	else if (tar_obj->type == CONE)
		init_cone(scene, fig, mat, tx);
	else if (tar_obj->type == LIGHT)
		init_p_light(scene, fig, mat);
}

void	copy_world_object(t_scene *scene,
	mlx_key_data_t key_data, t_vect *offset_origin)
{
	t_object	*target_obj;

	target_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!target_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	if (key_data.key == MLX_KEY_N && scene->object_selected)
	{
		target_obj = ft_memcpy(target_obj,
				get_selected_object(scene->objects, scene->lights),
				sizeof(t_object));
		target_obj->edit_origin(target_obj,
			vect_subtract(*offset_origin, target_obj->get_origin(target_obj)));
		init_copy(scene, target_obj);
	}
	free(target_obj);
}
