/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:26 by vperez-f          #+#    #+#             */
/*   Updated: 2024/12/31 02:32:02 by vpf              ###   ########.fr       */
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

float	f_clamp(float target, float min, float max)
{
	if (target < min)
		return (min);
	if (target > max)
		return (max);
	return (target);
}

void	print_vec_s(t_vect vect, char*msg)
{
	printf("%s X: %f\n", msg, vect.x);
	printf("%s Y: %f\n", msg, vect.y);
	printf("%s Z: %f\n\n", msg, vect.z);
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

void	progressive_render(t_thread *thread, uint32_t x, uint32_t y, t_color color)
{
	t_color		final_color;
	t_vect		*prev_color_index;

	if ((x >= thread->scene->width) || y >= thread->scene->height)
		return ;
	prev_color_index = &thread->scene->cumulative_image[((y * thread->scene->image->width) + x)];
	prev_color_index->x += color.x;
	prev_color_index->y += color.y;
	prev_color_index->z += color.z;
	final_color = clamp_vect(vect_simple_mult(*prev_color_index, 1.0 / (float)thread->iterations), 0.0, 1.0);
	mlx_put_pixel(thread->scene->image, x, y, get_rgba(
		(int)(final_color.x * 255.9),
		(int)(final_color.y * 255.9),
		(int)(final_color.z * 255.9),
		255));
}

void	move_menu(t_scene *scene, keys_t key)
{
	if (key == MLX_KEY_UP)
	{
		if (scene->current_file > 0)
			scene->current_file--;
	}
	else if (key == MLX_KEY_DOWN)
	{
		if (scene->current_file < scene->map_count - 1) 
			scene->current_file++;
	}
	else if (key == MLX_KEY_LEFT)
	{
		if (scene->current_file >= 10)
			scene->current_file -= 10;
	}
	else if (key == MLX_KEY_RIGHT)
	{
		if ((scene->current_file + 10) < scene->map_count)
			scene->current_file += 10;
		else if ((int)(scene->current_file / 20) < (int)(scene->map_count) / 20)
			scene->current_file = ((scene->current_file / 20) + 1) * 20;
	}
	draw_buttons(scene->buttons, scene);
}

int		is_movement_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_UP || key_data.key == MLX_KEY_DOWN
		|| key_data.key == MLX_KEY_LEFT || key_data.key == MLX_KEY_RIGHT
		||key_data.key == MLX_KEY_LEFT_SHIFT || key_data.key == MLX_KEY_SPACE)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
	{
		return (1);
	}
	return (0);
}

int		is_rotation_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_S
		|| key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_D
		|| key_data.key == MLX_KEY_Q || key_data.key == MLX_KEY_E)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
	{
		return (1);
	}
	return (0);
}

int		is_extra_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_F
		|| key_data.key == MLX_KEY_G
		|| key_data.key == MLX_KEY_V
		|| key_data.key == MLX_KEY_T
		|| key_data.key == MLX_KEY_O
		|| key_data.key == MLX_KEY_Z
		|| key_data.key == MLX_KEY_X
		|| key_data.key == MLX_KEY_C
		|| key_data.key == MLX_KEY_B
		|| key_data.key == MLX_KEY_J
		|| key_data.key == MLX_KEY_K
		|| key_data.key == MLX_KEY_L
		|| key_data.key == MLX_KEY_P
		|| key_data.key == MLX_KEY_TAB
		|| key_data.key == MLX_KEY_EQUAL
		|| key_data.key == MLX_KEY_MINUS
		|| key_data.key == MLX_KEY_ENTER
		|| key_data.key == MLX_KEY_SEMICOLON
		|| key_data.key == MLX_KEY_APOSTROPHE
		|| key_data.key == MLX_KEY_LEFT_BRACKET
		|| key_data.key == MLX_KEY_RIGHT_BRACKET)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
	{
		return (1);
	}
	return (0);
}

