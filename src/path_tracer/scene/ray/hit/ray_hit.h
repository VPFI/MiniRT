/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:29:21 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 21:26:19 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_HIT_H
# define RAY_HIT_H

struct s_object;
struct s_hit_info;

typedef enum e_bounds
{
	MIN = 0,
	MAX = 1,
}			t_bounds;

bool	shadow_hit(struct s_object *objects, t_ray ray, struct s_hit_info *hit_info, float max);
bool	ray_hit(struct s_object *objects, t_ray ray, struct s_hit_info *hit_info, struct s_object *sky_sphere);
bool	ray_hit_plus_lights(struct s_object *objects, struct s_object *plights, t_ray ray, struct s_hit_info *hit_info);

#endif