/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:52:48 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 17:11:17 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/scene.h"
#include "path_tracer/utils/vectors/vectors.h"
#include "mlx/MLX42/include/MLX42/MLX42.h"

#include "path_tracer/scene/objects/figures/sphere/sphere.h"
#include "path_tracer/scene/objects/figures/plane/plane.h"
#include "path_tracer/scene/objects/figures/quad/quad.h"
#include "path_tracer/scene/objects/figures/box/box.h"
#include "path_tracer/scene/objects/figures/disk/disk.h"
#include "path_tracer/scene/objects/figures/cylinder/cylinder.h"
#include "path_tracer/scene/objects/figures/cone/cone.h"
#include "path_tracer/scene/objects/figures/p_light/p_light.h"

void	add_world_object(t_scene *scene,
	mlx_key_data_t key_data, t_vect *offset_origin)
{
	if (key_data.key == MLX_KEY_1)
		set_new_fig_sphere(scene, offset_origin);
	else if (key_data.key == MLX_KEY_2)
		set_new_fig_plane(scene, offset_origin);
	else if (key_data.key == MLX_KEY_3)
		set_new_fig_quad(scene, offset_origin);
	else if (key_data.key == MLX_KEY_4)
		set_new_fig_box(scene, offset_origin);
	else if (key_data.key == MLX_KEY_5)
		set_new_fig_disk(scene, offset_origin);
	else if (key_data.key == MLX_KEY_6)
		set_new_fig_cylinder(scene, offset_origin);
	else if (key_data.key == MLX_KEY_7)
		set_new_fig_cone(scene, offset_origin);
	else if (key_data.key == MLX_KEY_8)
		set_new_fig_p_light(scene, offset_origin);
}
