/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scatters.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:48:20 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 19:00:39 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCATTERS_H
# define SCATTERS_H

# include "path_tracer/scene/ray/ray.h"
# include "path_tracer/utils/vectors/vectors.h"
# include "path_tracer/thread_management/thread_management.h"

# define AIR_REF_INDEX	1.0003

struct	s_hit_info;

float	reflectance(float index, float cos);
t_ray	refract(struct s_hit_info hit_info, t_vect udir, float indx, float cos);
t_ray	lambertian_scatter(struct s_hit_info hit_info,
			t_color *emittance, t_thread *thread);
t_ray	metal_scatter(struct s_hit_info hit_info,
			t_ray inc_ray, t_color *emittance, t_thread *thread);
t_ray	dielectric_scatter(struct s_hit_info hit_info,
			t_ray inc_ray, t_color *emittance, t_thread *thread);

#endif