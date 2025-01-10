/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:37:02 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/10 20:18:40 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_MANAGEMENT_H
# define MEMORY_MANAGEMENT_H

# include "src/path_tracer/scene/scene.h"
# include "src/path_tracer/scene/objects/texture/texture.h"
# include "src/path_tracer/scene/objects/objects.h"

void	clean_memory(t_scene *scene);
void	free_boxes(t_object *objects);
void	free_objects(t_object **objects);
void	free_texture(t_texture **texture);
void	free_primitive(t_object **object);

#endif