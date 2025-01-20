/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_sampling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:28:52 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 15:42:34 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_SAMPLING_H
# define LIGHT_SAMPLING_H

# include "path_tracer/utils/vectors/vectors.h"
# include "path_tracer/scene/objects/objects.h"
# include "path_tracer/scene/objects/material/material.h"
# include "path_tracer/thread_management/thread_management.h"

t_color	light_sampling(t_thread *thread, t_hit_info ht, t_mat_type scatter);

#endif