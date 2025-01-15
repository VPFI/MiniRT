/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_add.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:52:56 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 00:04:03 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_ADD_H
# define OBJECT_ADD_H

# include "src/path_tracer/scene/scene.h"

void	add_world_object(t_scene *scene, mlx_key_data_t key_data, t_vect *offset_origin);

#endif