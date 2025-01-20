/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:20 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 19:44:07 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATIONS_H
# define TRANSFORMATIONS_H

# include "path_tracer/scene/camera/camera.h"
# include "path_tracer/scene/objects/objects.h"
# include "path_tracer/utils/vectors/vectors.h"

void	resize_disk(t_object *object, t_vect transformation);
void	translate_disk(t_object *object, t_vect transformation);
void	rotate_disk(t_object *object, t_camera *camera, t_vect transformation);

#endif