/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:16:03 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/11 22:57:58 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

# include "src/path_tracer/utils/vectors/vectors.h"

typedef enum e_mat_type
{
	LAMBERTIAN = 0,
	METAL = 1,
	GLOSSY = 2,
	DIELECTRIC = 3,
	EMISSIVE = 4,
}			t_mat_type;

typedef struct s_material
{
	t_color		color;
	t_color		albedo;
	t_mat_type	type;
	float		specular;
	float		metal_roughness;
	float		refraction_index;
	float		emission_intensity;
	float		pattern_dim;
	bool		pattern;
}				t_material;

t_material	new_standard_plight(void);
t_material	new_standard_material(void);

#endif