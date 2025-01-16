/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_transformations.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:48:48 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:15:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_TRANSFORMATIONS_H
# define OBJECT_TRANSFORMATIONS_H

# include "path_tracer/scene/scene.h"
# include "path_tracer/scene/objects/objects.h"
# include "mlx/MLX42/include/MLX42/MLX42.h"

# include "path_tracer/scene/objects/hooks/transformations/aspect/object_aspect.h"
# include "path_tracer/scene/objects/hooks/transformations/resize/object_resize.h"
# include "path_tracer/scene/objects/hooks/transformations/rotations/object_rotations.h"
# include "path_tracer/scene/objects/hooks/transformations/translations/object_translations.h"

t_vect	clamp_object_coords(t_object *target_object);
int		check_object_focus(t_object *target_object, t_scene *scene, mlx_key_data_t key_data);
void	transform_object(t_object *objects, t_object *lights, t_scene *scene, mlx_key_data_t key_data);

#endif