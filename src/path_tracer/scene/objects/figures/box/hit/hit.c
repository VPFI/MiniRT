/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:43:01 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 20:14:45 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/ray/ray.h"
#include "path_tracer/scene/objects/objects.h"
#include "path_tracer/scene/objects/figures/figures.h"

bool	hit_box(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	t_hit_info	internal_ht;

	if (ray_hit(fig.box.faces, ray, &internal_ht, NULL))
	{
		if (internal_ht.t <= bounds[MIN] || bounds[MAX] <= internal_ht.t)
			return (false);
		hit_info->t = internal_ht.t;
		return (true);
	}
	return (false);
}
