/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:26 by vperez-f          #+#    #+#             */
/*   Updated: 2024/11/13 13:44:50 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

// Xorshift || https://en.wikipedia.org/wiki/Xorshift || [0,1]
float fast_rand(uint32_t *state)
{
	uint32_t x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;
    return (x / (float)UINT32_MAX);
}

void	print_vec(t_vect vect)
{
	printf("VECT X: %f\n", vect.x);
	printf("VECT Y: %f\n", vect.y);
	printf("VECT Z: %f\n", vect.z);
}

void	safe_pixel_put_bres(t_scene *scene, uint32_t x, uint32_t y, int color)
{
	if ((x >= scene->width) || y >= scene->height)
		return ;
	mlx_put_pixel(scene->image, x, y, color);
}

void	safe_pixel_put(t_scene *scene, uint32_t x, uint32_t y, t_color color)
{
	if ((x >= scene->width) || y >= scene->height)
		return ;
	mlx_put_pixel(scene->image, x, y, get_rgba((int)(color.x * 255.9), (int)(color.y * 255.9), (int)(color.z * 255.9), 255));
}

void	test_progresive(t_scene *scene, uint32_t x, uint32_t y, t_color color, int iterations)
{
	t_vect		*prev_color_index;
	t_color		final_color;

	if ((x >= scene->width) || y >= scene->height)
		return ;
	prev_color_index = &scene->cumulative_image[((y * scene->image->width) + x)];
	prev_color_index->x += color.x;
	prev_color_index->y += color.y;
	prev_color_index->z += color.z;
	final_color = clamp_vect(vect_simple_mult(*prev_color_index, 1.0 / (float)iterations), 0.0, 1.0);
	mlx_put_pixel(scene->image, x, y, get_rgba(
		(int)(final_color.x * 255.9),
		(int)(final_color.y * 255.9),
		(int)(final_color.z * 255.9),
		255));
}

void	close_all(t_scene *scene)
{
	mlx_close_window(scene->mlx);
}

void	move_menu(t_scene *scene, keys_t key)
{
	if (key == MLX_KEY_UP)
	{
		if (scene->current_file > 0 && scene->buttons[scene->current_file - 1].text)
			scene->current_file--;
	}
	else if (key == MLX_KEY_DOWN)
	{
		if (scene->current_file < 20 && scene->buttons[scene->current_file + 1].text) 
			scene->current_file++;
	}
	else if (key == MLX_KEY_LEFT)
	{
		if (scene->current_file >= 10 && scene->buttons[scene->current_file - 10].text)
			scene->current_file -= 10;
	}
	else if (key == MLX_KEY_RIGHT)
	{
		if (scene->current_file < 10 && scene->buttons[scene->current_file + 10].text)
			scene->current_file += 10;
	}
	draw_buttons(scene->buttons, scene);
}

int		is_arrow_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_UP || key_data.key == MLX_KEY_DOWN
		|| key_data.key == MLX_KEY_LEFT || key_data.key == MLX_KEY_RIGHT)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
	{
		return (1);
	}
	return (0);
}

int		is_wasd_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_S
		|| key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_D)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
	{
		return (1);
	}
	return (0);
}

int		is_extra_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_LEFT_SHIFT
		|| key_data.key == MLX_KEY_SPACE
		|| key_data.key == MLX_KEY_F
		|| key_data.key == MLX_KEY_G
		|| key_data.key == MLX_KEY_V
		|| key_data.key == MLX_KEY_T
		|| key_data.key == MLX_KEY_Q
		|| key_data.key == MLX_KEY_E
		|| key_data.key == MLX_KEY_O
		|| key_data.key == MLX_KEY_Z
		|| key_data.key == MLX_KEY_X
		|| key_data.key == MLX_KEY_C
		|| key_data.key == MLX_KEY_B
		|| key_data.key == MLX_KEY_H
		|| key_data.key == MLX_KEY_J
		|| key_data.key == MLX_KEY_K
		|| key_data.key == MLX_KEY_L
		|| key_data.key == MLX_KEY_EQUAL
		|| key_data.key == MLX_KEY_MINUS
		|| key_data.key == MLX_KEY_TAB)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
	{
		return (1);
	}
	return (0);
}

int		is_camera_key_down(mlx_key_data_t key_data)
{
	if (is_arrow_key_down(key_data)
		|| is_wasd_key_down(key_data)
		|| is_extra_key_down(key_data))
	{
		return (1);
	}
	return (0);
}

int	is_material_key_down(mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_H
		|| key_data.key == MLX_KEY_J
		|| key_data.key == MLX_KEY_K
		|| key_data.key == MLX_KEY_L)
	{
		return (1);
	}
	return (0);
}

int	is_rgb_key_down(mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_Z
		|| key_data.key == MLX_KEY_X
		|| key_data.key == MLX_KEY_C)
	{
		return (1);
	}
	return (0);
}

int	is_num_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_1
		|| key_data.key == MLX_KEY_2
		|| key_data.key == MLX_KEY_3
		|| key_data.key == MLX_KEY_4
		|| key_data.key == MLX_KEY_5
		|| key_data.key == MLX_KEY_BACKSPACE)
		&& (key_data.action == MLX_PRESS))
	{
		return (1);
	}
	return (0);
}

int	is_scene_settings_key_down(mlx_key_data_t key_data)
{
		if ((key_data.key == MLX_KEY_COMMA
			|| key_data.key == MLX_KEY_PERIOD)
			&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
	{
		return (1);
	}
	return (0);	
}

int	is_press_and_ctrl(mlx_key_data_t key_data)
{
	if (key_data.action == MLX_PRESS && key_data.modifier == MLX_CONTROL)
		return (1);
	return (0);
}

int	check_rotations(t_camera *camera, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_W)
	{
		camera->orientation.y += 0.1;
		print_vec(unit_vect(camera->orientation));
		return (1);
	}
	else if (key_data.key == MLX_KEY_A)
	{
		camera->orientation.x -= 0.1;
		print_vec(unit_vect(camera->orientation));
		return (1);
	}
	else if (key_data.key == MLX_KEY_S)
	{
		camera->orientation.y -= 0.1;
		print_vec(unit_vect(camera->orientation));
		return (1);
	}
	else if (key_data.key == MLX_KEY_D)
	{
		camera->orientation.x += 0.1;
		print_vec(unit_vect(camera->orientation));
		return (1);
	}
	else if (key_data.key == MLX_KEY_Q)
	{
		camera->orientation.z -= 0.1;
		print_vec(unit_vect(camera->orientation));
		return (1);
	}
	else if (key_data.key == MLX_KEY_E)
	{
		camera->orientation.z += 0.1;
		print_vec(unit_vect(camera->orientation));
		return (1);
	}
	return (0);
}

int	check_translations(t_camera *camera, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_UP)
	{
		camera->origin = vect_add(camera->origin, vect_simple_mult(camera->orientation, 0.5));
		return (1);
	}
	else if (key_data.key == MLX_KEY_DOWN)
	{
		camera->origin = vect_subtract(camera->origin, vect_simple_mult(camera->orientation, 0.5));
		return (1);
	}
	else if (key_data.key == MLX_KEY_RIGHT)
	{
		camera->origin = vect_add(camera->origin, vect_simple_mult(camera->u, 0.5));
		return (1);
	}
	else if (key_data.key == MLX_KEY_LEFT)
	{
		camera->origin = vect_subtract(camera->origin, vect_simple_mult(camera->u, 0.5));
		return (1);
	}
	else if (key_data.key == MLX_KEY_SPACE)
	{
		camera->origin.y += 0.5;
		return (1);
	}
	else if (key_data.key == MLX_KEY_LEFT_SHIFT)
	{
		camera->origin.y -= 0.5;
		return (1);
	}
	return (0);
}

int	check_settings(t_camera *camera, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_F)
	{
		if (key_data.modifier == MLX_CONTROL)
		{
			camera->fov -= 1;
			if (camera->fov < 0)
				camera->fov = 0;
		}
		else
			camera->fov += 1;
		printf("FOV: %f\n", camera->fov);
		return (1);
	}
	else if (key_data.key == MLX_KEY_G)
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
		return (1);
	}
	else if (key_data.key == MLX_KEY_V)
	{
		if (key_data.modifier == MLX_CONTROL)
		{
			camera->focus_dist -= 0.5;
			if (camera->focus_dist < 0)
				camera->focus_dist = 0.1;
		}
		else
			camera->focus_dist += 0.5;
		printf("FOCUS DIST: %f\n", camera->focus_dist);
		return (1);
	}
	return (0);
}

int	check_reset(t_camera *camera, t_camera *backup, mlx_key_data_t key_data)
{

	if (key_data.key == MLX_KEY_O)
	{
		camera->origin = new_vect(0.0, 0.5, 0.0);
		camera->orientation = new_vect(0.0, 0.0, -1.0);
		return (1);
	}
	else if (key_data.key == MLX_KEY_T)
	{
		*camera = *backup;
		return (1);
	}
	return (0);
}

void	move_camera(t_camera *camera, t_camera *backup, mlx_key_data_t key_data)
{
	//control for infinite moving overflows etc....
	if (check_reset(camera, backup, key_data))
		return ;
	else if (check_rotations(camera, key_data))
		return ;
	else if (check_translations(camera, key_data))
		return ;
	else if (check_settings(camera, key_data))
		return ;
	return ;
}

int	check_object_rotations(t_object *target_object, mlx_key_data_t key_data)
{
	//Adapt object movements to camer orientation
	t_vect	transformation;

	transformation = new_vect(0.0, 0.0, 0.0);
	if (key_data.key == MLX_KEY_W)
	{
		transformation.y += 0.1;
	}
	else if (key_data.key == MLX_KEY_A)
	{
		transformation.x -= 0.1;
	}
	else if (key_data.key == MLX_KEY_S)
	{
		transformation.y -= 0.1;
	}
	else if (key_data.key == MLX_KEY_D)
	{
		transformation.x += 0.1;
	}
	else if (key_data.key == MLX_KEY_Q)
	{
		transformation.z -= 0.1;
	}
	else if (key_data.key == MLX_KEY_E)
	{
		transformation.z += 0.1;
	}
	if (!zero_vect(transformation))
	{
		target_object->edit_orientation(target_object, transformation);
		return (1);
	}
	return (0);
}

int	check_object_translations(t_object *target_object, mlx_key_data_t key_data)
{
	//Adapt object movements to camer orientation
	t_vect	transformation;

	transformation = new_vect(0.0, 0.0, 0.0);
	if (key_data.key == MLX_KEY_UP)
	{
		transformation.z += 0.25;
	}
	else if (key_data.key == MLX_KEY_DOWN)
	{
		transformation.z -= 0.25;
	}
	else if (key_data.key == MLX_KEY_RIGHT)
	{
		transformation.x += 0.25;
	}
	else if (key_data.key == MLX_KEY_LEFT)
	{
		transformation.x -= 0.25;
	}
	else if (key_data.key == MLX_KEY_SPACE)
	{
		transformation.y += 0.25;
	}
	else if (key_data.key == MLX_KEY_LEFT_SHIFT)
	{
		transformation.y -= 0.25;
	}
	if (!zero_vect(transformation))
	{
		target_object->edit_origin(target_object, transformation);
		return (1);
	}
	return (0);
}

void	increment_material_component(t_object *target_object, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_H)
	{
		target_object->material.specular += 0.05;
		if (target_object->material.specular > 1.0)
			target_object->material.specular = 1.0;
	}
	else if (key_data.key == MLX_KEY_J)
	{
		target_object->material.metal_roughness += 0.05;
		if (target_object->material.metal_roughness > 1.0)
			target_object->material.metal_roughness = 1.0;
	}
	else if (key_data.key == MLX_KEY_K)
	{
		target_object->material.refraction_index += 0.05;
		if (target_object->material.refraction_index > 10.0)
			target_object->material.refraction_index = 10.0;
	}
	else if (key_data.key == MLX_KEY_L)
	{
		target_object->material.emission_intensity += 0.05;
		if (target_object->material.emission_intensity > 100.0)
			target_object->material.emission_intensity = 100.0;
	}
	return ;
}

void	decrement_material_component(t_object *target_object, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_H)
	{
		target_object->material.specular -= 0.05;
		if (target_object->material.specular < 0.0)
			target_object->material.specular = 0.0;
	}
	else if (key_data.key == MLX_KEY_J)
	{
		target_object->material.metal_roughness -= 0.05;
		if (target_object->material.metal_roughness < 0.0)
			target_object->material.metal_roughness = 0.0;
	}
	else if (key_data.key == MLX_KEY_K)
	{
		target_object->material.refraction_index -= 0.05;
		if (target_object->material.refraction_index < 0.0)
			target_object->material.refraction_index = 0.0;
	}
	else if (key_data.key == MLX_KEY_L)
	{
		target_object->material.emission_intensity -= 0.05;
		if (target_object->material.emission_intensity < 0.0)
			target_object->material.emission_intensity = 0.0;
	}
	return ;
}

void	increment_color(t_object *target_object, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_Z)
	{
		target_object->material.color.x += 0.05;
		if (target_object->material.color.x > 1.0)
			target_object->material.color.x = 1.0;
	}
	else if (key_data.key == MLX_KEY_X)
	{
		target_object->material.color.y += 0.05;
		if (target_object->material.color.y > 1.0)
			target_object->material.color.y = 1.0;
	}
	else if (key_data.key == MLX_KEY_C)
	{
		target_object->material.color.z += 0.05;
		if (target_object->material.color.z > 1.0)
			target_object->material.color.z = 1.0;
	}
	return ;
}

void	decrement_color(t_object *target_object, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_Z)
	{
		target_object->material.color.x -= 0.05;
		if (target_object->material.color.x < 0.0)
			target_object->material.color.x = 0.0;
	}
	else if (key_data.key == MLX_KEY_X)
	{
		target_object->material.color.y -= 0.05;
		if (target_object->material.color.y < 0.0)
			target_object->material.color.y = 0.0;
	}
	else if (key_data.key == MLX_KEY_C)
	{
		target_object->material.color.z -= 0.05;
		if (target_object->material.color.z < 0.0)
			target_object->material.color.z = 0.0;
	}
	return ;
}

void	cicle_material_type(t_object *target_object)
{
	target_object->material.type = (target_object->material.type + 1) % 5;
	return ;
}

int	check_object_aspect(t_object *target_object, mlx_key_data_t key_data)
{
	if (is_rgb_key_down(key_data))
	{
		if (key_data.modifier == MLX_CONTROL)
			decrement_color(target_object, key_data);
		else
			increment_color(target_object, key_data);
		return (1);
	}
	else if (is_material_key_down(key_data))
	{
		if (key_data.modifier == MLX_CONTROL)
			decrement_material_component(target_object, key_data);
		else
			increment_material_component(target_object, key_data);
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

	transformation = new_vect(0.0, 0.0, 0.0);
	if (key_data.key == MLX_KEY_EQUAL)
	{
		transformation.x = 1.15;
		target_object->edit_dimensions(target_object, transformation);
		return (1);
	}
	else if (key_data.key == MLX_KEY_MINUS)
	{
		transformation.x = 0.85;
		target_object->edit_dimensions(target_object, transformation);
		return (1);
	}
	return (0);
}

int	check_object_focus(t_object *target_object, t_camera *camera, mlx_key_data_t key_data)
{
	//Adapt object movements to camer orientation
	t_vect	obj_origin;

	if (key_data.key == MLX_KEY_B)
	{
		obj_origin = target_object->get_origin(target_object);
		camera->orientation = unit_vect(vect_subtract(obj_origin, camera->origin));
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

void	transform_object(t_object *objects, t_object *lights, t_camera *camera, mlx_key_data_t key_data)
{
	//control for infinite moving overflows etc....
	//reset for objects? just duplicate the init object list like lights etc...
	t_object	*target_object;

	target_object = get_selected_object(objects, lights);
	if (!target_object)
		return ;
	if (check_object_translations(target_object, key_data))
		return ;
	else if (check_object_rotations(target_object, key_data))
		return ;
	else if (check_object_aspect(target_object, key_data))
		return ;
	else if (check_object_resize(target_object, key_data))
		return ;
	else if (check_object_focus(target_object, camera, key_data))
		return ;
	return ;
}

void	change_scene_settings(t_scene *scene, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_COMMA)
	{
		scene->amb_light -= 0.05;
		if (scene->amb_light < 0.0)
			scene->amb_light = 0.0;
	}
	else if (key_data.key == MLX_KEY_PERIOD)
		scene->amb_light += 0.05;
	return ;
}

t_material	new_standard_material(void)
{
	t_material	mat;
	uint32_t	state;

	state = (uint32_t)(mlx_get_time() * 10000);
	mat.color = new_color(fast_rand(&state), fast_rand(&state), fast_rand(&state));
	mat.albedo = mat.color;
	mat.specular = 0.2;
	mat.metal_roughness = 0.0;
	mat.refraction_index = 1.5;
	mat.emission_intensity = 0.0;
	mat.type = LAMBERTIAN;
	return (mat);
}

t_material	new_standard_plight(void)
{
	t_material	mat;
	uint32_t	state;

	state = (uint32_t)(mlx_get_time() * 10000);
	mat.color = new_color(fast_rand(&state), fast_rand(&state), fast_rand(&state));
	mat.albedo = mat.color;
	mat.specular = 0.2;
	mat.metal_roughness = 0.0;
	mat.refraction_index = 1.5;
	mat.emission_intensity = 1.5;
	mat.type = EMISSIVE;
	return (mat);
}

void	add_world_object(t_scene *scene, mlx_key_data_t key_data)
{
	//Adapt object movements to camer orientation
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	if (key_data.key == MLX_KEY_1)
	{
		fig.sphere.center = new_vect(0.0, 0.0, -1.0);
		fig.sphere.radius = 1.0;
		init_object(scene, fig, mat, SPHERE);
	}
	else if (key_data.key == MLX_KEY_2)
	{
		fig.plane.center = new_vect(0.0, 0.0, -1.0);
		fig.plane.normal = new_vect(0.0, 0.0, 1.0);
		init_object(scene, fig, mat, PLANE);
	}
	else if (key_data.key == MLX_KEY_3)
	{
		fig.quad.origin = new_vect(0.0, 0.0, -1.0);
		fig.quad.u_vect = new_vect(2.0, 0.0, 0.0);
		fig.quad.v_vect = new_vect(0.0, 2.0, 0.0);
		init_object(scene, fig, mat, QUAD);
	}
	else if (key_data.key == MLX_KEY_4)
	{
		fig.disk.center = new_vect(0.0, 0.0, -1.0);
		fig.disk.normal = new_vect(0.0, 0.0, 1.0);
		fig.disk.radius = 1.0;
		init_object(scene, fig, mat, DISK);
	}
	else if (key_data.key == MLX_KEY_5)
	{
		fig.p_light.location = new_vect(0.0, 1.0, -1.0);
		mat = new_standard_plight();
		init_object(scene, fig, mat, LIGHT);
	}
	return ;
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
		free(obj);
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

void	write_ppm(mlx_image_t *image, int fd, char *filename)
{
	uint32_t	x;
	uint32_t	y;
	uint8_t		*pixel;

	y = 0;
	pixel = NULL;
	ft_printf(STDOUT_FILENO, "\n\nExporting %i x %i image\n", image->width, image->height);
	ft_printf(fd, "P3\n");
	ft_printf(fd, "%i %i\n", image->width, image->height);
	ft_printf(fd, "255\n");
	while (y < image->height)
	{
		x = 0;
		pixel = &image->pixels[((y * image->width)) * sizeof(uint32_t)];
		while (x < image->width)
		{
			ft_printf(fd, "%i %i %i", *(pixel), *(pixel + 1), *(pixel + 2));
			x++;
			pixel = pixel + sizeof(uint32_t);
			if (x < image->width)
				ft_printf(fd, "  ");
		}
		ft_printf(fd, "\n");
		y++;
		ft_printf(STDERR_FILENO, "--| %i%% |--\r", (int)((y / (float)image->height) * 100));
	}
	ft_printf(STDOUT_FILENO, "Image exported succesfully to \"%s\"\n\n", filename);
}

int	export_to_ppm(mlx_image_t *image)
{
	int		fd;
	char	*filename;

	fd = 0;
	filename = ft_itoa((int)(mlx_get_time() * mlx_get_time() * 1000));
	filename = ft_strattach("img/exported/", &filename);
	filename = ft_strappend(&filename, ".ppm");
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		if (access(filename, F_OK))
			ft_printf(STDERR_FILENO, ERR_NOFILE_MSG);
		else if (access(filename, R_OK))
			ft_printf(STDERR_FILENO, ERR_PERM_MSG);
		else
			ft_printf(STDERR_FILENO, ERR_STD_MSG);
		free(filename);
		return (1);
	}
	write_ppm(image, fd, filename);
	close(fd);
	free(filename);
	return (0);
}

void	edit_mode_hooks(t_scene *scene, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_R && is_press_and_ctrl(key_data))
	{
		scene->stop = true;
		wait_for_threads(scene);
		scene->stop = false;
		scene->edit_mode = false;
		deselect_objects(scene->objects, scene->lights, &scene->object_selected);
		main_loop(scene);
	}
	else if (is_num_key_down(key_data))
	{
		scene->stop = true;
		wait_for_threads(scene);
		scene->stop = false;
		if (key_data.key == MLX_KEY_BACKSPACE && scene->object_selected)
			delete_world_object(scene);
		else
			add_world_object(scene, key_data);
		main_loop(scene);
	}
	else if (is_camera_key_down(key_data))
	{
		scene->stop = true;
		wait_for_threads(scene);
		scene->stop = false;
		if (scene->object_selected)
			transform_object(scene->objects, scene->lights, &scene->camera, key_data);
		else
			move_camera(&scene->camera, &scene->back_up_camera, key_data);
		recalculate_view(scene);
		main_loop(scene);
	}
	else if (is_scene_settings_key_down(key_data))
	{
		scene->stop = true;
		wait_for_threads(scene);
		scene->stop = false;
		change_scene_settings(scene, key_data);
		main_loop(scene);
	}
}

void	render_mode_hooks(t_scene *scene, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_X && is_press_and_ctrl(key_data))
	{
		scene->stop = true;
		wait_for_threads(scene);
		scene->do_backup = true;
		scene->stop = false;
		if (export_to_ppm(scene->image))
			ft_printf(STDERR_FILENO, "Unexpected error exporting image |--> Resuming render\n");
		main_loop(scene);
	}
	else if (key_data.key == MLX_KEY_E && is_press_and_ctrl(key_data))
	{
		scene->stop = true;
		wait_for_threads(scene);
		scene->stop = false;
		scene->edit_mode = true;
		ft_memset(scene->cumulative_image, 0, sizeof(t_vect) * scene->height * scene->width);
		main_loop(scene);
	}
}

void	key_down(mlx_key_data_t key_data, void *sc)
{
	t_scene	*scene;

	scene = sc;
	// agrupate scene stop | wait threads | scene stop  |+| specific functionality
	// make controls based on fov or other dynamic way?
	if (key_data.key == MLX_KEY_ESCAPE && key_data.action == MLX_PRESS)
	{
		set_stop_status(scene);
		close_all(scene);
	}
	else if (!scene->choose_file && is_arrow_key_down(key_data))
		move_menu(scene, key_data.key);
	else if (!scene->choose_file && (key_data.key == MLX_KEY_ENTER && key_data.action == MLX_PRESS))
	{
		scene->choose_file = 1;
		set_new_image(scene);
		mlx_image_to_window(scene->mlx, scene->image, 0 ,0);
		printf("YOU CHOSE %s.rt\n", scene->buttons[scene->current_file].text);
	}
	else if (scene->edit_mode == false)
		render_mode_hooks(scene, key_data);
	else if (scene->edit_mode == true)
		edit_mode_hooks(scene, key_data);
}

t_vect	set_pixel_offset(t_camera camera, uint32_t x, uint32_t y, uint32_t *state)
{
	t_vect	res;
	t_vect	aux1;
	t_vect	aux2;

	aux1 = vect_simple_mult(camera.pixel_delta_h, (x + (fast_rand(state) - 0.5)));
	aux2 = vect_simple_mult(camera.pixel_delta_v, (y + (fast_rand(state) - 0.5)));
	res = vect_add(aux1, aux2);
	res = vect_add(res, camera.viewport_pixel0);
	return (res);
}

t_vect	set_pixel(t_camera camera, uint32_t x, uint32_t y)
{
	t_vect	res;
	t_vect	aux1;
	t_vect	aux2;

	aux1 = vect_simple_mult(camera.pixel_delta_h, x);
	aux2 = vect_simple_mult(camera.pixel_delta_v, y);
	res = vect_add(aux1, aux2);
	res = vect_add(res, camera.viewport_pixel0);
	return (res);
}

bool	shadow_hit(t_scene *scene, t_ray ray, t_hit_info *hit_info, float max)
{
	t_object	*temp;
	float		bounds[2];
	bool		hit;

	hit = false;
	bounds[MIN] = 0.001;
	bounds[MAX] = __FLT_MAX__;
	if (max)
	{
		bounds[MAX] = max;
	}
	ray.dir = unit_vect(ray.dir);
	temp = scene->objects;
	while (temp)
	{
		if (temp->hit_func(ray, temp->figure, hit_info, bounds))
		{
			hit = true;
			bounds[MAX] = hit_info->t;
			hit_info->object = temp;
			break ;
		}
		temp = temp->next;
	}
	return (hit);
}

bool	ray_hit(t_object *objects, t_ray ray, t_hit_info *hit_info)
{
	float		bounds[2];
	bool		hit;

	hit = false;
	bounds[MIN] = 0.001;
	bounds[MAX] = __FLT_MAX__;
	while (objects)
	{
		if (objects->hit_func(ray, objects->figure, hit_info, bounds))
		{
			hit = true;
			bounds[MAX] = hit_info->t;
			hit_info->object = objects;
		}
		objects = objects->next;
	}
	return (hit);
}

bool	ray_hit_plus_lights(t_object *objects, t_object *plights, t_ray ray, t_hit_info *hit_info)
{
	float		bounds[2];
	bool		hit;

	hit = false;
	bounds[MIN] = 0.001;
	bounds[MAX] = __FLT_MAX__;
	while (objects)
	{
		if (objects->hit_func(ray, objects->figure, hit_info, bounds))
		{
			hit = true;
			bounds[MAX] = hit_info->t;
			hit_info->object = objects;
		}
		objects = objects->next;
	}
	while (plights)
	{
		if (plights->hit_func(ray, plights->figure, hit_info, bounds))
		{
			hit = true;
			bounds[MAX] = hit_info->t;
			hit_info->object = plights;
		}
		plights = plights->next;
	}
	return (hit);
}

t_color	calc_pixel_color_normal(t_scene *scene, t_ray ray)
{
	t_color		color;
	t_hit_info	hit_info;

	if (ray_hit_plus_lights(scene->objects, scene->lights, ray, &hit_info))
	{
		if (hit_info.object->selected)
			color = hexa_to_vect(WHITE);
		else if (hit_info.object->type == LIGHT)
			color = hit_info.object->material.color;
		else	
			color = new_color(((hit_info.normal.x + 1) * 0.5), ((hit_info.normal.y + 1) * 0.5), ((hit_info.normal.z + 1) * 0.5));
	}
	else
	{
		color = vect_simple_mult(hexa_to_vect(SILVER), scene->amb_light);
	}
	return (color);
}

t_vect	get_random_uvect_alt(uint32_t *state)
{
	t_vect	res;
	float	a;
	float	r;

	a = fast_rand(state) * 2.0 * M_PI;
	res.z = (fast_rand(state) * 2.0) - 1.0;
	r = sqrtf(1.0 - (res.z * res.z));
	res.x = r * cosf(a);
	res.y = r * sinf(a);
	return (res);
}

t_vect	get_random_uvect(uint32_t *state)
{
	t_vect	res;
	float	bound;

	while (1)
	{
		res.x = (fast_rand(state) - 0.5) * 2;
		res.y = (fast_rand(state) - 0.5) * 2;
		res.z = (fast_rand(state) - 0.5) * 2;
		bound = vect_dot(res, res);
		if ( 1e-40 < bound && bound <= 1)
		{
			res = vect_simple_div(res, sqrtf(bound));
			return (res);
		}
	}
}

float	test_specular(t_hit_info hit_info, t_ray inc_ray, t_vect cam_orientation)
{
	t_vect		bounce_dir;
	float		test;

	inc_ray.dir = unit_vect(inc_ray.dir);
	bounce_dir = vect_subtract(inc_ray.dir, vect_simple_mult(hit_info.normal, 2 * vect_dot(inc_ray.dir, hit_info.normal)));
	test = vect_dot(unit_vect(bounce_dir), cam_orientation);
	if (test < 0)
		test = 0;
	test = pow(test, 256);
	return (test);
}

t_color	light_sampling(t_thread *thread, t_hit_info hit_info)
{
	t_ray		shadow_ray;
	t_hit_info	test_hit;
	float		mod;
	float		mod2;
	t_object	*temp;
	t_color 	emittance;
	float		tot_intensity;

	tot_intensity = 0;
	emittance = new_color(0.0, 0.0, 0.0);
	temp = thread->scene->lights;
	while (temp)
	{
		if (temp->type != LIGHT)
		{
			temp = temp->next;
			continue ;
		}
		shadow_ray.origin = hit_info.point;
		shadow_ray.dir = vect_subtract(temp->figure.p_light.location, hit_info.point);
		if (!shadow_hit(thread->scene, shadow_ray, &test_hit, sqrtf(vect_dot(shadow_ray.dir, shadow_ray.dir))))
		{
			mod2 = 1 / sqrtf(vect_dot(shadow_ray.dir, shadow_ray.dir));
			if (hit_info.object->material.type == LAMBERTIAN)
			{
				mod = vect_dot(hit_info.normal, unit_vect(shadow_ray.dir));
				if (mod < 0)
					mod = 0;
				emittance = vect_add(emittance, vect_simple_mult(temp->material.color, (temp->material.emission_intensity * mod * mod2)));
			}
			else
				emittance = vect_add(emittance, vect_simple_mult(temp->material.color, (test_specular(hit_info, shadow_ray, thread->scene->camera.orientation) * temp->material.emission_intensity) * mod2 * 10));
		}
		tot_intensity += temp->material.emission_intensity;
		temp = temp->next;
	}
	//refactor intensity especially for 1 light
	//if (tot_intensity)
		//emittance = vect_simple_div(emittance, tot_intensity);

	return (emittance);	
}

t_ray	metal_scatter(uint32_t *state, t_hit_info hit_info, t_ray inc_ray, t_color *emittance, t_thread *thread)
{
	t_vect		bounce_dir;
	t_ray		bounce_ray;

	bounce_dir = vect_subtract(inc_ray.dir, vect_simple_mult(hit_info.normal, 2 * vect_dot(inc_ray.dir, hit_info.normal)));
	if (hit_info.object->material.metal_roughness)
		bounce_dir = vect_add(unit_vect(bounce_dir), vect_simple_mult(get_random_uvect(state), powf(hit_info.object->material.metal_roughness, 2)));
	bounce_ray = new_ray(bounce_dir, hit_info.point);
	hit_info.object->material.albedo = hit_info.object->material.color;
	*emittance = light_sampling(thread, hit_info);
	return (bounce_ray);
}

t_ray	lambertian_scatter(uint32_t *state, t_hit_info hit_info, t_color *emittance, t_thread *thread)
{
	t_vect		bounce_dir;
	t_vect		target_on_sphere;
	t_ray		bounce_ray;

	bounce_dir = get_random_uvect(state);
	target_on_sphere = vect_add(bounce_dir, hit_info.normal);
	if (zero_vect(bounce_dir))
		target_on_sphere = hit_info.normal;
	target_on_sphere = vect_add(target_on_sphere, hit_info.point); // = target_onsphere + hit.info.point
	bounce_ray = new_ray(unit_vect(vect_subtract(target_on_sphere, hit_info.point)), hit_info.point);
	hit_info.object->material.albedo = hit_info.object->material.color;
	*emittance = light_sampling(thread, hit_info);
	return (bounce_ray);
}

//Schlick's approximation || R0 = R0 + (1 - R0)(1 - cos0)^5 || R0 = (n1 - n2) / (n1 + n2)
float	reflectance(float index, float cos)
{
	float	r;
	float	res;

	r = (1 - index) / (1 + index);
	r = r * r;
	res = r + (1 - r) * powf((1 - cos), 5);
	return (res);
}

// η⋅sinθ=η′⋅sinθ′
t_ray	refract(t_hit_info hit_info, t_vect udir, float index, float cos)
{
	t_vect	perp;
	t_vect	parallel;
	t_ray	res;

	perp = vect_simple_mult(vect_add(udir, vect_simple_mult(hit_info.normal, cos)), index);
	parallel = vect_simple_mult(hit_info.normal, sqrtf(fabs(1.0 - vect_dot(perp, perp))) * -1.0);
	res = new_ray(vect_add(perp, parallel), hit_info.point);
	return (res);
}

t_ray	dielectric_scatter(uint32_t *state, t_hit_info hit_info, t_ray inc_ray, t_color *emittance, t_thread *thread)
{
	//check face vect_dot etc...
	t_ray		bounce_ray;
	bool		front_face;
	t_vect		udir;
	float		index;
	float		cos;
	float		sin;
	t_hit_info	adj_hit;

	adj_hit = hit_info;
	udir = unit_vect(inc_ray.dir);
	index = hit_info.object->material.refraction_index;
	front_face = vect_dot(hit_info.normal, udir) <= 0.0;
	if (front_face)
		index = AIR_REF_INDEX / index;
	else
		adj_hit.normal = vect_simple_mult(hit_info.normal, -1); //if not inverted + normal in point inception material
	cos = fminf(vect_dot(vect_simple_mult(udir, -1.0), adj_hit.normal), 1.0);
	sin = sqrtf(1.0 - (cos * cos));
	if (((index * sin) > 1.0) || (reflectance(index, cos) > fast_rand(state)))
		bounce_ray = metal_scatter(state, adj_hit, inc_ray, emittance, thread);
	else
	{
		bounce_ray = refract(adj_hit, udir, index, cos);
		if (hit_info.object->material.metal_roughness)
			bounce_ray.dir = vect_add(unit_vect(bounce_ray.dir), vect_simple_mult(get_random_uvect(state), powf(hit_info.object->material.metal_roughness, 2)));
	}
	hit_info.object->material.albedo = hit_info.object->material.color;
	return (bounce_ray);
}

bool	scatter_ray(t_thread *thread, t_hit_info hit_info, t_ray *bounce_ray, t_ray ray, t_color *emittance)
{
	//change emmitance in-funciton etc...
	//tweak intensity || light sampling etc...
	if (hit_info.object->material.type == LAMBERTIAN)
	{
		//refactor wiht 1/pi etc...
		(*bounce_ray) = lambertian_scatter(thread->state, hit_info, emittance, thread);
		return(true);
	}
	else if (hit_info.object->material.type == METAL)
	{
		(*bounce_ray) = metal_scatter(thread->state, hit_info, ray, emittance, thread);
		//refine for roughness
		if (vect_dot((*bounce_ray).dir, hit_info.normal) <= 0)
			return (false);
	}
	else if (hit_info.object->material.type == DIELECTRIC)
	{
		(*bounce_ray) = dielectric_scatter(thread->state, hit_info, ray, emittance, thread);
		return (true);
	}
	else if (hit_info.object->material.type == GLOSSY)
	{
		float	cos = fminf(vect_dot(vect_simple_mult(ray.dir, -1.0), hit_info.normal), 1.0);
		if (hit_info.object->material.specular > fast_rand(thread->state) || reflectance(1.5, cos) > fast_rand(thread->state))
		{
			(*bounce_ray) = metal_scatter(thread->state, hit_info, ray, emittance, thread);
			if (vect_dot((*bounce_ray).dir, hit_info.normal) <= 0)
				return (false);
			hit_info.object->material.albedo = new_color(1.0, 1.0, 1.0);
			return (true);
		}
		else
		{
			(*bounce_ray) = lambertian_scatter(thread->state, hit_info, emittance, thread);
			return(true);
		}
	}
	return (true);
}

t_color	calc_pixel_color(t_thread *thread, t_ray ray, int depth)
{
	t_color		emittance;
	t_color		background;
	float		time_aux;
	float		mod;
	t_hit_info	hit_info;
	t_ray		bounce_ray;

	if (depth <= 0)
		return (new_color(0, 0, 0));
	ft_bzero(&hit_info, sizeof(hit_info));
	emittance = new_color(0, 0, 0);
	time_aux = mlx_get_time();
	if (ray_hit(thread->scene->objects, ray, &hit_info))
	{
		thread->time_hit += mlx_get_time() - time_aux;
		if (hit_info.object->material.type == EMISSIVE)
		{
			emittance = vect_simple_mult(hit_info.object->material.color, hit_info.object->material.emission_intensity);
			return (emittance);
		}
		if (!scatter_ray(thread, hit_info, &bounce_ray, ray, &emittance))
		{
			return (emittance);
		}
		return (vect_add(vect_mult(calc_pixel_color(thread, bounce_ray, depth - 1), hit_info.object->material.albedo), emittance));
	}
	thread->time_hit += mlx_get_time() - time_aux;
	t_vect	unit_dir = unit_vect(ray.dir);
	mod = 0.5 * (unit_dir.y + 1.0);
	background = vect_add(vect_simple_mult(new_color(1, 1, 1), (1.0 - mod)), vect_simple_mult(new_color(0.3, 0.7, 1), mod));
	if (AMB)
		background = hexa_to_vect(AMB_COLOR);
	background = vect_simple_mult(background, thread->scene->amb_light);
	return (background);
}

void	set_thread_backup(t_thread *thread, t_thread_backup *back_up)
{
	thread->current_y = back_up->current_y;
	thread->iterations = back_up->iterations;
}

void	set_thread_default(t_thread *thread)
{
	thread->current_y = 0;
	thread->iterations = 1;
}

void	set_thread(t_thread *thread, t_thread_backup *back_up, bool do_backup)
{
	if (do_backup)
	{
		set_thread_backup(thread, back_up);
	}
	else
	{
		set_thread_default(thread);		
	}
	thread->y_start = 0;
	thread->y_end = thread->scene->height;
	thread->current_x = 0;
	thread->x_start = thread->id;
	thread->x_end = thread->scene->width;
	thread->x_increment = THREADS;
	thread->pix_rendered = 0;
	thread->time_hit = 0;
	thread->state = malloc(sizeof(uint32_t));
	if (!thread->state)
	{
		exit (205);
	}
	*(thread->state) = mlx_get_time() * (thread->id + 1) * 123456;
	//printf("%i -- %i -- %i -- %i\n", thread->y_start, thread->y_end, thread->x_start, thread->x_end);
}

void	init_render(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		scene->threads[i].id = i;
		scene->threads[i].scene = scene;
		set_thread(&scene->threads[i], &scene->threads_backup[i], scene->do_backup);
		if (pthread_create(&scene->threads[i].self, NULL, &set_rendering, (void *)&scene->threads[i]))
			exit (201);
		i++;
	}
	if (scene->do_backup)
	{
		scene->do_backup = false;
		ft_memset(scene->threads_backup, 0, sizeof(t_thread_backup) * THREADS);
	}
}

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

void	edit_mode(t_thread *thread, uint32_t x, uint32_t y)
{
	t_ray		ray;
	t_vect		pixel_offset;
	t_color		color;

	ray.origin = defocus_sample(thread->scene->camera, thread->state);
	pixel_offset = set_pixel(thread->scene->camera, x, y);
	ray.dir = unit_vect(vect_subtract(pixel_offset, ray.origin));
	color = calc_pixel_color_normal(thread->scene, ray);
	color = clamp_vect(color, 0.0, 1.0);
	safe_pixel_put(thread->scene, x, y, color);
}

void	render_mode(t_thread *thread, uint32_t x, uint32_t y)
{
	int			sample_count;
	t_ray		ray;
	t_vect		pixel_offset;
	t_color		color;

	sample_count = 0;
	color = new_color(0, 0, 0);
	while(sample_count < SPP)
	{
		ray.origin = defocus_sample(thread->scene->camera, thread->state);
		pixel_offset = set_pixel_offset(thread->scene->camera, x, y, thread->state);
		ray.dir = unit_vect(vect_subtract(pixel_offset, ray.origin));
		color = vect_add(color, calc_pixel_color(thread, ray, MAX_DEPTH));
		sample_count++;
	}
	color = vect_simple_mult(color, 1 / (float)sample_count);
	test_progresive(thread->scene, x, y, color, thread->iterations);
}

void	*set_rendering(void *args)
{
	t_thread 	*thread;

	thread = args;
	while (get_stop_status(thread->scene) == false)
	{
		if (thread->current_y >= thread->y_end)
			thread->current_y = thread->y_start;
		while (get_stop_status(thread->scene) == false && thread->current_y < thread->y_end)
		{
			thread->current_x = thread->x_start;
			while (thread->current_x < thread->x_end)
			{
				if (thread->scene->edit_mode == true)
					edit_mode(thread, thread->current_x, thread->current_y);
				else
					render_mode(thread, thread->current_x, thread->current_y);
				thread->pix_rendered++;
				thread->current_x += thread->x_increment;
			}
			thread->current_y++;
		}
		//fprintf(stderr, "THREAD: %i || LAP: %i\r", thread->id, thread->iterations);
		thread->iterations++;
	}
	free(thread->state);
	//printf("THREAD: %i --- || %i || TIME: %f || TIME_HIT: %f\n", thread->id, thread->pix_rendered, mlx_get_time(), thread->time_hit);
	if (get_stop_status(thread->scene)== true)
	{
		thread->scene->threads_backup[thread->id].iterations = thread->iterations - 1;
		thread->scene->threads_backup[thread->id].current_y = thread->current_y;
	}
	return (NULL);
}

void	main_loop(void *sc)
{
	t_scene		*scene;

	scene = sc;
	if (!scene->choose_file)
		return ;
	if (!scene->do_backup)
	{	
		set_new_image(scene);
		mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	}
	scene->time = mlx_get_time();
	init_render(scene);
	//printf("TOT PIX %i || %i\n", scene->height * scene->width, scene->height * scene->width / THREADS);
}

void	resize_disk(t_object *object, t_vect transformation)
{
	object->figure.disk.radius *= transformation.x;
	return ;
}

t_vect	get_origin_disk(t_object *object)
{
	return (object->figure.disk.center);
}

void	rotate_disk(t_object *object, t_vect transformation)
{
	object->figure.disk.normal = unit_vect(vect_add(object->figure.disk.normal, transformation));
	return ;
}

void	translate_disk(t_object *object, t_vect transformation)
{
	object->figure.disk.center = vect_add(object->figure.disk.center, transformation);
	return ;
}

bool	hit_disk(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	float	denominator;
	float	root;
	float	q;
	t_vect	hit_origin;
	t_vect	point;
	t_vect	normal;

	normal = fig.disk.normal;
	denominator = vect_dot(normal, ray.dir);
	if (fabs(denominator) < 1e-8)
		return (false);
	q = vect_dot(fig.disk.center, normal);
	point = ray.origin;
	root = (q - vect_dot(point, normal)) / denominator;
	if (root <= bounds[MIN] || bounds[MAX] <= root)
	{
		return (false);
	}
	hit_origin = vect_subtract(ray_at(ray, root), fig.disk.center);
	if (vect_length(hit_origin) > (fig.disk.radius))
	{
		return (false);
	}
	hit_info->t = root;
	hit_info->point = ray_at(ray, root);
	hit_info->normal = normal;
	// pointer in hit_info to object node hit so as to only calc normal once (after knowing closest hit)
	return (true);	
}

void	resize_quad(t_object *object, t_vect transformation)
{
	object->figure.quad.u_vect = vect_simple_mult(object->figure.quad.u_vect, transformation.x);
	object->figure.quad.v_vect = vect_simple_mult(object->figure.quad.v_vect, transformation.x);
	return ;
}

t_vect	get_origin_quad(t_object *object)
{
	return (object->figure.quad.origin);
}

void	rotate_quad(t_object *object, t_vect transformation)
{
	object->figure.quad.u_vect = vect_simple_mult(unit_vect(vect_add(object->figure.quad.u_vect, transformation)), vect_length(object->figure.quad.u_vect));
	object->figure.quad.v_vect = vect_simple_mult(unit_vect(vect_subtract(object->figure.quad.v_vect, transformation)), vect_length(object->figure.quad.v_vect));
	return ;
}

void	translate_quad(t_object *object, t_vect transformation)
{
	object->figure.quad.origin = vect_add(object->figure.quad.origin, transformation);
	return ;
}

bool	hit_quad(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	float	denominator;
	float	root;
	float	q;
	t_vect	hit_origin;
	t_vect	hit_u;
	t_vect	hit_v;
	t_vect	point;
	t_vect	normal;

	//careful with dot products close to 0 || floating point etc...
	normal = unit_vect(vect_cross(fig.quad.u_vect, fig.quad.v_vect)); // cache normal
	denominator = vect_dot(normal, ray.dir);
	if (fabs(denominator) < 1e-8)
		return (false);
	q = vect_dot(normal, fig.quad.origin);
	point = ray.origin;
	root = (q - vect_dot(point, normal)) / denominator;
	if (root <= bounds[MIN] || bounds[MAX] <= root)
	{
		return (false);
	}
	hit_origin = vect_subtract(ray_at(ray, root), fig.quad.origin);
	hit_u = vect_simple_mult(fig.quad.u_vect, vect_dot(hit_origin, vect_div(new_vect(1.0, 1.0, 1.0), fig.quad.u_vect)));
	hit_v = vect_simple_mult(fig.quad.v_vect, vect_dot(hit_origin, vect_div(new_vect(1.0, 1.0, 1.0), fig.quad.v_vect)));
	if (vect_length(hit_u) > vect_length(fig.quad.u_vect) || vect_length(hit_v) > vect_length(fig.quad.v_vect))
	{
		return (false);
	}
	hit_info->t = root;
	hit_info->point = ray_at(ray, root);
	hit_info->normal = normal;
	// pointer in hit_info to object node hit so as to only calc normal once (after knowing closest hit)
	return (true);
}

void	resize_plane(t_object *object, t_vect transformation)
{
	(void)object;
	(void)transformation;
	return ;
}

t_vect	get_origin_plane(t_object *object)
{
	return (object->figure.plane.center);
}

void	rotate_plane(t_object *object, t_vect transformation)
{
	object->figure.plane.normal = unit_vect(vect_add(object->figure.plane.normal, transformation));
	return ;
}

void	translate_plane(t_object *object, t_vect transformation)
{
	object->figure.plane.center = vect_add(object->figure.plane.center, transformation);
	return ;
}

bool	hit_plane(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	float	denominator;
	float	root;
	t_vect	point;

	//careful with dot products close to 0 || floating point etc...
	denominator = vect_dot(fig.plane.normal, ray.dir);
	if (fabs(denominator) < 1e-8)
		return (false);
	point = vect_subtract(ray.origin, fig.plane.center);
	root = -1 * (vect_dot(fig.plane.normal, point)) / denominator;
	if (root <= bounds[MIN] || bounds[MAX] <= root)
	{
		return (false);
	}
	hit_info->t = root;
	hit_info->point = ray_at(ray, root);
	hit_info->normal = fig.plane.normal;
	// pointer in hit_info to object node hit so as to only calc normal once (after knowing closest hit)
	return (true);	
}

void	resize_sphere(t_object *object, t_vect transformation)
{
	object->figure.sphere.radius *= transformation.x;
	return ;
}

t_vect	get_origin_sphere(t_object *object)
{
	return (object->figure.sphere.center);
}

void	rotate_sphere(t_object *object, t_vect transformation)
{
	(void)object;
	(void)transformation;
	return ;
}

void	translate_sphere(t_object *object, t_vect transformation)
{
	object->figure.sphere.center = vect_add(object->figure.sphere.center, transformation);
	return ;
}

bool	hit_sphere(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	t_vect	oc;
	float	var[4];
	float	sqrt_disc;
	float	root;

	oc = vect_subtract(fig.sphere.center, ray.origin);
	var[a] = vect_dot(ray.dir, ray.dir);
	var[h] = vect_dot(ray.dir, oc);
	var[c] = vect_dot(oc, oc) - (fig.sphere.radius * fig.sphere.radius);
	var[discr] = (var[h] * var[h]) - (var[a] * var[c]);
	if (var[discr] < 0)
		return (false);
	sqrt_disc = sqrtf(var[discr]); 
	root = (var[h] - sqrt_disc) / var[a];
	if (root <= bounds[MIN] || bounds[MAX] <= root)
	{
		root = (var[h] + sqrt_disc) / var[a];
		if (root <= bounds[MIN] || bounds[MAX] <= root)
			return (false);
	}
	hit_info->t = root;
	hit_info->point = ray_at(ray, root);
	hit_info->normal = vect_simple_div(vect_subtract(hit_info->point, fig.sphere.center), fig.sphere.radius);
	// pointer in hit_info to object node hit so as to only calc normal once (after knowing closest hit)
	return (true);	
}

void	resize_point_light(t_object *object, t_vect transformation)
{
	(void)object;
	(void)transformation;
	return ;
}

t_vect	get_origin_point_light(t_object *object)
{
	return (object->figure.p_light.location);
}

void	translate_point_light(t_object *object, t_vect transformation)
{
	object->figure.p_light.location = vect_add(object->figure.p_light.location, transformation);
	return ;
}

bool	hit_point_light(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	t_vect	oc;
	float	var[4];
	float	sqrt_disc;
	float	root;

	oc = vect_subtract(fig.p_light.location, ray.origin);
	var[a] = vect_dot(ray.dir, ray.dir);
	var[h] = vect_dot(ray.dir, oc);
	var[c] = vect_dot(oc, oc) - (0.2 * 0.2);
	var[discr] = (var[h] * var[h]) - (var[a] * var[c]);
	if (var[discr] < 0)
		return (false);
	sqrt_disc = sqrtf(var[discr]); 
	root = (var[h] - sqrt_disc) / var[a];
	if (root <= bounds[MIN] || bounds[MAX] <= root)
	{
		root = (var[h] + sqrt_disc) / var[a];
		if (root <= bounds[MIN] || bounds[MAX] <= root)
			return (false);
	}
	hit_info->t = root;
	hit_info->point = ray_at(ray, root);
	hit_info->normal = vect_simple_div(vect_subtract(hit_info->point, fig.p_light.location), 0.2);
	// pointer in hit_info to object node hit so as to only calc normal once (after knowing closest hit)
	return (true);	
}

void	resize_minirt(int32_t width, int32_t height, void *sc)
{
	t_scene *scene;

	scene = sc;
	scene->height = height;
	scene->width = width;
	if (!scene->choose_file)
	{
		set_new_image(scene);
		draw_file_menu(scene);
	}
	else
	{
		scene->stop = true;
		wait_for_threads(scene);
		scene->stop = false;
		if (scene->cumulative_image)
			free(scene->cumulative_image);
		scene->width = width;
		scene->height = height;
		recalculate_view(scene);
		scene->cumulative_image = ft_calloc((scene->height * scene->width), sizeof(t_vect));
		main_loop(scene);
	}
}

void	set_new_image(t_scene *scene)
{
	if (scene->image)
		mlx_delete_image(scene->mlx, scene->image);
	scene->image = mlx_new_image(scene->mlx, scene->width, scene->height);
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

void	mouse_handle(mouse_key_t button, action_t action, modifier_key_t mods, void *sc)
{
	t_scene *scene;
	int32_t	x;
	int32_t	y;

	scene = sc;
	(void)mods;
	if (scene->edit_mode == true
		&& button == MLX_MOUSE_BUTTON_LEFT
		&& action == MLX_PRESS)
	{
		mlx_get_mouse_pos(scene->mlx, &x, &y);
		deselect_objects(scene->objects, scene->lights, &scene->object_selected);
		select_object(scene, x, y);
	}
	else if (scene->edit_mode == true
		&& button == MLX_MOUSE_BUTTON_RIGHT
		&& action == MLX_PRESS)
	{
		deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	}
}

void	recalculate_view(t_scene *scene)
{
	t_vect temp;

	scene->camera.orientation = unit_vect(scene->camera.orientation);

	scene->camera.viewport_height = 2.0 * tanf((scene->camera.fov * M_PI / 180) * 0.5) * scene->camera.focus_dist;
	scene->camera.viewport_width = scene->camera.viewport_height * (scene->width / (float)scene->height);

	scene->camera.w = scene->camera.orientation;
	scene->camera.u = unit_vect(vect_cross(scene->camera.w, new_vect(0, 1, 0)));
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


	camera->origin = new_vect(0.0, 6.0, 10);
	camera->orientation = unit_vect(new_vect(0, 0.0, -1));
	//camera->origin = new_vect(0, 0, 10);
	//camera->orientation = unit_vect(new_vect(0, 0, -1));
	//camera->origin = new_vect(-5.0, 16.0, 11.0);
	//camera->orientation = unit_vect(new_vect(0.4, -1.5, -1.0));
	//camera->origin = new_vect(20.0, 3.0, -0.0);
	//camera->orientation = unit_vect(new_vect(-1.0, -0.5, -1.0));
	camera->fov = FOV;
	camera->defocus_angle = DEFOCUS;
	camera->focus_dist = FOCUS_DIST;
	camera->viewport_height = 2.0 * tanf((camera->fov * M_PI / 180) * 0.5) * camera->focus_dist;
	camera->viewport_width = camera->viewport_height * (width / (float)height);

	camera->w = camera->orientation;
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

t_color	hexa_to_vect(int color)
{
	t_color	res;

	res.x = get_r(color) / 255.0;
	res.y = get_g(color) / 255.0;
	res.z = get_b(color) / 255.0;
	return (res);
}

void	print_list(t_object *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("OBJ: %i --- type: %i\n", i, list->type);
		i++;
		list = list->next;
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

int	init_object(t_scene *scene, t_figure fig, t_material mat, t_fig_type type)
{
	t_object 	*new_obj;
	t_object 	*new_light;

	new_obj = (t_object *)malloc(sizeof(t_object));
	if (!new_obj)
		return (-1);
	if (type == SPHERE)
	{
		new_obj->type = type;
		new_obj->figure.sphere.center = fig.sphere.center;
		new_obj->figure.sphere.radius = fig.sphere.radius;
		new_obj->material.color = mat.color;
		new_obj->material.specular = mat.specular;
		new_obj->material.albedo = mat.albedo;
		new_obj->material.type = mat.type;
		new_obj->material.metal_roughness = mat.metal_roughness;
		new_obj->material.emission_intensity = mat.emission_intensity;
		new_obj->material.refraction_index = mat.refraction_index;
		new_obj->hit_func = hit_sphere;
		new_obj->edit_origin = translate_sphere;
		new_obj->edit_orientation = rotate_sphere;
		new_obj->get_origin = get_origin_sphere;
		new_obj->edit_dimensions = resize_sphere;
		new_obj->next = NULL;
	}
	if (type == PLANE)
	{
		new_obj->type = type;
		new_obj->figure.plane.center = fig.plane.center;
		new_obj->figure.plane.normal = unit_vect(fig.plane.normal);
		new_obj->material.color = mat.color;
		new_obj->material.specular = mat.specular;
		new_obj->material.albedo = mat.albedo;
		new_obj->material.type = mat.type;
		new_obj->material.metal_roughness = mat.metal_roughness;
		new_obj->material.emission_intensity = mat.emission_intensity;
		new_obj->material.refraction_index = mat.refraction_index;
		new_obj->hit_func = hit_plane;
		new_obj->edit_origin = translate_plane;
		new_obj->edit_orientation = rotate_plane;
		new_obj->get_origin = get_origin_plane;
		new_obj->edit_dimensions = resize_plane;
		new_obj->next = NULL;
	}
	if (type == QUAD)
	{
		new_obj->type = type;
		new_obj->figure.quad.origin = fig.quad.origin;
		new_obj->figure.quad.u_vect = fig.quad.u_vect;
		new_obj->figure.quad.v_vect = fig.quad.v_vect;
		new_obj->material.color = mat.color;
		new_obj->material.specular = mat.specular;
		new_obj->material.albedo = mat.albedo;
		new_obj->material.type = mat.type;
		new_obj->material.metal_roughness = mat.metal_roughness;
		new_obj->material.emission_intensity = mat.emission_intensity;
		new_obj->material.refraction_index = mat.refraction_index;
		new_obj->hit_func = hit_quad;
		new_obj->edit_origin = translate_quad;
		new_obj->edit_orientation = rotate_quad;
		new_obj->get_origin = get_origin_quad;
		new_obj->edit_dimensions = resize_quad;
		new_obj->next = NULL;
	}
	if (type == DISK)
	{
		new_obj->type = type;
		new_obj->figure.disk.center = fig.disk.center;
		new_obj->figure.disk.normal = unit_vect(fig.disk.normal);
		new_obj->figure.disk.radius = fig.disk.radius;
		new_obj->material.color = mat.color;
		new_obj->material.specular = mat.specular;
		new_obj->material.albedo = mat.albedo;
		new_obj->material.type = mat.type;
		new_obj->material.metal_roughness = mat.metal_roughness;
		new_obj->material.emission_intensity = mat.emission_intensity;
		new_obj->material.refraction_index = mat.refraction_index;
		new_obj->hit_func = hit_disk;
		new_obj->edit_origin = translate_disk;
		new_obj->edit_orientation = rotate_disk;
		new_obj->get_origin = get_origin_disk;
		new_obj->edit_dimensions = resize_disk;
		new_obj->next = NULL;
	}
	if (type == LIGHT)
	{
		new_obj->type = type;
		new_obj->figure.p_light.location = fig.p_light.location;
		new_obj->material.color = mat.color;
		new_obj->material.specular = mat.specular;
		new_obj->material.albedo = mat.albedo;
		new_obj->material.type = mat.type;
		new_obj->material.metal_roughness = mat.metal_roughness;
		new_obj->material.emission_intensity = mat.emission_intensity;
		new_obj->material.refraction_index = mat.refraction_index;
		new_obj->hit_func = hit_point_light;
		new_obj->edit_origin = translate_point_light;
		new_obj->edit_orientation = rotate_sphere;
		new_obj->get_origin = get_origin_point_light;
		new_obj->edit_dimensions = resize_point_light;
		new_obj->next = NULL;
	}
	new_obj->selected = false;
	if (mat.type == EMISSIVE && type == LIGHT)
	{
		new_light = (t_object *)malloc(sizeof(t_object));
		new_light = ft_memcpy(new_light, new_obj, sizeof(t_object));
		add_object(&scene->lights, new_light);
		if (type == LIGHT)
			return (0);
	}
	add_object(&scene->objects, new_obj);
	return (0);
}

void	create_box(t_scene *scene, t_vect center, t_vect u, t_vect v, t_material mat, float depth, float width, float height)
{
	t_figure	fig;
	t_vect		normal;
	t_vect		anti_normal;

	u = unit_vect(u);
	v = unit_vect(v);

	normal = unit_vect(vect_cross(u, v));
	anti_normal = vect_simple_mult(normal, -1);

	fig.quad.u_vect = vect_simple_mult(u, width);
	fig.quad.v_vect = vect_simple_mult(v, height);
	fig.quad.origin = vect_add(center, vect_simple_mult(normal, depth));
	init_object(scene, fig, mat, QUAD);

	fig.quad.u_vect = vect_simple_mult(u, width);
	fig.quad.v_vect = vect_simple_mult(v, -1 * height);
	fig.quad.origin = vect_add(center, vect_simple_mult(anti_normal, depth));
	init_object(scene, fig, mat, QUAD);

	fig.quad.u_vect = vect_simple_mult(anti_normal, depth);
	fig.quad.v_vect = vect_simple_mult(v, height);
	fig.quad.origin = vect_add(center, vect_simple_mult(u, width));
	init_object(scene, fig, mat, QUAD);

	fig.quad.u_vect = vect_simple_mult(anti_normal, depth);
	fig.quad.v_vect = vect_simple_mult(v, -1 * height);
	fig.quad.origin = vect_add(center, vect_simple_mult(u, -1 * width));
	init_object(scene, fig, mat, QUAD);

	fig.quad.u_vect = vect_simple_mult(anti_normal, depth);
	fig.quad.v_vect = vect_simple_mult(u, -1 * width);
	fig.quad.origin = vect_add(center, vect_simple_mult(v, height));
	init_object(scene, fig, mat, QUAD);

	fig.quad.u_vect = vect_simple_mult(anti_normal, depth);
	fig.quad.v_vect = vect_simple_mult(u, width);
	fig.quad.origin = vect_add(center, vect_simple_mult(v, -1 * height));
	init_object(scene, fig, mat, QUAD);
}

void	init_lights(t_scene *scene)
{
	t_figure	fig;
	t_material	mat;

	ft_bzero(&mat, sizeof(mat));
	ft_bzero(&fig, sizeof(fig));

	fig.p_light.location = new_vect(0, 5.0, -7.0);
	mat.color = hexa_to_vect(BLUE);
	mat.specular = 0.0;
	mat.metal_roughness = 0.0;
	mat.albedo = mat.color;
	mat.emission_intensity = 5.0;
	mat.type = EMISSIVE;
	//init_object(scene, fig, mat, LIGHT);
	fig.p_light.location = new_vect(0, -5.0, -7.0);
	mat.color = hexa_to_vect(TURQUOISE);
	mat.specular = 0.0;
	mat.metal_roughness = 0.0;
	mat.albedo = mat.color;
	mat.emission_intensity = 5.0;
	mat.type = EMISSIVE;
	//init_object(scene, fig, mat, LIGHT);
	fig.p_light.location = new_vect(8, 0.0, -8.0);
	mat.color = hexa_to_vect(GREEN);
	mat.specular = 0.0;
	mat.metal_roughness = 0.0;
	mat.albedo = mat.color;
	mat.emission_intensity = 2.5;
	mat.type = EMISSIVE;
	//init_object(scene, fig, mat, LIGHT);
	fig.p_light.location = new_vect(-8.0, 0.0, -8.0);
	mat.color = hexa_to_vect(BLUE);
	mat.specular = 0.0;
	mat.metal_roughness = 0.0;
	mat.albedo = mat.color;
	mat.emission_intensity = 2.5;
	mat.type = EMISSIVE;
	//init_object(scene, fig, mat, LIGHT);
	fig.p_light.location = new_vect(1.0, -5.0, -2.0);
	mat.color = hexa_to_vect(YELLOW);
	mat.specular = 0.0;
	mat.metal_roughness = 0.0;
	mat.albedo = mat.color;
	mat.emission_intensity = 2.5;
	mat.type = EMISSIVE;
	//init_object(scene, fig, mat, LIGHT);
	(void)scene;
}

void	init_figures(t_scene *scene)
{
	t_figure	fig;
	t_material	mat;

	ft_bzero(&mat, sizeof(mat));
	ft_bzero(&fig, sizeof(fig));

	fig.sphere.center = new_vect(0.0, 1.0, -4);
	fig.sphere.radius = 1;
	mat.color = hexa_to_vect(DEF_COLOR);
	mat.albedo = mat.color;
	mat.specular = 0.2;
	mat.metal_roughness = 0.1;
	mat.refraction_index = 1.5;
	mat.emission_intensity = 0.0;
	mat.type = LAMBERTIAN;
	init_object(scene, fig, mat, SPHERE);

	fig.sphere.center = new_vect(2.0, 1.0, -4);
	fig.sphere.radius = 1;
	mat.color = hexa_to_vect(DEF_COLOR);
	mat.albedo = mat.color;
	mat.specular = 0.2;
	mat.metal_roughness = 0.1;
	mat.refraction_index = 1.5;
	mat.emission_intensity = 0.0;
	mat.type = LAMBERTIAN;
	init_object(scene, fig, mat, SPHERE);

	fig.sphere.center = new_vect(0.0, 0.0, 0.0);
	fig.plane.normal = new_vect(0.0, 1.0, 0.0);
	mat.color = hexa_to_vect(CYAN_GULF);
	mat.albedo = mat.color;
	mat.specular = 0.2;
	mat.metal_roughness = 0.1;
	mat.refraction_index = 1.5;
	mat.emission_intensity = 0.0;
	mat.type = LAMBERTIAN;
	init_object(scene, fig, mat, PLANE);


	fig.sphere.center = new_vect(0.0, -0.8, 0.0);
	fig.plane.normal = new_vect(0.0, 1.0, 0.0);
	mat.color = hexa_to_vect(BLACK);
	mat.albedo = mat.color;
	mat.specular = 0.2;
	mat.metal_roughness = 0.0;
	mat.refraction_index = 1.5;
	mat.emission_intensity = 1.5;
	mat.type = LAMBERTIAN;
	//init_object(scene, fig, mat, PLANE);
}

void	init_scene(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
	scene->width = WINW;
	scene->height = WINH;
	scene->amb_light = AMB_LIGHT;
	scene->aspect_ratio = scene->width / (float)scene->height;
	scene->choose_file = 1;
	scene->current_file = 0;
	scene->mlx = mlx_init(scene->width, scene->height, "miniRT", true);
	scene->image = mlx_new_image(scene->mlx, scene->width, scene->height);
	scene->cumulative_image = ft_calloc((scene->height * scene->width), sizeof(t_vect));
	ft_memset(scene->threads_backup, 0, sizeof(t_thread_backup) * THREADS);
	pthread_mutex_init(&scene->stop_mutex, NULL);
	scene->stop = false;
	scene->edit_mode = false;
	scene->do_backup = false;
	scene->object_selected = false;
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	init_figures(scene);
	init_lights(scene);
	init_camera(&scene->camera, scene->width, scene->height);
	scene->back_up_camera = scene->camera;
}

void	free_objects(t_object **objects)
{
	t_object *temp;

	if (objects)
	{
		while ((*objects))
		{
			temp = (*objects)->next;
			free((*objects));
			(*objects) = temp;
		}
	}
}

void	wait_for_threads(t_scene *scene)
{
	int i;
	
	i = 0;
	while (i < THREADS)
	{
		if (pthread_join(scene->threads[i].self, NULL))
		{
			exit (200);
		}
		i++;
	}
}

void	unset_stop_status(t_scene *scene)
{
	pthread_mutex_lock(&scene->stop_mutex);
	scene->stop = false;
	pthread_mutex_unlock(&scene->stop_mutex);
}

void	set_stop_status(t_scene *scene)
{
	pthread_mutex_lock(&scene->stop_mutex);
	scene->stop = true;
	pthread_mutex_unlock(&scene->stop_mutex);
}

bool	get_stop_status(t_scene *scene)
{
	bool res;

	pthread_mutex_lock(&scene->stop_mutex);
	res = scene->stop;
	pthread_mutex_unlock(&scene->stop_mutex);
	return (res);
}

int	main(int argc, char **argv)
{
	//check exit when clicking x on window
	//TEST MUTEX PERFOMANCE ETC...
	(void)argc;
	(void)argv;
	t_scene	scene;

	init_scene(&scene);
	//draw_file_menu(&scene);
	main_loop(&scene);
	mlx_key_hook(scene.mlx, key_down, &scene);
	mlx_mouse_hook(scene.mlx, mouse_handle, &scene);
	mlx_resize_hook(scene.mlx, resize_minirt, &scene);
	//mlx_loop_hook(scene.mlx, main_loop, &scene);
	mlx_loop(scene.mlx);
	printf("END: %f\n", mlx_get_time() - scene.time);
	wait_for_threads(&scene);
	pthread_mutex_destroy(&scene.stop_mutex);
	if (scene.mlx)
		mlx_terminate(scene.mlx);
	free(scene.cumulative_image);
	free_objects(&scene.objects);
	free_objects(&scene.lights);
	//free_buttons(scene.buttons);
	return (0);
}