int		is_camera_key_down(mlx_key_data_t key_data)
{
	if (is_movement_key_down(key_data)
		|| is_rotation_key_down(key_data)
		|| is_extra_key_down(key_data))
	{
		return (1);
	}
	return (0);
}

int	is_material_key_down(mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_J
		|| key_data.key == MLX_KEY_K
		|| key_data.key == MLX_KEY_L
		|| key_data.key == MLX_KEY_SEMICOLON
		|| key_data.key == MLX_KEY_APOSTROPHE)
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

int	is_aspect_key_down(mlx_key_data_t key_data)
{
	if (is_rgb_key_down(key_data)
		|| is_material_key_down(key_data)
		|| key_data.key == MLX_KEY_TAB)
	{
		return (1);
	}
	return (0);
}
int	is_copy_delete_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_N
		|| key_data.key == MLX_KEY_BACKSPACE)
		&& (key_data.action == MLX_PRESS))
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
		|| key_data.key == MLX_KEY_6
		|| key_data.key == MLX_KEY_7
		|| key_data.key == MLX_KEY_8)
		&& (key_data.action == MLX_PRESS))
	{
		return (1);
	}
	return (0);
}

int	is_scene_settings_key_down(mlx_key_data_t key_data)
{
		if ((key_data.key == MLX_KEY_COMMA
			|| key_data.key == MLX_KEY_PERIOD
			|| key_data.key == MLX_KEY_RIGHT_SHIFT)
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


t_vect	align_camera_to_axis(mlx_key_data_t key_data)
{
	t_vect	res;

	res = new_vect(0.0, 0.0, -1.0);
	if (key_data.key == MLX_KEY_W)
	{
		res = new_vect(0.0, 1.0, 0.0);
	}
	else if (key_data.key == MLX_KEY_A)
	{
		res = new_vect(-1.0, 0.0, 0.0);
	}
	else if (key_data.key == MLX_KEY_S)
	{
		res = new_vect(0.0, -1.0, 0.0);
	}
	else if (key_data.key == MLX_KEY_D)
	{
		res = new_vect(1.0, 0.0, 0.0);
	}
	else if (key_data.key == MLX_KEY_Q)
	{
		res = new_vect(0.0, 0.0, 1.0);
	}
	else if (key_data.key == MLX_KEY_E)
	{
		res = new_vect(0.0, 0.0, -1.0);
	}
	return (res);
}

int	check_rotations(t_camera *camera, mlx_key_data_t key_data)
{
	if (key_data.modifier == MLX_CONTROL)
	{
		camera->orientation = align_camera_to_axis(key_data);
	}
	else if (key_data.key == MLX_KEY_W)
	{
		rotate_vector(&camera->orientation, camera->u, 0.05);
	}
	else if (key_data.key == MLX_KEY_A)
	{
		rotate_vector(&camera->orientation, camera->v, 0.05);
	}
	else if (key_data.key == MLX_KEY_S)
	{
		rotate_vector(&camera->orientation, camera->u, -0.05);
	}
	else if (key_data.key == MLX_KEY_D)
	{
		rotate_vector(&camera->orientation, camera->v, -0.05);
	}
	print_vec_s(unit_vect(camera->orientation), "New camera orientation");
	return (1);
}

int	check_translations(t_camera *camera, t_object *skysphere, mlx_key_data_t key_data)
{
	t_vect	transformation;

	if (key_data.modifier == MLX_CONTROL)
		transformation = absolute_translate(key_data);
	else
		transformation = relative_translate(camera, key_data);
	if (skysphere)
		skysphere->figure.sphere.center = vect_add(skysphere->figure.sphere.center, transformation);
	camera->origin = vect_add(camera->origin, transformation);
	print_vec_s(camera->origin, "New camera origin: ");
	return (1);
}

int	check_settings(t_camera *camera, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_F)
	{
		if (key_data.modifier == MLX_CONTROL)
		{
			if (camera->fov > 1)
				camera->fov -= 1;
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
			if (camera->focus_dist > 1)
				camera->focus_dist -= 0.5;
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
		camera->origin = new_vect(0.0, 0.5, 1.0);
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

int	is_reset_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_O || key_data.key == MLX_KEY_T)
		&& (key_data.action == MLX_PRESS))
	{
		return (1);
	}
	return (0);
}

int	is_settings_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_F
		|| key_data.key == MLX_KEY_G
		|| key_data.key == MLX_KEY_V)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
	{
		return (1);
	}
	return (0);
}

