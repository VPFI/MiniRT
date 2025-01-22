/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_aspect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:42:05 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 19:10:31 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/MLX42/include/MLX42/MLX42.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/material/material.h"
#include "window_management/key_identifiers/key_identifiers.h"
#include "path_tracer/utils/print/print_utils.h"
#include <stdio.h>

void	check_object_aspect(t_object *tar_obj, mlx_key_data_t key_data)
{
	if (is_rgb_key_down(key_data))
	{
		if (key_data.modifier == MLX_CONTROL)
			decrement_color(&tar_obj->material, key_data);
		else
			increment_color(&tar_obj->material, key_data);
		print_vec_s(tar_obj->material.color, "NEW COLOR:");
	}
	else if (is_material_key_down(key_data))
	{
		if (key_data.modifier == MLX_CONTROL)
			decrement_material_component(&tar_obj->material, key_data);
		else
			increment_material_component(&tar_obj->material, key_data);
		printf(ASPECT_CHANGE_MSG,
			tar_obj->material.specular,
			tar_obj->material.metal_roughness,
			tar_obj->material.refraction_index,
			tar_obj->material.emission_intensity,
			tar_obj->material.pattern);
	}
	else if (key_data.key == MLX_KEY_TAB)
		cicle_material_type(&tar_obj->material);
}
