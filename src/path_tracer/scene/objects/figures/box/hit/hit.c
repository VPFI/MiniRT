/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:43:01 by vpf               #+#    #+#             */
/*   Updated: 2025/01/16 15:09:45 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/path_tracer/scene/ray/ray.h"
#include "src/path_tracer/scene/objects/objects.h"
#include "src/path_tracer/scene/objects/figures/figures.h"

bool	hit_box(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	t_hit_info	internal_hit_info;

	if (ray_hit(fig.box.faces, ray, &internal_hit_info, NULL))
	{
		if (internal_hit_info.t <= bounds[MIN] || bounds[MAX] <= internal_hit_info.t)
			return (false);
		hit_info->t = internal_hit_info.t;
		return (true);
	}
	return (false);
}
