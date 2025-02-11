/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:12:16 by vpf               #+#    #+#             */
/*   Updated: 2025/01/24 00:05:57 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/utils/vectors/vectors.h"
#include "mlx/MLX42/include/MLX42/MLX42.h"
#include "path_tracer/utils/math/math_utils.h"
#include "path_tracer/scene/objects/material/material.h"
#include <math.h>
#include <stdbool.h>

t_material	new_standard_material(void)
{
	t_material	mat;
	uint32_t	seed;

	seed = (uint32_t)(mlx_get_time() * 10000);
	mat.color = new_color(fast_rand(&seed), fast_rand(&seed), fast_rand(&seed));
	mat.specular = 0.2;
	mat.metal_roughness = 0.1;
	mat.refraction_index = 1.5;
	mat.emission_intensity = 1.0;
	mat.pattern_dim = M_PI / 6;
	mat.pattern = false;
	mat.type = LAMBERTIAN;
	return (mat);
}

t_material	new_standard_plight(void)
{
	t_material	mat;
	uint32_t	state;

	state = (uint32_t)(mlx_get_time() * 10000);
	mat.color = new_color((fast_rand(&state) + 1) / 2,
			(fast_rand(&state) + 1) / 2, (fast_rand(&state) + 1) / 2);
	mat.specular = 1;
	mat.metal_roughness = 1;
	mat.refraction_index = 1;
	mat.emission_intensity = 1;
	mat.pattern_dim = 1;
	mat.pattern = false;
	mat.type = EMISSIVE;
	return (mat);
}
