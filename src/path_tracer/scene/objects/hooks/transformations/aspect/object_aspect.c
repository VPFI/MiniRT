/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_aspect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:42:05 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 17:49:36 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	check_object_aspect(t_object *target_object, mlx_key_data_t key_data)
{
	if (is_rgb_key_down(key_data))
	{
		if (key_data.modifier == MLX_CONTROL)
			decrement_color(target_object, key_data);
		else
			increment_color(target_object, key_data);
		print_vec_s(target_object->material.color, "NEW COLOR:");

		return (1);
	}
	else if (is_material_key_down(key_data))
	{
		if (key_data.modifier == MLX_CONTROL)
			decrement_material_component(target_object, key_data);
		else
			increment_material_component(target_object, key_data);
		printf("Material components:\n Specular: %f Roughness: %f Refraction index: %f Light intensity: %f\n\n",
			target_object->material.specular, target_object->material.metal_roughness,
			target_object->material.refraction_index, target_object->material.emission_intensity);
		return (1);		
	}
	else if (key_data.key == MLX_KEY_TAB)
	{
		cicle_material_type(target_object);
	}
	return (0);
}
