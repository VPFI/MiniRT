/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:37:02 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 21:06:31 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_MANAGEMENT_H
# define MEMORY_MANAGEMENT_H

# include "path_tracer/scene/scene.h"
# include "path_tracer/scene/objects/texture/texture_objects.h"
# include "path_tracer/scene/objects/objects.h"

void	clean_memory(t_scene *scene);
void	free_boxes(t_object *objects);
void	free_objects(t_object **objects);
void	free_texture(t_texture **texture);
void	free_primitive(t_object **object);

#endif