void	move_camera(t_camera *camera, t_camera *backup, t_object *skysphere, mlx_key_data_t key_data)
{
	if (is_reset_key_down(key_data))
		check_reset(camera, backup, key_data);
	else if (is_rotation_key_down(key_data))
		check_rotations(camera, key_data);
	else if (is_movement_key_down(key_data))
		check_translations(camera, skysphere, key_data);
	else if (is_settings_key_down(key_data))
		check_settings(camera, key_data);
	return ;
}

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

void	increment_material_component(t_object *target_object, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_J)
	{
		target_object->material.specular += 0.05;
		if (target_object->material.specular > 1.0)
			target_object->material.specular = 1.0;
	}
	else if (key_data.key == MLX_KEY_K)
	{
		target_object->material.metal_roughness += 0.05;
		if (target_object->material.metal_roughness > 1.0)
			target_object->material.metal_roughness = 1.0;
	}
	else if (key_data.key == MLX_KEY_L)
	{
		target_object->material.refraction_index += 0.05;
		if (target_object->material.refraction_index > 10.0)
			target_object->material.refraction_index = 10.0;
	}
	else if (key_data.key == MLX_KEY_SEMICOLON)
	{
		target_object->material.emission_intensity += 0.05;
		if (target_object->material.emission_intensity > 10000.0)
			target_object->material.emission_intensity = 10000.0;
	}
	else if (key_data.key == MLX_KEY_APOSTROPHE)
		target_object->material.pattern = true;
	return ;
}

void	decrement_material_component(t_object *target_object, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_J)
	{
		target_object->material.specular -= 0.05;
		if (target_object->material.specular < 0.0)
			target_object->material.specular = 0.0;
	}
	else if (key_data.key == MLX_KEY_K)
	{
		target_object->material.metal_roughness -= 0.05;
		if (target_object->material.metal_roughness < 0.0)
			target_object->material.metal_roughness = 0.0;
	}
	else if (key_data.key == MLX_KEY_L)
	{
		target_object->material.refraction_index -= 0.05;
		if (target_object->material.refraction_index < 0.0)
			target_object->material.refraction_index = 0.0;
	}
	else if (key_data.key == MLX_KEY_SEMICOLON)
	{
		target_object->material.emission_intensity -= 0.05;
		if (target_object->material.emission_intensity < 0.0)
			target_object->material.emission_intensity = 0.0;
	}
	else if (key_data.key == MLX_KEY_APOSTROPHE)
		target_object->material.pattern = false;
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
	ft_printf(STDOUT_FILENO, "Material is now: %i\n\n", target_object->material.type);
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

void	change_scene_settings(t_scene *scene, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_COMMA)
	{
		scene->amb_light -= 0.05;
		if (scene->amb_light < 0.0)
			scene->amb_light = 0.0;
		printf("Ambient light intensity: %f\n", scene->amb_light);
	}
	else if (key_data.key == MLX_KEY_PERIOD)
	{
		scene->amb_light += 0.05;
		printf("Ambient light intensity: %f\n", scene->amb_light);
	}
	else if (key_data.key == MLX_KEY_RIGHT_SHIFT)
		deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	return ;
}


