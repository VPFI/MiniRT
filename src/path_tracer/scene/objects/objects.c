/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:56:04 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 15:14:42 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	check_object_rotations(t_object *target_object, t_camera *camera, mlx_key_data_t key_data)
{
	t_vect	transformation;

	transformation = new_vect(0.0, 0.0, 0.0);
	if (key_data.key == MLX_KEY_W)
	{
		transformation.x -= 0.0873;
	}
	else if (key_data.key == MLX_KEY_A)
	{
		transformation.y -= 0.0873;
	}
	else if (key_data.key == MLX_KEY_S)
	{
		transformation.x += 0.0873;
	}
	else if (key_data.key == MLX_KEY_D)
	{
		transformation.y += 0.0873;
	}
	else if (key_data.key == MLX_KEY_Q)
	{
		transformation.z -= 0.0873;
	}
	else if (key_data.key == MLX_KEY_E)
	{
		transformation.z += 0.0873;
	}
	if (!zero_vect(transformation))
	{
		if (key_data.modifier == MLX_CONTROL)
		{
			transformation = vect_simple_mult(transformation, 1 / 0.0873 * M_PI / 2);
		}
		target_object->edit_orientation(target_object, camera, transformation);
		return (1);
	}
	return (0);
}


t_vect	relative_translate(t_camera *camera, mlx_key_data_t key_data)
{
	t_vect	transformation;

	transformation = new_vect(0.0, 0.0, 0.0);
	if (key_data.key == MLX_KEY_UP)
	{
		transformation = vect_simple_mult(camera->orientation, 0.1);
	}
	else if (key_data.key == MLX_KEY_DOWN)
	{
		transformation = vect_simple_mult(camera->orientation, -0.1);
	}
	else if (key_data.key == MLX_KEY_RIGHT)
	{
		transformation = vect_simple_mult(camera->u, 0.1);
	}
	else if (key_data.key == MLX_KEY_LEFT)
	{
		transformation = vect_simple_mult(camera->u, -0.1);
	}
	else if (key_data.key == MLX_KEY_LEFT_SHIFT)
	{
		transformation = vect_simple_mult(camera->v, -0.1);
	}
	else if (key_data.key == MLX_KEY_SPACE)
	{
		transformation = vect_simple_mult(camera->v, 0.1);
	}
	return (transformation);
}

t_vect	absolute_translate(mlx_key_data_t key_data)
{
	t_vect	transformation;

	transformation = new_vect(0.0, 0.0, 0.0);
	if (key_data.key == MLX_KEY_UP)
	{
		transformation = new_vect(0.0, 0.0, 0.1);
	}
	else if (key_data.key == MLX_KEY_DOWN)
	{
		transformation = new_vect(0.0, 0.0, -0.1);
	}
	else if (key_data.key == MLX_KEY_RIGHT)
	{
		transformation = new_vect(0.1, 0.0, 0.0);
	}
	else if (key_data.key == MLX_KEY_LEFT)
	{
		transformation = new_vect(-0.1, 0.0, 0.0);
	}
	else if (key_data.key == MLX_KEY_LEFT_SHIFT)
	{
		transformation = new_vect(0.0, -0.1, 0.0);
	}
	else if (key_data.key == MLX_KEY_SPACE)
	{
		transformation = new_vect(0.0, 0.1, 0.0);
	}
	return (transformation);
}

t_vect	clamp_object_coords(t_object *target_object)
{
	t_vect	transformation;
	t_vect	obj_origin;

	transformation = new_vect(0.0, 0.0, 0.0);
	obj_origin = target_object->get_origin(target_object);
	transformation.x = roundf(obj_origin.x);
	transformation.y = roundf(obj_origin.y);
	transformation.z = roundf(obj_origin.z);
	transformation = vect_subtract(transformation, obj_origin);
	return (transformation);
}

int	check_object_translations(t_object *target_object, t_camera *camera, mlx_key_data_t key_data)
{
	//Adapt object movements to camer orientation
	t_vect	transformation;

	if (key_data.key == MLX_KEY_ENTER)
		transformation = clamp_object_coords(target_object);
	else if (key_data.modifier == MLX_CONTROL)
		transformation = absolute_translate(key_data);
	else
		transformation = relative_translate(camera, key_data);
	if (!zero_vect(transformation))
	{
		target_object->edit_origin(target_object, transformation);
		return (1);
	}
	return (0);
}

