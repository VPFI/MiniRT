/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_mode.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:34:24 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/10 20:28:45 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDIT_MODE_H
# define EDIT_MODE_H

# include "src/path_tracer/scene/scene.h"
# include "src/path_tracer/scene/ray/ray.h"
# include "src/path_tracer/thread_management/thread_management.h"

void	edit_mode(t_thread *thread, uint32_t x, uint32_t y);

t_color	calc_pixel_color_normal(t_thread *thread, t_scene *scene, t_ray ray);

#endif