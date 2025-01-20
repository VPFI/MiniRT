/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:40:20 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 19:12:51 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATIONS_H
# define TRANSFORMATIONS_H

# include "path_tracer/scene/camera/camera.h"
# include "path_tracer/utils/vectors/vectors.h"
# include "path_tracer/scene/objects/objects.h"

void	resize_quad(t_object *object, t_vect transformation);
void	translate_quad(t_object *object, t_vect transformation);
void	rotate_quad(t_object *object, t_camera *camera, t_vect transformation);

#endif