int	check_object_aspect(t_object *target_object, mlx_key_data_t key_data)
{
	if (is_rgb_key_down(key_data))
	{
		if (key_data.modifier == MLX_CONTROL)
			decrement_color(target_object, key_data);
		else
			increment_color(target_object, key_data);
		print_vec_s(target_object->material.color, "NEW COLOR:");

		return (1);
	}
	else if (is_material_key_down(key_data))
	{
		if (key_data.modifier == MLX_CONTROL)
			decrement_material_component(target_object, key_data);
		else
			increment_material_component(target_object, key_data);
		printf("Material components:\n Specular: %f Roughness: %f Refraction index: %f Light intensity: %f\n\n",
			target_object->material.specular, target_object->material.metal_roughness,
			target_object->material.refraction_index, target_object->material.emission_intensity);
		return (1);		
	}
	else if (key_data.key == MLX_KEY_TAB)
	{
		cicle_material_type(target_object);
	}
	return (0);
}

int	check_object_resize(t_object *target_object, mlx_key_data_t key_data)
{
	t_vect	transformation;

	
	if (key_data.key == MLX_KEY_EQUAL)
	{
		transformation = new_vect(1.15, 1.15, 1.15);
		target_object->edit_dimensions(target_object, transformation);
		return (1);
	}
	else if (key_data.key == MLX_KEY_MINUS)
	{
		transformation = new_vect(0.85, 0.85, 0.85);
		target_object->edit_dimensions(target_object, transformation);
		return (1);
	}
	else if (key_data.key == MLX_KEY_P)
	{
		transformation = new_vect(1.15, 1.0, 1.0);
		if (key_data.modifier == MLX_CONTROL)
			transformation.x = 0.85;
		target_object->edit_dimensions(target_object, transformation);
		return (1);
	}
	else if (key_data.key == MLX_KEY_LEFT_BRACKET)
	{
		transformation = new_vect(1.0, 1.15, 1.0);
		if (key_data.modifier == MLX_CONTROL)
			transformation.y = 0.85;
		target_object->edit_dimensions(target_object, transformation);
		return (1);
	}
	else if (key_data.key == MLX_KEY_RIGHT_BRACKET)
	{
		transformation = new_vect(1.0, 1.0, 1.15);
		if (key_data.modifier == MLX_CONTROL)
			transformation.z = 0.85;
		target_object->edit_dimensions(target_object, transformation);
		return (1);
	}
	return (0);
}

int	check_object_focus(t_object *target_object, t_scene *scene, mlx_key_data_t key_data)
{
	t_vect	obj_origin;

	if (key_data.key == MLX_KEY_B)
	{
		obj_origin = target_object->get_origin(target_object);
		scene->camera.orientation = unit_vect(vect_subtract(obj_origin, scene->camera.origin));
		recalculate_view(scene);
		return (1);
	}
	return (0);
}

t_object	*get_selected_object(t_object *objects, t_object *lights)
{
	while (objects)
	{
		if (objects->selected == true)
			return(objects);
		objects = objects->next;	
	}
	while (lights)
	{
		if (lights->selected == true)
			return(lights);
		lights = lights->next;	
	}
	return (NULL);
}

void	transform_object(t_object *objects, t_object *lights, t_scene *scene, mlx_key_data_t key_data)
{
	t_object	*target_object;

	target_object = get_selected_object(objects, lights);
	if (!target_object)
		return ;
	if (is_movement_key_down(key_data) || key_data.key == MLX_KEY_ENTER)
		check_object_translations(target_object, &scene->camera, key_data);
	else if (is_rotation_key_down(key_data) || key_data.key == MLX_KEY_ENTER)
		check_object_rotations(target_object, &scene->camera, key_data);
	else if (is_aspect_key_down(key_data))
		check_object_aspect(target_object, key_data);
	else if (check_object_focus(target_object, scene, key_data))
		return ;
	else if (check_object_resize(target_object, key_data))
		return ;
	return ;
}

bool	is_2d(t_object *object)
{
	if (object->type == PLANE || object->type == QUAD || object->type == DISK)
	{
		return (true);
	}
	return (false);
}

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
