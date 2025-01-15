/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:27:26 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 00:39:50 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_UTILS_H
# define CAMERA_UTILS_H

# include "src/path_tracer/scene/camera/camera.h"
# include "src/path_tracer/scene/objects/objects.h"
# include "libraries/mlx/MLX42/include/MLX42/MLX42.h"

t_vect	defocus_sample(t_camera camera, uint32_t *state);
t_vect	set_pixel(t_camera camera, uint32_t x, uint32_t y);
t_vect	set_pixel_offset(t_camera camera, uint32_t x, uint32_t y, uint32_t *state);
void	move_camera(t_camera *camera, t_camera *backup, t_object *skysphere, mlx_key_data_t key_data);

#endif