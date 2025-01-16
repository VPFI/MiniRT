/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increments.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:13:32 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:15:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/MLX42/include/MLX42/MLX42.h"
#include "path_tracer/scene/objects/material/material.h"

void	increment_material_component(t_material *material, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_J)
	{
		material->specular += 0.05;
		if (material->specular > 1.0)
			material->specular = 1.0;
	}
	else if (key_data.key == MLX_KEY_K)
	{
		material->metal_roughness += 0.05;
		if (material->metal_roughness > 1.0)
			material->metal_roughness = 1.0;
	}
	else if (key_data.key == MLX_KEY_L)
	{
		material->refraction_index += 0.05;
		if (material->refraction_index > 10.0)
			material->refraction_index = 10.0;
	}
	else if (key_data.key == MLX_KEY_SEMICOLON)
	{
		material->emission_intensity += 0.05;
		if (material->emission_intensity > 10000.0)
			material->emission_intensity = 10000.0;
	}
	else if (key_data.key == MLX_KEY_APOSTROPHE)
		material->pattern = true;
	return ;
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
