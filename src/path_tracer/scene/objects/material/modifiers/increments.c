/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increments.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:13:32 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 18:17:31 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/MLX42/include/MLX42/MLX42.h"
#include "path_tracer/scene/objects/material/material.h"

void	increment_material_component(t_material *mat, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_J)
	{
		mat->specular += 0.05;
		if (mat->specular > 1.0)
			mat->specular = 1.0;
	}
	else if (key_data.key == MLX_KEY_K)
	{
		mat->metal_roughness += 0.05;
		if (mat->metal_roughness > 1.0)
			mat->metal_roughness = 1.0;
	}
	else if (key_data.key == MLX_KEY_L)
	{
		mat->refraction_index += 0.05;
		if (mat->refraction_index > 10.0)
			mat->refraction_index = 10.0;
	}
	else if (key_data.key == MLX_KEY_SEMICOLON)
	{
		mat->emission_intensity += 0.1;
		if (mat->emission_intensity > 10000.0)
			mat->emission_intensity = 10000.0;
	}
	mat->pattern = ((key_data.key == MLX_KEY_APOSTROPHE) + mat->pattern) % 2;
}

void	increment_color(t_material *material, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_Z)
	{
		material->color.x += 0.05;
		if (material->color.x > 1.0)
			material->color.x = 1.0;
	}
	else if (key_data.key == MLX_KEY_X)
	{
		material->color.y += 0.05;
		if (material->color.y > 1.0)
			material->color.y = 1.0;
	}
	else if (key_data.key == MLX_KEY_C)
	{
		material->color.z += 0.05;
		if (material->color.z > 1.0)
			material->color.z = 1.0;
	}
	return ;
}
