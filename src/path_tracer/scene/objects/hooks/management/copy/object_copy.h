/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_copy.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:46:44 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 00:05:00 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_COPY_H
# define OBJECT_COPY_H

# include "src/path_tracer/scene/scene.h"

void	copy_world_object(t_scene *scene, mlx_key_data_t key_data, t_vect *offset_origin);

#endif