void	select_scene(t_scene *scene)
{
	if (scene->map_count)
	{
		scene->path = get_map_path(scene->current_file);
		if (!scene->path)
			return (exit_err(ERR_MEM_MSG, "while retrieving map path", 1));
	}
	scene->choose_file = 1;
	init_scene(scene);
	set_new_image(scene);
	mlx_image_to_window(scene->mlx, scene->image, 0 ,0);
	main_loop(scene);
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

float	p_light_specular(t_hit_info hit_info, t_ray inc_ray, t_vect cam_orientation)
{
	t_vect		bounce_dir;
	float		test;

	inc_ray.dir = unit_vect(inc_ray.dir);
	bounce_dir = vect_subtract(inc_ray.dir, vect_simple_mult(hit_info.normal, 2 * vect_dot(inc_ray.dir, hit_info.normal)));
	test = vect_dot(unit_vect(bounce_dir), cam_orientation);
	if (test < 0)
		test = 0;
	test = pow(test, (128 * (1.1 - hit_info.object->material.metal_roughness)));
	return (test);
}

t_vect	test_sample_area(uint32_t *state, t_object *light)
{
	return (vect_add(light->get_origin(light), vect_simple_mult(get_random_uvect(state), light->figure.p_light.radius_shadow)));
}

t_color	sample_area_light(t_thread *thread, t_object *light, t_hit_info hit_info, t_mat_type scatter_type)
{
	t_ray		shadow_ray;
	t_hit_info	test_hit;
	float		mod;
	float		mod2;
	t_color 	emittance;

	t_vect		sample_area;

	emittance = new_color(0.0, 0.0, 0.0);
	if (light->type != SPHERE)
		return (emittance);
	shadow_ray.origin = hit_info.point;
	sample_area = test_sample_area(thread->state, light);
	shadow_ray.dir = vect_subtract(sample_area, hit_info.point);
	if (!shadow_hit(thread->scene, shadow_ray, &test_hit, vect_length(shadow_ray.dir)))
	{
		mod2 = 1 / vect_length(shadow_ray.dir);
		if (scatter_type == LAMBERTIAN)
		{
			mod = vect_dot(hit_info.normal, unit_vect(shadow_ray.dir));
			if (mod < 0)
				mod = 0;
			emittance = vect_add(emittance, vect_simple_mult(light->material.color, (light->material.emission_intensity * mod * mod2)));
		}
		else if (scatter_type == METAL)
			emittance = vect_add(emittance, vect_simple_mult(light->material.color, (p_light_specular(hit_info, shadow_ray, thread->scene->camera.orientation) * light->material.emission_intensity) * mod2 * 10));			
		thread->sampled = true;
	}
	else
	{
		thread->sampled = false;
	}
	return (emittance);
}

t_color	light_sampling(t_thread *thread, t_hit_info hit_info, t_mat_type scatter_type)
{
	t_ray		shadow_ray;
	t_hit_info	test_hit;
	float		mod;
	float		mod2;
	t_object	*temp;
	t_color 	emittance;

	t_vect		bound_to_light;

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
		bound_to_light = vect_subtract(temp->figure.p_light.location, hit_info.point);
		shadow_ray.dir = vect_subtract(test_sample_area(thread->state, temp), hit_info.point);
		if (!shadow_hit(thread->scene, shadow_ray, &test_hit, vect_length(bound_to_light)))
		{
			mod2 = 1 / vect_length(bound_to_light);
			if (scatter_type == LAMBERTIAN)
			{
				mod = vect_dot(hit_info.normal, unit_vect(bound_to_light));
				if (mod < 0)
					mod = 0;
				emittance = vect_add(emittance, vect_simple_mult(temp->material.color, (temp->material.emission_intensity * mod * mod2)));
			}
			else if (scatter_type == METAL)
				emittance = vect_add(emittance, vect_simple_mult(temp->material.color, (p_light_specular(hit_info, shadow_ray, thread->scene->camera.orientation) * temp->material.emission_intensity) * mod2 * 10));
		}
		temp = temp->next;
	}
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
	hit_info.object->material.albedo = get_obj_color(&hit_info);
	*emittance = light_sampling(thread, hit_info, METAL);
	return (bounce_ray);
}

