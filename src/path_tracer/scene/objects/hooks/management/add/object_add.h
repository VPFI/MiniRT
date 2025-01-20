/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_add.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:52:56 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 17:13:18 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_ADD_H
# define OBJECT_ADD_H

# include "path_tracer/scene/scene.h"

void	add_world_object(t_scene *scene,
			mlx_key_data_t key_data, t_vect *offset_origin);

#endif