/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_scatter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:29:18 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 01:12:04 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_SCATTER_H
# define RAY_SCATTER_H

# include "src/path_tracer/scene/ray/ray.h"
# include "src/path_tracer/scene/objects/objects.h"
# include "src/path_tracer/thread_management/thread_management.h"
# include <stdbool.h>

bool	scatter_ray(t_thread *thread, t_hit_info hit_info, t_ray *bounce_ray, t_ray ray, t_color *emittance);

#endif