t_ray	test_sampling(t_thread *thread, t_hit_info *hit_info)
{
	t_ray		light_ray;
	t_object	*temp;

	temp = thread->scene->objects;
	while (temp)
	{
		if (temp->material.type != EMISSIVE)
		{
			temp = temp->next;
			continue ;
		}
		light_ray.origin = hit_info->point;
		light_ray.dir = vect_subtract(test_sample_area(thread->state, temp), hit_info->point);
		temp = temp->next;
	}
	return (light_ray);
}

t_ray	lambertian_scatter(uint32_t *state, t_hit_info hit_info, t_color *emittance, t_thread *thread)
{
	t_vect		bounce_dir;
	t_vect		target_on_sphere;
	t_ray		bounce_ray;

	bounce_dir = get_random_uvect(state);
	target_on_sphere = vect_add(bounce_dir, hit_info.normal);
	if (zero_vect(target_on_sphere))
		target_on_sphere = hit_info.normal;
	target_on_sphere = unit_vect(target_on_sphere); // = target_onsphere + hit.info.point
	bounce_ray = new_ray(target_on_sphere, hit_info.point);
	hit_info.object->material.albedo = get_obj_color(&hit_info);
	*emittance = light_sampling(thread, hit_info, LAMBERTIAN);
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
	cos = vect_dot(vect_simple_mult(udir, -1.0), adj_hit.normal);
	sin = sqrtf(1.0 - (cos * cos));
	if (((index * sin) > 1.0 || reflectance(index, cos) > fast_rand(state)) && front_face)
		bounce_ray = metal_scatter(state, adj_hit, inc_ray, emittance, thread);
	else
	{
		bounce_ray = refract(adj_hit, udir, index, cos);
		if (hit_info.object->material.metal_roughness)
			bounce_ray.dir = vect_add(unit_vect(bounce_ray.dir), vect_simple_mult(get_random_uvect(state), powf(hit_info.object->material.metal_roughness, 2)));
	}
	hit_info.object->material.albedo = get_obj_color(&hit_info);
	return (bounce_ray);
}
void	check_normal(t_vect *normal, t_vect *ray_dir)
{	
	if (vect_dot(*normal, unit_vect(*ray_dir)) <= 0.0)
		return ;
	*normal = vect_simple_mult(*normal, -1.0);
}

bool	is_2d(t_object *object)
{
	if (object->type == PLANE || object->type == QUAD || object->type == DISK)
	{
		return (true);
	}
	return (false);
}

bool	scatter_ray(t_thread *thread, t_hit_info hit_info, t_ray *bounce_ray, t_ray ray, t_color *emittance)
{
	if (!hit_info.object->texture && is_2d(hit_info.object))
	{
		check_normal(&hit_info.normal, &ray.dir);
	}
	if (hit_info.object->material.type == LAMBERTIAN)
	{
		(*bounce_ray) = lambertian_scatter(thread->state, hit_info, emittance, thread);
	}
	else if (hit_info.object->material.type == METAL)
	{
		(*bounce_ray) = metal_scatter(thread->state, hit_info, ray, emittance, thread);
		if (vect_dot((*bounce_ray).dir, hit_info.normal) <= 0)
			return (false);
	}
	else if (hit_info.object->material.type == DIELECTRIC)
	{
		(*bounce_ray) = dielectric_scatter(thread->state, hit_info, ray, emittance, thread);
	}
	else if (hit_info.object->material.type == GLOSSY)
	{
		float	cos = vect_dot(vect_simple_mult(ray.dir, -1.0), hit_info.normal);
		if (hit_info.object->material.specular > fast_rand(thread->state) 
			|| (reflectance(1.5, cos) > fast_rand(thread->state) && hit_info.object->material.specular))
		{
			(*bounce_ray) = metal_scatter(thread->state, hit_info, ray, emittance, thread);
			if (vect_dot((*bounce_ray).dir, hit_info.normal) <= 0)
				return (false);
			hit_info.object->material.albedo = new_color(1.0, 1.0, 1.0);
		}
		else
		{
			(*bounce_ray) = lambertian_scatter(thread->state, hit_info, emittance, thread);
		}
	}
	return (true);
}

