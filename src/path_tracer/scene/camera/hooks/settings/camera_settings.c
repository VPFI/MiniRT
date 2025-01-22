/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:19:30 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 19:42:41 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/camera/camera.h"
#include "mlx/MLX42/include/MLX42/MLX42.h"
#include <stdio.h>

void	modify_fov(t_camera *camera, mlx_key_data_t key_data)
{
	if (key_data.modifier == MLX_CONTROL)
	{
		if (camera->fov > 1)
			camera->fov -= 1;
	}
	else
		camera->fov += 1;
	printf("FOV: %f\n", camera->fov);
}

void	modify_defocus(t_camera *camera, mlx_key_data_t key_data)
{
	if (key_data.modifier == MLX_CONTROL)
	{
		camera->defocus_angle -= 0.25;
		if (camera->defocus_angle < 0)
			camera->defocus_angle = 0;
	}
	else
		camera->defocus_angle += 0.25;
	printf("DEFOCUS ANGLE: %f\n", camera->defocus_angle);
}

void	modify_focus_dist(t_camera *camera, mlx_key_data_t key_data)
{
	if (key_data.modifier == MLX_CONTROL)
	{
		if (camera->focus_dist > 1)
			camera->focus_dist -= 0.5;
	}
	else
		camera->focus_dist += 0.5;
	printf("FOCUS DIST: %f\n", camera->focus_dist);
}
