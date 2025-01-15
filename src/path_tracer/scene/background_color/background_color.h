/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_color.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:37:52 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/14 19:24:13 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKGROUND_COLOR_H
# define BACKGROUND_COLOR_H

# include "src/path_tracer/scene/ray/ray.h"
# include "src/path_tracer/thread_management/thread_management.h"

t_color	get_background_color(t_thread *thread, t_ray *ray);

#endif