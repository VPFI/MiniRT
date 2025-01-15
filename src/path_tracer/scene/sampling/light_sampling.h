/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_sampling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:28:52 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 16:55:55 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_SAMPLING_H
# define LIGHT_SAMPLING_H

# include "src/path_tracer/utils/vectors/vectors.h"
# include "src/path_tracer/scene/objects/objects.h"
# include "src/path_tracer/scene/objects/material/material.h"
# include "src/path_tracer/thread_management/thread_management.h"

t_color	light_sampling(t_thread *thread, t_hit_info hit_info, t_mat_type scatter_type);

#endif