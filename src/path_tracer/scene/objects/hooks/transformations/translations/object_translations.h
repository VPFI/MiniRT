/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_translations.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:43:12 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 18:00:30 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_TRANSLATION_H
# define OBJECT_TRANSLATION_H

# include "src/path_tracer/scene/camera/camera.h"
# include "src/path_tracer/scene/objects/objects.h"
# include "libraries/mlx/MLX42/include/MLX42/MLX42.h"

t_vect	absolute_translate(mlx_key_data_t key_data);
t_vect	relative_translate(t_camera *camera, mlx_key_data_t key_data);
int		check_object_translations(t_object *target_object, t_camera *camera, mlx_key_data_t key_data);

#endif