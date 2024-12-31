/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:56:04 by vperez-f          #+#    #+#             */
/*   Updated: 2024/12/30 22:13:31 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



void	copy_world_object(t_scene *scene, mlx_key_data_t key_data, t_vect *offset_origin)
{
	t_object	*selected_obj;
	t_material	mat;

	mat = new_standard_material();
	selected_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!selected_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	if (key_data.key == MLX_KEY_N && scene->object_selected)
	{
		selected_obj = ft_memcpy(selected_obj, get_selected_object(scene->objects, scene->lights), sizeof(t_object));
		selected_obj->edit_origin(selected_obj, vect_subtract(*offset_origin, selected_obj->get_origin(selected_obj)));
		init_copy(scene, selected_obj);
	}
	free(selected_obj);
}

void	manage_world_objects(t_scene *scene, mlx_key_data_t key_data)
{
	t_ray		camera_ray;
	t_vect		offset_origin;

	if (is_num_key_down(key_data))
	{
		camera_ray = new_ray(scene->camera.orientation, scene->camera.origin);
		offset_origin = vect_add(ray_at(camera_ray, scene->camera.focus_dist + 1), get_random_uvect(&scene->state));
		add_world_object(scene, key_data, &offset_origin);
	}
	else if (key_data.key == MLX_KEY_N && scene->object_selected)
	{
		camera_ray = new_ray(scene->camera.orientation, scene->camera.origin);
		offset_origin = vect_add(ray_at(camera_ray, scene->camera.focus_dist + 1), get_random_uvect(&scene->state));
		copy_world_object(scene, key_data, &offset_origin);
	}
	else if (key_data.key == MLX_KEY_BACKSPACE && scene->object_selected)
	{
		delete_world_object(scene);
	}
}

void	delete_from_objects(t_scene *scene)
{
	t_object	*obj;
	t_object	*prev_object;
	t_object	*next_object;

	obj = scene->objects;
	prev_object = NULL;
	next_object = NULL;
	if (obj && obj->selected)
		scene->objects = obj->next;
	while (obj && !obj->selected)
	{
		if (obj->next && obj->next->selected)
		{
			prev_object = obj;
			next_object = obj->next->next;
		}
		obj = obj->next;
	}
	if (prev_object)
		prev_object->next = next_object;
	if (obj && obj->selected)
		free_primitive(&obj);
}
void	delete_from_lights(t_scene *scene)
{
	t_object	*obj;
	t_object	*prev_object;
	t_object	*next_object;

	obj = scene->lights;
	prev_object = NULL;
	next_object = NULL;
	if (obj && obj->selected)
		scene->lights = obj->next;
	while (obj && !obj->selected)
	{
		if (obj->next && obj->next->selected)
		{
			prev_object = obj;
			next_object = obj->next->next;
		}
		obj = obj->next;
	}
	if (prev_object)
		prev_object->next = next_object;
	if (obj && obj->selected)
		free(obj);
}

void	delete_world_object(t_scene *scene)
{
	delete_from_objects(scene);
	delete_from_lights(scene);
	scene->object_selected = false;
}

void	add_world_object(t_scene *scene, mlx_key_data_t key_data, t_vect *offset_origin)
{
	if (key_data.key == MLX_KEY_1)
		set_new_fig_sphere(scene, offset_origin);
	else if (key_data.key == MLX_KEY_2)
		set_new_fig_plane(scene, offset_origin);
	else if (key_data.key == MLX_KEY_3)
		set_new_fig_quad(scene, offset_origin);
	else if (key_data.key == MLX_KEY_4)
		set_new_fig_box(scene, offset_origin);
	else if (key_data.key == MLX_KEY_5)
		set_new_fig_disk(scene, offset_origin);
	else if (key_data.key == MLX_KEY_6)
		set_new_fig_cylinder(scene, offset_origin);
	else if (key_data.key == MLX_KEY_7)
		set_new_fig_cone(scene, offset_origin);
	else if (key_data.key == MLX_KEY_8)
		set_new_fig_p_light(scene, offset_origin);
}

void	deselect_objects(t_object *objects, t_object *lights, bool *object_selected)
{
	while (objects)
	{
		objects->selected = false;
		objects = objects->next;
	}
	while (lights)
	{
		lights->selected = false;
		lights = lights->next;
	}
	*object_selected = false;
}

void	select_object(t_scene *scene, uint32_t x, uint32_t y)
{
	t_ray		ray;
	t_vect		pixel_offset;
	t_hit_info	hit_info;

	ray.origin = scene->camera.origin;
	pixel_offset = set_pixel(scene->camera, x, y);
	ray.dir = unit_vect(vect_subtract(pixel_offset, ray.origin));
	if (ray_hit_plus_lights(scene->objects, scene->lights, ray, &hit_info))
	{
		hit_info.object->selected = true;
		scene->object_selected = true;
	}
}

t_object	*last_object(t_object *objects)
{
	if (objects)
	{
		if (objects->next)
			return (last_object(objects->next));
	}
	return (objects);
}

int	add_object(t_object **objects, t_object *new)
{
	t_object 	*last_obj;

	if (objects)
	{
		if ((*objects))
		{
			last_obj = last_object((*objects));
			last_obj->next = new;
		}
		else
			(*objects) = new;
	}
	return (0);
}

void	init_copy(t_scene *scene, t_object *selected_obj)
{
	t_figure	fig;
	t_texture	*tx;
	t_material	mat;

	tx = NULL;
	if (selected_obj->texture)
		tx = get_texture(selected_obj->texture->path, selected_obj->texture->texture_dim);
	fig = selected_obj->figure;
	mat = selected_obj->material;
	if (selected_obj->type == SPHERE)
		init_sphere(scene, fig, mat, tx);
	else if (selected_obj->type == PLANE)
		init_plane(scene, fig, mat, tx);
	else if (selected_obj->type == QUAD)
		init_quad(scene, fig, mat, tx);
	else if (selected_obj->type == BOX)
		init_box(scene, fig, mat, tx);
	else if (selected_obj->type == DISK)
		init_disk(scene, fig, mat, tx);
	else if (selected_obj->type == CYLINDER)
		init_cylinder(scene, fig, mat, tx);
	else if (selected_obj->type == CONE)
		init_cone(scene, fig, mat, tx);
	else if (selected_obj->type == LIGHT)
		init_p_light(scene, fig, mat);
}