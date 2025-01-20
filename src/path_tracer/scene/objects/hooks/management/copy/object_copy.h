/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_copy.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:46:44 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 14:31:50 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_COPY_H
# define OBJECT_COPY_H

# include "path_tracer/scene/scene.h"

void	copy_world_object(t_scene *scene, mlx_key_data_t key_data, t_vect *o_o);

#endif