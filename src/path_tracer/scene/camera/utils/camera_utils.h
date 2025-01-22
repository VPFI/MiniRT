/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:27:26 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 13:46:06 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_UTILS_H
# define CAMERA_UTILS_H

# include "path_tracer/scene/camera/camera.h"
# include "path_tracer/scene/objects/objects.h"
# include "mlx/MLX42/include/MLX42/MLX42.h"

t_vect	defocus_sample(t_camera cam, uint32_t *state);
t_vect	set_pixel(t_camera cam, uint32_t x, uint32_t y);
t_vect	set_pixel_offset(t_camera cam, uint32_t x, uint32_t y, uint32_t *state);
void	move_camera(t_camera *cam, t_camera *backup,
			t_object *skysphere, mlx_key_data_t key_data);

#endif