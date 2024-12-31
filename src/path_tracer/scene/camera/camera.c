/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:41:19 by vpf               #+#    #+#             */
/*   Updated: 2024/12/31 02:29:23 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



t_vect	get_random_disk_sample(uint32_t *state)
{
	t_vect	res;

	while (true)
	{
		res = new_vect((fast_rand(state) * 2.0) - 1.0, (fast_rand(state) * 2.0) - 1.0, 0.0);
		if (vect_length(res) < 1.0) //sample from -1,1 square | keep only the ones inside disk
			return (res);
	}
}

t_vect	defocus_sample(t_camera camera, uint32_t *state)
{
	t_vect	disk_sample;
	t_vect	res;

	if (camera.defocus_angle <= 0)
		return (camera.origin);
	disk_sample = get_random_disk_sample(state);
	res = vect_add(vect_simple_mult(camera.defocus_disk_u, disk_sample.x), vect_simple_mult(camera.defocus_disk_v, disk_sample.y));
	return (vect_add(camera.origin, res));
}

void	recalculate_view(t_scene *scene)
{
	t_vect temp;
	t_vect world_axis;

	world_axis = new_vect(0.0, 1.0, 0.0);

	scene->camera.orientation = unit_vect(scene->camera.orientation);

	scene->camera.viewport_height = 2.0 * tanf((scene->camera.fov * M_PI / 180) * 0.5) * scene->camera.focus_dist;
	scene->camera.viewport_width = scene->camera.viewport_height * (scene->width / (float)scene->height);

	scene->camera.w = scene->camera.orientation;
	if (vect_dot(scene->camera.w, world_axis) == 1.0
		|| vect_dot(scene->camera.w, world_axis) == -1.0)
	{
		world_axis = new_vect(0.0, 0.0, 1.0);
	}
	scene->camera.u = unit_vect(vect_cross(scene->camera.w, world_axis));
	scene->camera.v = unit_vect(vect_cross(scene->camera.u, scene->camera.w));

	scene->camera.defocus_radius = scene->camera.focus_dist * (tanf((scene->camera.defocus_angle * M_PI / 180) * 0.5));
	scene->camera.defocus_disk_u = vect_simple_mult(scene->camera.u, scene->camera.defocus_radius);
	scene->camera.defocus_disk_v = vect_simple_mult(scene->camera.v, scene->camera.defocus_radius);

	scene->camera.vp_edge_horizntl = vect_simple_mult(scene->camera.u, scene->camera.viewport_width);
	scene->camera.vp_edge_vert = vect_simple_mult(vect_simple_mult(scene->camera.v, -1.0), scene->camera.viewport_height);
	
	scene->camera.pixel_delta_h = vect_simple_div(scene->camera.vp_edge_horizntl, scene->width);
	scene->camera.pixel_delta_v = vect_simple_div(scene->camera.vp_edge_vert, scene->height);
	
	scene->camera.viewport_origin.x = scene->camera.origin.x + (scene->camera.focus_dist * scene->camera.w.x) - (scene->camera.vp_edge_horizntl.x / 2.0) - (scene->camera.vp_edge_vert.x / 2.0);	
	scene->camera.viewport_origin.y = scene->camera.origin.y + (scene->camera.focus_dist * scene->camera.w.y) - (scene->camera.vp_edge_horizntl.y / 2.0) - (scene->camera.vp_edge_vert.y / 2.0);
	scene->camera.viewport_origin.z = scene->camera.origin.z + (scene->camera.focus_dist * scene->camera.w.z) - (scene->camera.vp_edge_horizntl.z / 2.0) - (scene->camera.vp_edge_vert.z / 2.0);
	temp = vect_add(scene->camera.pixel_delta_h, scene->camera.pixel_delta_v);
	scene->camera.viewport_pixel0.x = scene->camera.viewport_origin.x + (0.5 * temp.x);
	scene->camera.viewport_pixel0.y = scene->camera.viewport_origin.y + (0.5 * temp.y);
	scene->camera.viewport_pixel0.z = scene->camera.viewport_origin.z + (0.5 * temp.z);
}

void	init_camera(t_camera *camera, uint32_t width, uint32_t height)
{
	t_vect temp;
	t_vect world_axis;

	world_axis = new_vect(0.0, 1.0, 0.0);
	
	camera->origin = new_vect(0, 1, 2);
	camera->orientation = unit_vect(new_vect(0, 0, -1));
	camera->fov = FOV;
	camera->defocus_angle = DEFOCUS;
	camera->focus_dist = FOCUS_DIST;
	camera->viewport_height = 2.0 * tanf((camera->fov * M_PI / 180) * 0.5) * camera->focus_dist;
	camera->viewport_width = camera->viewport_height * (width / (float)height);

	camera->w = camera->orientation;
	if (vect_dot(camera->w, world_axis) == 1.0
		|| vect_dot(camera->w, world_axis) == -1.0)
	{
		world_axis = new_vect(0.0, 0.0, 1.0);
	}
	camera->u = unit_vect(vect_cross(camera->w, new_vect(0, 1, 0)));
	camera->v = unit_vect(vect_cross(camera->u, camera->w));

	camera->defocus_radius = camera->focus_dist * (tanf((camera->defocus_angle * M_PI / 180) * 0.5));
	camera->defocus_disk_u = vect_simple_mult(camera->u, camera->defocus_radius);
	camera->defocus_disk_v = vect_simple_mult(camera->v, camera->defocus_radius);

	camera->vp_edge_horizntl = vect_simple_mult(camera->u, camera->viewport_width);
	camera->vp_edge_vert = vect_simple_mult(vect_simple_mult(camera->v, -1.0), camera->viewport_height);
	
	camera->pixel_delta_h = vect_simple_div(camera->vp_edge_horizntl, width);
	camera->pixel_delta_v = vect_simple_div(camera->vp_edge_vert, height);
	
	camera->viewport_origin.x = camera->origin.x + (camera->focus_dist * camera->w.x) - (camera->vp_edge_horizntl.x / 2.0) - (camera->vp_edge_vert.x / 2.0);	
	camera->viewport_origin.y = camera->origin.y + (camera->focus_dist * camera->w.y) - (camera->vp_edge_horizntl.y / 2.0) - (camera->vp_edge_vert.y / 2.0);
	camera->viewport_origin.z = camera->origin.z + (camera->focus_dist * camera->w.z) - (camera->vp_edge_horizntl.z / 2.0) - (camera->vp_edge_vert.z / 2.0);
	temp = vect_add(camera->pixel_delta_h, camera->pixel_delta_v);
	camera->viewport_pixel0.x = camera->viewport_origin.x + (0.5 * temp.x);
	camera->viewport_pixel0.y = camera->viewport_origin.y + (0.5 * temp.y);
	camera->viewport_pixel0.z = camera->viewport_origin.z + (0.5 * temp.z);
}
