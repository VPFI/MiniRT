/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increments.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:13:32 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 17:13:55 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	increment_material_component(t_object *target_object, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_J)
	{
		target_object->material.specular += 0.05;
		if (target_object->material.specular > 1.0)
			target_object->material.specular = 1.0;
	}
	else if (key_data.key == MLX_KEY_K)
	{
		target_object->material.metal_roughness += 0.05;
		if (target_object->material.metal_roughness > 1.0)
			target_object->material.metal_roughness = 1.0;
	}
	else if (key_data.key == MLX_KEY_L)
	{
		target_object->material.refraction_index += 0.05;
		if (target_object->material.refraction_index > 10.0)
			target_object->material.refraction_index = 10.0;
	}
	else if (key_data.key == MLX_KEY_SEMICOLON)
	{
		target_object->material.emission_intensity += 0.05;
		if (target_object->material.emission_intensity > 10000.0)
			target_object->material.emission_intensity = 10000.0;
	}
	else if (key_data.key == MLX_KEY_APOSTROPHE)
		target_object->material.pattern = true;
	return ;
}

void	increment_color(t_object *target_object, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_Z)
	{
		target_object->material.color.x += 0.05;
		if (target_object->material.color.x > 1.0)
			target_object->material.color.x = 1.0;
	}
	else if (key_data.key == MLX_KEY_X)
	{
		target_object->material.color.y += 0.05;
		if (target_object->material.color.y > 1.0)
			target_object->material.color.y = 1.0;
	}
	else if (key_data.key == MLX_KEY_C)
	{
		target_object->material.color.z += 0.05;
		if (target_object->material.color.z > 1.0)
			target_object->material.color.z = 1.0;
	}
	return ;
}