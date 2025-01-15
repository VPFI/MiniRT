/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_rotations.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:43:00 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 18:09:35 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_ROTATION_H
# define OBJECT_ROTATION_H

# include "src/path_tracer/scene/camera/camera.h"
# include "src/path_tracer/scene/objects/objects.h"
# include "libraries/mlx/MLX42/include/MLX42/MLX42.h"

int	check_object_rotations(t_object *target_object, t_camera *camera, mlx_key_data_t key_data);

#endif