void	set_sky_texture_color(t_vect *point, t_figure *fig, t_texture *tx, t_color *color)
{
	float		polar_coords[2];
	t_vect		texture_dims;
	uint8_t		*pixel;
	t_texel		texel;
	float		point_radius;

	set_polar_coords(point, fig, polar_coords);
	point_radius = sqrt(pow(point->x, 2) + pow(point->z, 2));
	texture_dims.x = tx->texture->width * (point_radius / fig->sphere.radius);
	texture_dims.y = tx->texture->height;
	if (point->x < 0.0)
		polar_coords[LATITUDE] = -polar_coords[LATITUDE];
	if (point->y > 0.0)
		polar_coords[LONGITUDE] = -polar_coords[LONGITUDE];
	texel.x = (polar_coords[LATITUDE] * (tx->texture->width / texture_dims.x));
	texel.y = polar_coords[LONGITUDE] + (texture_dims.y / 2.0);
	if (polar_coords[LATITUDE] < 0)
		texel.x += tx->texture->width;
	texel.x = f_clamp(texel.x, 0, tx->texture->width - 1);
	texel.y = f_clamp(texel.y, 0, tx->texture->height - 1);
	pixel = tx->texture->pixels	+ ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	color->x = *pixel / 255.0;
	color->y = *(pixel + 1) / 255.0;
	color->z = *(pixel + 2) / 255.0;
}

t_color	get_sky_sphere_color(t_thread *thread, t_hit_info *ht)
{
	t_color	scene_sky_color;
	t_vect	translated_point;

	translated_point = vect_subtract(ht->point, thread->scene->sky_sphere->figure.sphere.center);
	set_sky_texture_color(&translated_point, &thread->scene->sky_sphere->figure, thread->scene->sky_sphere->texture, &scene_sky_color);
	return (scene_sky_color);
}

t_color	get_sky_color(t_thread *thread, t_ray *ray)
{
	float		mod;
	t_hit_info	hit_info;
	t_vect		background;

	ft_bzero(&hit_info, sizeof(hit_info));
	background = new_color(0.0, 0.0, 0.0);
	if (thread->scene->sky_sphere && ray_hit(thread->scene->sky_sphere, *ray, &hit_info, NULL))
	{
		hit_info.point = ray_at(*ray, hit_info.t);
		background = get_sky_sphere_color(thread, &hit_info);
	}
	else
	{
		if (AMB)
			background = hexa_to_vect(thread->scene->amb_color);
		else
		{
			mod = 0.5 * (ray->dir.y + 1.0);
			background = vect_add(vect_simple_mult(new_color(1, 1, 1),
				(1.0 - mod)),vect_simple_mult(new_color(0.3, 0.7, 1), mod));
		}
	}
	background = vect_simple_mult(background, thread->scene->amb_light);
	return (background);
}

