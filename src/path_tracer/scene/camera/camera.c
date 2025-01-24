/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:41:19 by vpf               #+#    #+#             */
/*   Updated: 2025/01/24 14:04:40 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/scene.h"
#include "path_tracer/scene/objects/objects.h"
#include <math.h>

static void	calculate_viewport(t_camera *cam, uint32_t width, uint32_t height)
{
	t_vect	temp;

	temp = new_vect(0, 0, 0);
	cam->vp_edge_horizntl = vect_simple_mult(cam->u, cam->viewport_width);
	cam->vp_edge_vert = vect_simple_mult(vect_simple_mult(cam->v, -1.0),
			cam->viewport_height);
	cam->pixel_delta_h = vect_simple_div(cam->vp_edge_horizntl, width);
	cam->pixel_delta_v = vect_simple_div(cam->vp_edge_vert, height);
	cam->viewport_origin.x = cam->origin.x + (cam->focus_dist * cam->w.x)
		- (cam->vp_edge_horizntl.x / 2.0) - (cam->vp_edge_vert.x / 2.0);
	cam->viewport_origin.y = cam->origin.y + (cam->focus_dist * cam->w.y)
		- (cam->vp_edge_horizntl.y / 2.0) - (cam->vp_edge_vert.y / 2.0);
	cam->viewport_origin.z = cam->origin.z + (cam->focus_dist * cam->w.z)
		- (cam->vp_edge_horizntl.z / 2.0) - (cam->vp_edge_vert.z / 2.0);
	temp = vect_add(cam->pixel_delta_h, cam->pixel_delta_v);
	cam->viewport_pixel0.x = cam->viewport_origin.x + (0.5 * temp.x);
	cam->viewport_pixel0.y = cam->viewport_origin.y + (0.5 * temp.y);
	cam->viewport_pixel0.z = cam->viewport_origin.z + (0.5 * temp.z);
}

void	recalculate_view(t_camera *cam, uint32_t width, uint32_t height)
{
	t_vect	world_axis;

	world_axis = new_vect(0.0, 1.0, 0.0);
	cam->orientation = unit_vect(cam->orientation);
	cam->viewport_height = 2.0 * tanf((cam->fov * M_PI / 180) * 0.5)
		* cam->focus_dist;
	cam->viewport_width = cam->viewport_height * (width / (float)height);
	cam->w = cam->orientation;
	if (vect_dot(cam->w, world_axis) == 1.0
		|| vect_dot(cam->w, world_axis) == -1.0)
	{
		world_axis = new_vect(0.0, 0.0, 1.0);
	}
	cam->u = unit_vect(vect_cross(cam->w, world_axis));
	cam->v = unit_vect(vect_cross(cam->u, cam->w));
	cam->defocus_radius = cam->focus_dist
		* (tanf((cam->defocus_angle * M_PI / 180) * 0.5));
	cam->defocus_disk_u = vect_simple_mult(cam->u, cam->defocus_radius);
	cam->defocus_disk_v = vect_simple_mult(cam->v, cam->defocus_radius);
	calculate_viewport(cam, width, height);
}

void	init_camera(t_camera *camera, uint32_t width, uint32_t height)
{
	camera->origin = new_vect(0, 1, 2);
	camera->orientation = unit_vect(new_vect(0, 0, -1));
	camera->fov = FOV;
	camera->defocus_angle = DEFOCUS;
	camera->focus_dist = FOCUS_DIST;
	recalculate_view(camera, width, height);
}
