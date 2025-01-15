/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:29:21 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 17:04:56 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_HIT_H
# define RAY_HIT_H

# include "src/path_tracer/scene/scene.h"
# include "src/path_tracer/scene/ray/ray.h"
# include "src/path_tracer/scene/objects/objects.h"

typedef enum e_bounds
{
	MIN = 0,
	MAX = 1,
}			t_bounds;

bool	shadow_hit(t_scene *scene, t_ray ray, t_hit_info *hit_info, float max);
bool	ray_hit(t_object *objects, t_ray ray, t_hit_info *hit_info, t_object *sky_sphere);
bool	ray_hit_plus_lights(t_object *objects, t_object *plights, t_ray ray, t_hit_info *hit_info);

#endif