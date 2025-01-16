/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:20 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 16:43:13 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATION_H
# define TRANSFORMATION_H

# include "src/path_tracer/scene/camera/camera.h"
# include "src/path_tracer/scene/objects/objects.h"
# include "src/path_tracer/utils/vectors/vectors.h"

void	resize_disk(t_object *object, t_vect transformation);
void	translate_disk(t_object *object, t_vect transformation);
void	rotate_disk(t_object *object, t_camera *camera, t_vect transformation);

#endif