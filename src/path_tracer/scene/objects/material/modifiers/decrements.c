/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decrements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:14:08 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 17:14:24 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	decrement_material_component(t_object *target_object, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_J)
	{
		target_object->material.specular -= 0.05;
		if (target_object->material.specular < 0.0)
			target_object->material.specular = 0.0;
	}
	else if (key_data.key == MLX_KEY_K)
	{
		target_object->material.metal_roughness -= 0.05;
		if (target_object->material.metal_roughness < 0.0)
			target_object->material.metal_roughness = 0.0;
	}
	else if (key_data.key == MLX_KEY_L)
	{
		target_object->material.refraction_index -= 0.05;
		if (target_object->material.refraction_index < 0.0)
			target_object->material.refraction_index = 0.0;
	}
	else if (key_data.key == MLX_KEY_SEMICOLON)
	{
		target_object->material.emission_intensity -= 0.05;
		if (target_object->material.emission_intensity < 0.0)
			target_object->material.emission_intensity = 0.0;
	}
	else if (key_data.key == MLX_KEY_APOSTROPHE)
		target_object->material.pattern = false;
	return ;
}

void	decrement_color(t_object *target_object, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_Z)
	{
		target_object->material.color.x -= 0.05;
		if (target_object->material.color.x < 0.0)
			target_object->material.color.x = 0.0;
	}
	else if (key_data.key == MLX_KEY_X)
	{
		target_object->material.color.y -= 0.05;
		if (target_object->material.color.y < 0.0)
			target_object->material.color.y = 0.0;
	}
	else if (key_data.key == MLX_KEY_C)
	{
		target_object->material.color.z -= 0.05;
		if (target_object->material.color.z < 0.0)
			target_object->material.color.z = 0.0;
	}
	return ;
}
