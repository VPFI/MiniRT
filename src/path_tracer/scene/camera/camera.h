/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:21:57 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:14:59 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "path_tracer/utils/vectors/vectors.h"

typedef struct s_camera
{
	t_vect		origin;
	t_vect		orientation;
	float		viewport_width;
	float		viewport_height;
	float		fov;
	float		focus_dist;
	float		defocus_angle;
	float		defocus_radius;
	t_vect		w;
	t_vect		u;
	t_vect		v;
	t_vect		defocus_disk_u;
	t_vect		defocus_disk_v;
	t_vect		vp_edge_vert;
	t_vect		vp_edge_horizntl;
	t_vect		pixel_delta_v;
	t_vect		pixel_delta_h;
	t_vect		viewport_origin;
	t_vect		viewport_pixel0;
}				t_camera;

void	init_camera(t_camera *camera, uint32_t width, uint32_t height);
void	recalculate_view(t_camera *camera, uint32_t width, uint32_t height);

#endif