t_color	calc_pixel_color(t_thread *thread, t_ray ray, int depth)
{
	t_color		emittance;
	float		time_aux;
	t_hit_info	hit_info;
	t_ray		bounce_ray;

	float		rr_coef_test;

	if (depth <= (thread->scene->max_depth / 2))
		rr_coef_test = 0.8;
	else
		rr_coef_test = 1.0;
	if (depth < 1 || (rr_coef_test != 1.0 && fast_rand(thread->state) > rr_coef_test))
		return (new_color(0, 0, 0));
	ft_bzero(&hit_info, sizeof(hit_info));
	emittance = new_color(0, 0, 0);
	time_aux = mlx_get_time();
	if (ray_hit(thread->scene->objects, ray, &hit_info, thread->scene->sky_sphere))
	{
		hit_info.point = ray_at(ray, hit_info.t);
		hit_info.normal = hit_info.object->get_normal(&hit_info, &hit_info.object->figure);
		thread->time_hit += mlx_get_time() - time_aux;
		if (hit_info.object->material.type == EMISSIVE)
		{
			emittance = vect_simple_mult(get_obj_color(&hit_info), hit_info.object->material.emission_intensity);
			return (emittance);
		}
		if (!scatter_ray(thread, hit_info, &bounce_ray, ray, &emittance))
		{
			return (emittance);
		}
		emittance = vect_mult(emittance, get_obj_color(&hit_info));
		return (vect_simple_mult(vect_add(vect_mult(calc_pixel_color(thread, bounce_ray, depth - 1), get_obj_color(&hit_info)), emittance), 1 / rr_coef_test));
	}
	thread->time_hit += mlx_get_time() - time_aux;
	return (get_sky_color(thread, &ray));
}

void	set_new_image(t_scene *scene)
{
	if (scene->image)
		mlx_delete_image(scene->mlx, scene->image);
	scene->image = mlx_new_image(scene->mlx, scene->width, scene->height);
}

int	vect_to_int(t_color color)
{
	return (get_rgba((int)(color.x * 255.9),
		(int)(color.y * 255.9), (int)(color.z * 255.9), 255));
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

void	init_sky_sphere(t_scene *scene, char *path)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	new_obj->material = new_standard_material();
	new_obj->type = SPHERE;
	new_obj->figure.sphere.center = scene->camera.origin;
	new_obj->texture = get_texture(path, 1);
	new_obj->figure.sphere.radius = new_obj->texture->texture->width / (M_PI * 2.0);
	new_obj->hit_func = hit_sphere;
	new_obj->edit_origin = translate_sphere;
	new_obj->edit_orientation = rotate_sphere;
	new_obj->get_origin = get_origin_sphere;
	new_obj->edit_dimensions = resize_sphere;
	new_obj->get_visual = get_sphere_pattern;
	new_obj->get_normal = get_sphere_normal;
	new_obj->next = NULL;
	add_object(&scene->sky_sphere, new_obj);
}

void	init_minirt(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
	scene->width = WINW;
	scene->height = WINH;
	scene->amb_color = AMB_COLOR;
	scene->amb_light = -1;
	scene->aspect_ratio = scene->width / (float)scene->height;
	scene->choose_file = 0;
	scene->current_file = 0;
	scene->mlx = mlx_init(scene->width, scene->height, "miniRT", true);
	scene->image = mlx_new_image(scene->mlx, scene->width, scene->height);
	if (!scene->image)
		return (exit_err(ERR_MEM_MSG, "while loading mlx image", 2));
	scene->cumulative_image = ft_calloc((scene->height * scene->width), sizeof(t_vect));
	if (!scene->cumulative_image)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	scene->state = (uint32_t)(scene->height * scene->width * mlx_get_time());
	ft_memset(scene->threads_backup, 0, sizeof(t_thread_backup) * THREADS);
	pthread_mutex_init(&scene->stop_mutex, NULL);
	scene->stop = false;
	scene->edit_mode = false;
	scene->do_backup = false;
	scene->object_selected = false;
	scene->path = NULL;
	scene->menu_tx = get_texture("./textures/menu/Sad_face1.png", 1);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	init_minirt(&scene);
	if (parse_map_path(&scene, argc, argv))
		draw_file_menu(&scene);
	init_scene(&scene);
	main_loop(&scene);
	mlx_close_hook(scene.mlx, close_mlx, &scene);
	mlx_key_hook(scene.mlx, key_down, &scene);
	mlx_mouse_hook(scene.mlx, mouse_handle, &scene);
	mlx_resize_hook(scene.mlx, resize_handle, &scene);
	mlx_loop(scene.mlx);
	printf("END: %f\n", mlx_get_time() - scene.time);
	wait_for_threads(&scene);
	clean_memory(&scene);
	return (0);
}
