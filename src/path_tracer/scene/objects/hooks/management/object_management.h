/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_management.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:46:03 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/14 23:58:30 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_MANAGEMENT_H
# define OBJECT_MANAGEMENT_H

# include "src/path_tracer/scene/scene.h"
# include "src/path_tracer/scene/objects/objects.h"

void	    deselect_objects(t_object *objects, t_object *lights, bool *object_selected);
void	    select_object(t_scene *scene, uint32_t x, uint32_t y);
void	    manage_world_objects(t_scene *scene, mlx_key_data_t key_data);
t_object	*get_selected_object(t_object *objects, t_object *lights);

#endif