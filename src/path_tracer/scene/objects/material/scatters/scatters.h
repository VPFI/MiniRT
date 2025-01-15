/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scatters.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:48:20 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 17:00:30 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCATTER_H
# define SCATTER_H

# include "src/path_tracer/scene/ray/ray.h"
# include "src/path_tracer/utils/vectors/vectors.h"
# include "src/path_tracer/scene/objects/objects.h"
# include "src/path_tracer/thread_management/thread_management.h"

# define AIR_REF_INDEX	1.0003

float	reflectance(float index, float cos);
t_ray	refract(t_hit_info hit_info, t_vect udir, float index, float cos);
t_ray	lambertian_scatter(uint32_t *state, t_hit_info hit_info, t_color *emittance, t_thread *thread);
t_ray	metal_scatter(uint32_t *state, t_hit_info hit_info, t_ray inc_ray, t_color *emittance, t_thread *thread);
t_ray	dielectric_scatter(uint32_t *state, t_hit_info hit_info, t_ray inc_ray, t_color *emittance, t_thread *thread);

#endif