/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_hooks.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:31:04 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 13:38:37 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HOOKS_H
# define CAMERA_HOOKS_H

# include "path_tracer/scene/camera/camera.h"
# include "path_tracer/scene/objects/objects.h"
# include "mlx/MLX42/include/MLX42/MLX42.h"

int	check_settings(t_camera *cam, mlx_key_data_t key_data);
int	check_rotations(t_camera *cam, mlx_key_data_t key_data);
int	check_reset(t_camera *cam, t_camera *backup, mlx_key_data_t key_data);
int	check_translations(t_camera *cam, t_object *sky_sphere, mlx_key_data_t key);

#endif