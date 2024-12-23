/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:26 by vperez-f          #+#    #+#             */
/*   Updated: 2024/12/24 17:37:50 by vperez-f         ###   ########.fr       */
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

void	close_all(t_scene *scene)
{
	mlx_close_window(scene->mlx);
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

//Euler-Rodrigues rotation formula  || https://en.wikipedia.org/wiki/Rodrigues_rotation_formula
void	rotate_vector(t_vect *vec, t_vect axis, float ang)
{
	t_vect		aux;
	float		cos;

	if (!ang)
		return ;
	aux = vect_cross(axis, *vec);
	cos = cosf(ang);
	*vec = vect_add(
		vect_add(vect_simple_mult(*vec, cos), vect_simple_mult(aux, sinf(ang))),
		vect_simple_mult(axis, vect_dot(*vec, axis) * (1 - cos)));
}

void	rotate_by_angle(t_vect *vect, t_vect *normal, float angle)
{
	t_vect	ideal;
	t_vect	axis;

	if (!angle)
		return ;
	ideal = new_vect(0.0, 0.0, 1.0);
	if (vect_dot(*normal, ideal) == -1.0)
		axis = new_vect(0.0, 1.0, 0.0);
	else
		axis = vect_cross(*normal, ideal);
	if (zero_vect(axis))
		return ;
	axis = unit_vect(axis);
	rotate_vector(vect, axis, angle);
}

void	rotate_x(t_vect *pt, float angle)
{
	float	temp_y;
	float	temp_z;

	temp_y = pt->y;
	temp_z = pt->z;
	pt->y = (temp_y * cos(angle)) + (temp_z * (-sin(angle)));
	pt->z = (temp_y * sin(angle)) + (temp_z * cos(angle));
}

void	rotate_y(t_vect *pt, float angle)
{
	float	temp_x;
	float	temp_z;

	temp_x = pt->x;
	temp_z = pt->z;
	pt->x = (temp_x * cos(angle)) + (temp_z * sin(angle));
	pt->z = (temp_x * (-sin(angle))) + (temp_z * cos(angle));
}

void	rotate_z(t_vect *pt, float angle)
{
	float	temp_x;
	float	temp_y;

	temp_x = pt->x;
	temp_y = pt->y;
	pt->x = (temp_x * cos(angle)) + (temp_y * (-sin(angle)));
	pt->y = (temp_x * sin(angle)) + (temp_y * cos(angle));
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

t_material	new_standard_material(void)
{
	t_material	mat;
	uint32_t	state;

	state = (uint32_t)(mlx_get_time() * 10000);
	mat.color = new_color(fast_rand(&state), fast_rand(&state), fast_rand(&state));
	mat.albedo = mat.color;
	mat.specular = 0.2;
	mat.metal_roughness = 0.1;
	mat.refraction_index = 1.5;
	mat.emission_intensity = 1.0;
	mat.pattern_dim = M_PI / 6;
	mat.pattern = false;
	mat.type = LAMBERTIAN;
	return (mat);
}

t_material	new_standard_plight(void)
{
	t_material	mat;
	uint32_t	state;

	state = (uint32_t)(mlx_get_time() * 10000);
	mat.color = new_color((fast_rand(&state) + 1) / 2, (fast_rand(&state) + 1) / 2, (fast_rand(&state) + 1) / 2);
	mat.albedo = mat.color;
	mat.specular = 1;
	mat.metal_roughness = 1;
	mat.refraction_index = 1;
	mat.emission_intensity = 1;
	mat.pattern_dim = 1;
	mat.pattern = false;
	mat.type = EMISSIVE;
	return (mat);
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

void	set_new_fig_p_light(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_plight();
	fig.p_light.location = *offset_origin;
	fig.p_light.radius_shadow = 1.0;
	init_p_light(scene, fig, mat);
}

void	set_new_fig_cone(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.cone.center = *offset_origin;
	fig.cone.normal = scene->camera.v;
	fig.cone.radius = 0.5;
	fig.cone.height = 2.0;
	init_cone(scene, fig, mat, NULL);
}

void	set_new_fig_cylinder(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.cylinder.center = *offset_origin;
	fig.cylinder.normal = scene->camera.v;
	fig.cylinder.radius = 0.5;
	fig.cylinder.height = 2.0;
	init_cylinder(scene, fig, mat, NULL);
}

void	set_new_fig_disk(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.disk.center = *offset_origin;
	fig.disk.normal = vect_simple_mult(scene->camera.orientation, -1.0);
	fig.disk.radius = 0.5;
	init_disk(scene, fig, mat, NULL);
}

void	set_new_fig_box(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.box.center = *offset_origin;
	fig.box.u_vect = scene->camera.u;
	fig.box.v_vect = scene->camera.v;
	fig.box.dimensions = new_vect(1.0, 1.0, 1.0);
	init_box(scene, fig, mat, NULL);
}

void	set_new_fig_quad(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.quad.center = *offset_origin;
	fig.quad.u_vect = scene->camera.u;
	fig.quad.v_vect = scene->camera.v;
	init_quad(scene, fig, mat, NULL);
}

void	set_new_fig_plane(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.plane.center = *offset_origin;
	fig.plane.normal = vect_simple_mult(scene->camera.orientation, -1.0);
	init_plane(scene, fig, mat, NULL);
}

void	set_new_fig_sphere(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.sphere.center = *offset_origin;
	fig.sphere.radius = 0.5;
	init_sphere(scene, fig, mat, NULL);
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
	filename = ft_itoa((int)(mlx_get_time() * 1000));
	filename = ft_strattach("img/exported/", &filename);
	filename = ft_strappend(&filename, ".ppm");
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		if (access(filename, F_OK))
			throw_err(ERR_NOFILE_MSG, filename, 1);
		else if (access(filename, R_OK))
			throw_err(ERR_PERM_MSG, NULL, 1);
		else
			throw_err(ERR_STD_MSG, NULL, 1);
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
		set_stop_status(scene);
		wait_for_threads(scene);
		scene->stop = false;
		scene->edit_mode = false;
		deselect_objects(scene->objects, scene->lights, &scene->object_selected);
		main_loop(scene);
	}
	else if (is_num_key_down(key_data) || is_copy_delete_key_down(key_data))
	{
		set_stop_status(scene);
		wait_for_threads(scene);
		scene->stop = false;
		manage_world_objects(scene, key_data);
		main_loop(scene);
	}
	else if (is_camera_key_down(key_data))
	{
		set_stop_status(scene);
		wait_for_threads(scene);
		scene->stop = false;
		if (scene->object_selected)
			transform_object(scene->objects, scene->lights, scene, key_data);
		else
		{
			move_camera(&scene->camera, &scene->back_up_camera, scene->sky_sphere, key_data);
			recalculate_view(scene);
		}
		main_loop(scene);
	}
	else if (is_scene_settings_key_down(key_data))
	{
		set_stop_status(scene);
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
		set_stop_status(scene);
		wait_for_threads(scene);
		scene->do_backup = true;
		scene->stop = false;
		if (export_to_ppm(scene->image))
			ft_printf(STDERR_FILENO, "Unexpected error exporting image |--> Resuming render\n");
		main_loop(scene);
	}
	else if (key_data.key == MLX_KEY_E && is_press_and_ctrl(key_data))
	{
		set_stop_status(scene);
		wait_for_threads(scene);
		scene->stop = false;
		scene->edit_mode = true;
		ft_memset(scene->cumulative_image, 0, sizeof(t_vect) * scene->height * scene->width);
		main_loop(scene);
	}
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

bool	shadow_hit(t_scene *scene, t_ray ray, t_hit_info *hit_info, float max)
{
	t_object	*temp;
	float		bounds[2];
	bool		hit;

	hit = false;
	bounds[MIN] = 0.001;
	bounds[MAX] = (float)(INT32_MAX - 10);
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

bool	ray_hit(t_object *objects, t_ray ray, t_hit_info *hit_info, t_object *sky_sphere)
{
	float		bounds[2];
	bool		hit;

	hit = false;
	bounds[MIN] = 0.001;
	if (sky_sphere)
		bounds[MAX] = sky_sphere->figure.sphere.radius;
	else
		bounds[MAX] = (float)(INT32_MAX - 10);
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
	bounds[MAX] = (float)(INT32_MAX - 10);
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

t_color	calc_pixel_color_normal(t_thread *thread, t_scene *scene, t_ray ray)
{
	t_color		color;
	t_hit_info	hit_info;

	if (ray_hit_plus_lights(scene->objects, scene->lights, ray, &hit_info))
	{
		hit_info.point = ray_at(ray, hit_info.t);
		hit_info.normal = hit_info.object->get_normal(&hit_info, &hit_info.object->figure);
		if (hit_info.object->type == LIGHT)
			color = hit_info.object->material.color;
		else
			color = new_color(((hit_info.normal.x + 1) * 0.5), ((hit_info.normal.y + 1) * 0.5), ((hit_info.normal.z + 1) * 0.5));
		if (hit_info.object->selected)
			color = vect_simple_mult(color, 1.5);
		color = vect_simple_div(color, fmaxf((log(hit_info.t) / log(3)), 1.0));
	}
	else
	{
		if (scene->sky_sphere)
			color = get_sky_color(thread, &ray);
		else
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
		if (1e-40 < bound && bound <= 1)
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
			emittance = vect_add(emittance, vect_simple_mult(light->material.color, (test_specular(hit_info, shadow_ray, thread->scene->camera.orientation) * light->material.emission_intensity) * mod2 * 10));			
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
				emittance = vect_add(emittance, vect_simple_mult(temp->material.color, (test_specular(hit_info, shadow_ray, thread->scene->camera.orientation) * temp->material.emission_intensity) * mod2 * 10));
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
	t_color		color;
	t_vect		pixel_offset;

	ray.origin = defocus_sample(thread->scene->camera, thread->state);
	pixel_offset = set_pixel(thread->scene->camera, x, y);
	ray.dir = unit_vect(vect_subtract(pixel_offset, ray.origin));
	color = calc_pixel_color_normal(thread, thread->scene, ray);
	color = clamp_vect(color, 0.0, 1.0);
	safe_pixel_put(thread->scene, x, y, color);
}

void	render_mode(t_thread *thread, uint32_t x, uint32_t y)
{
	t_ray		ray;
	t_color		color;
	t_vect		pixel_offset;
	int			sample_count;

	sample_count = 0;
	color = new_color(0, 0, 0);
	while(sample_count < thread->scene->samples)
	{
		ray.origin = defocus_sample(thread->scene->camera, thread->state);
		pixel_offset = set_pixel_offset(thread->scene->camera, x, y, thread->state);
		ray.dir = unit_vect(vect_subtract(pixel_offset, ray.origin));
		thread->sampled = false;
		color = vect_add(color, calc_pixel_color(thread, ray, thread->scene->max_depth));
		sample_count++;
	}
	color = vect_simple_mult(color, 1 / (float)sample_count);
	progressive_render(thread, x, y, color);
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
		fprintf(stderr, "THREAD: %i || LAP: %i\r", thread->id, thread->iterations);
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
		//set_new_image(scene);
		//mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	}
	scene->time = mlx_get_time();
	init_render(scene);
	//printf("TOT PIX %i || %i\n", scene->height * scene->width, scene->height * scene->width / THREADS);
}

float	rotate_reference_system(t_vect normal, t_vect *vec, t_vect *point)
{
	t_vect	axis;
	t_vect	ideal;
	float	angle;

	angle = 0.0;
	ideal = new_vect(0.0, 0.0, 1.0);
	if (vect_dot(normal, ideal) == -1.0)
		axis = new_vect(0.0, 1.0, 0.0);
	else
		axis = vect_cross(normal, ideal);
	if (zero_vect(axis))
		return (angle);
	axis = unit_vect(axis);
	angle = (acosf(f_clamp(vect_dot(normal, ideal), -1.0, 1.0)));
	if (vec && !zero_vect(*vec))
		rotate_vector(vec, axis, angle);
	if (point && !zero_vect(*point))
		rotate_vector(point, axis, angle);
	return (angle);	
}

void	rotate_texture_normal(t_vect *point_normal, t_vect *normal)
{
	t_vect	axis;
	float	angle;
	t_vect	ideal_normal;

	ideal_normal = new_vect(0.0, 0.0, 1.0);
	axis = vect_cross(ideal_normal, *point_normal);
	if (zero_vect(axis))
		return ;
	axis = unit_vect(axis);
	angle = acosf(f_clamp(vect_dot(ideal_normal, *point_normal), -1.0, 1.0));
	rotate_vector(normal, axis, angle);
}

float	get_height(t_vect point, t_vect center, float base)
{
	t_vect		center_to_point;
	float		point_height;
	float		hypotenuse;

	center_to_point = vect_subtract(point, center);
	hypotenuse = vect_dot(center_to_point, center_to_point);
	point_height = sqrt(fabs(hypotenuse - base * base));
	return (point_height);
}

bool	hit_cylinder_base(t_reference_system *ref_sys, t_figure fig, t_hit_info *internal_hit_info, float *bounds)
{
	t_figure		disk_figure;
	t_vect			base_center;

	ft_bzero(&disk_figure, sizeof(t_figure));
	disk_figure.disk.normal = new_vect(0.0, 0.0, 1.0);
	base_center = new_vect(0.0, 0.0, 0.0);
	base_center.z = ref_sys->center.z + (fig.cylinder.height * 0.5);
	disk_figure.disk.center = base_center;
	disk_figure.disk.radius = fig.cylinder.radius;
	if (!(hit_disk(ref_sys->ray, disk_figure, internal_hit_info, bounds)))
		return (false);
	bounds[MAX] = internal_hit_info->t;
	return (true);
}

bool	cylinder_body_intersections(t_reference_system *ref_sys, t_figure fig, t_eq_params *params)
{
	t_vect		ray_to_cyl;

	ray_to_cyl = vect_subtract(ref_sys->center, ref_sys->ray.origin);
	ray_to_cyl.z = 0;
	params->a = (ref_sys->ray.dir.x * ref_sys->ray.dir.x)
		+ (ref_sys->ray.dir.y * ref_sys->ray.dir.y);
	params->b = -2.0 * ((ref_sys->ray.dir.x * ray_to_cyl.x)
			+ (ref_sys->ray.dir.y * ray_to_cyl.y));
	params->c = (ray_to_cyl.x * ray_to_cyl.x)
		+ (ray_to_cyl.y * ray_to_cyl.y) - (pow(fig.cylinder.radius, 2));
	params->discr = (params->b * params->b)	- (4.0 * params->a * params->c);
	if (params->discr < 0.0)
		return (false);
	params->root = (-params->b - sqrtf(params->discr)) / (2.0 * params->a);
	return (true);
}

bool	hit_cylinder_body(t_reference_system *ref_sys, t_figure fig, t_hit_info *internal_hit_info, float *bounds)
{
	t_eq_params			params;
	t_vect				point;
	float				point_height;

	ft_bzero(&params, sizeof(t_eq_params));
	if (!(cylinder_body_intersections(ref_sys, fig, &params)))
		return (false);
	point = ray_at(ref_sys->ray, params.root);
	point_height = get_height(point, ref_sys->center, fig.cylinder.radius);
	if (params.root <= bounds[MIN] || params.root >= bounds[MAX]
		|| point_height > fig.cylinder.height / 2.0)
	{
		params.root = (-params.b + sqrtf(params.discr)) / (2.0 * params.a);
		point = ray_at(ref_sys->ray, params.root);
		point_height = get_height(point, ref_sys->center, fig.cylinder.radius);
		if (params.root <= bounds[MIN] || params.root >= bounds[MAX]
			|| point_height > fig.cylinder.height / 2.0)
		{
			return (false);
		}
	}
	internal_hit_info->t = params.root;
	internal_hit_info->point = ray_at(ref_sys->ray, internal_hit_info->t);
	bounds[MAX] = internal_hit_info->t;
	return (true);
}

int	belongs_to_base(t_vect point, t_vect center, t_vect normal, float height)
{
	t_vect		top_to_point;
	t_vect		bottom_to_point;
	float		dot_top;
	float		dot_bottom;

	top_to_point = vect_add(center, vect_simple_mult(normal, height));
	top_to_point = vect_subtract(point, top_to_point);
	top_to_point = unit_vect(top_to_point);
	bottom_to_point = vect_subtract(center, vect_simple_mult(normal, height));
	bottom_to_point = vect_subtract(point, bottom_to_point);
	bottom_to_point = unit_vect(bottom_to_point);
	dot_top = vect_dot(normal, top_to_point);
	dot_bottom = vect_dot(normal, bottom_to_point);
	if (fabs(dot_top) > 0.0001 && fabs(dot_bottom) > 0.0001)
		return (0);
	if (fabs(dot_top) < 0.0001)
		return (1);
	else
		return (-1);
}

float	get_point_angle(t_vect *point)
{
	float	angle;
	t_vect	center_to_point;

	center_to_point = *point;
	center_to_point.z = 0;
	center_to_point = unit_vect(center_to_point);
	center_to_point.y = f_clamp(center_to_point.y, -1.0, 1.0);
	angle = acosf(center_to_point.y);
	return (angle);
}

void	rotate_texture_normal_cylinder(t_vect *point, t_vect *normal)
{
	t_vect	point_normal;

	point_normal = *point;
	point_normal.z = 0;
	point_normal = unit_vect(point_normal);
	rotate_texture_normal(&point_normal, normal);
}

void	remove_point_texture_offset_cylinder(t_vect *point, float *arc, t_vect *texture_dims)
{
	if (point->x < 0.0)
		*arc = -*arc + texture_dims->x + (texture_dims->x * (int)(*arc / texture_dims->x));
	if (point->z < 0.0)
		point->z = point->z + texture_dims->y + (texture_dims->y * (int)(fabs(point->z) / texture_dims->y));
	if (*arc >= texture_dims->x)
		*arc = *arc	- (texture_dims->x * (int)(*arc / texture_dims->x));
	if (point->z >= texture_dims->y)
		point->z = point->z	- (texture_dims->y * (int)(point->z / texture_dims->y));
}

void	set_bump_map_normal_cylinder(t_vect *point, t_vect *normal, t_texture *tx, t_figure *fig)
{
	float	arc;
	float	angle;
	t_texel	texel;
	uint8_t	*pixel;
	t_vect	texture_dims;

	texture_dims.x = tx->texture_dim;
	texture_dims.y = tx->texture_dim * (tx->texture->height / (float) tx->texture->width);
	angle = get_point_angle(point);
	arc = angle * fig->cylinder.radius;
	remove_point_texture_offset_cylinder(point, &arc, &texture_dims);
	texel.x = f_clamp(arc * (tx->texture->width / texture_dims.x), 0.0, tx->texture->width - 1);
	texel.y = f_clamp(point->z * (tx->texture->height / texture_dims.y), 0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels + ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
	rotate_texture_normal_cylinder(point, normal);
}

t_vect	get_cylinder_texture(t_hit_info *ht, t_texture *tx, t_figure *fig, int is_base)
{
	float	angle;
	t_vect	axis;
	t_vect	rotated_point;
	t_vect	reverse_normal;
	t_vect	texture_normal;

	rotated_point = vect_subtract(ht->point, fig->cylinder.center);
	reverse_normal = vect_simple_mult(fig->cylinder.normal, -1.0);
	angle = rotate_reference_system(reverse_normal, NULL, &rotated_point);
	if (is_base)
	{
		set_bump_map_normal_base(&rotated_point, &texture_normal, tx, fig->cylinder.radius, (-fig->cylinder.height / 2) * is_base);
		if (is_base == 1)
		{
			axis = new_vect(0.0, 1.0, 0.0);
			rotate_by_angle(&texture_normal, &axis, M_PI);
		}
	}
	else
		set_bump_map_normal_cylinder(&rotated_point, &texture_normal, tx, fig);
	rotate_by_angle(&texture_normal, &reverse_normal, -angle);
	return (texture_normal);
}

t_vect	compute_cylinder_normal(t_figure *fig, t_hit_info *hit_info, int is_base)
{
	float		point_height;
	t_vect		center_offset;
	t_vect		center_to_point;
	t_vect		normal;

	if (is_base == 1)
		normal = fig->cylinder.normal;
	else if (is_base == -1)
		normal = vect_simple_mult(fig->cylinder.normal, -1.0);
	else
	{
		center_to_point = vect_subtract(hit_info->point, fig->cylinder.center);
		point_height = get_height(hit_info->point, fig->cylinder.center, fig->cylinder.radius);
		if (vect_dot(center_to_point, fig->cylinder.normal) < 0.0)
			point_height *= -1;
		center_offset = vect_add(fig->cylinder.center, vect_simple_mult(fig->cylinder.normal, point_height));
		normal = unit_vect(vect_subtract(hit_info->point, center_offset));
	}
	return (normal);
}

t_vect	get_cylinder_normal(t_hit_info *hit_info, t_figure *fig)
{
	int	is_base;

	is_base = belongs_to_base(hit_info->point, fig->cylinder.center, fig->cylinder.normal, fig->cylinder.height * 0.5);
	if (hit_info->object->texture)
	{
		return (get_cylinder_texture(hit_info, hit_info->object->texture, fig, is_base));
	}
	else
	{
		return (compute_cylinder_normal(fig, hit_info, is_base));
	}
}

t_color	get_cylinder_body_pattern(t_hit_info *hit_info)
{
	t_vect			rotated_point;
	t_pattern_vars	p_var;

	rotated_point = vect_subtract(hit_info->point, hit_info->object->figure.cylinder.center);
	rotate_reference_system(hit_info->object->figure.cylinder.normal, NULL, &rotated_point);
	p_var.x_index_square = (int)(fabs(acos(get_vector_arc_height(&rotated_point)) * hit_info->object->figure.cylinder.radius) / hit_info->object->material.pattern_dim);
	p_var.y_index_square = (int)(rotated_point.z / hit_info->object->material.pattern_dim);
	if (rotated_point.x < 0.0)
		p_var.x_index_square++;
	if (rotated_point.z < 0.0)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2) + (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return(hit_info->object->material.color);
	else
		return(vect_simple_div(hit_info->object->material.color, 3.0));	
}

t_vect	get_cylinder_pattern(t_hit_info *ht)
{
	t_figure	base;
	int			is_base;
	t_vect		rotated_point;

	is_base = belongs_to_base(ht->point, ht->object->figure.cylinder.center, ht->object->figure.cylinder.normal, ht->object->figure.cylinder.height / 2);
	if (is_base)
	{
		base.disk.center.y = ht->object->figure.cylinder.height / 2;
		base.disk.radius = ht->object->figure.cylinder.radius;
		rotated_point = vect_subtract(ht->point, ht->object->figure.cylinder.center);
		rotate_reference_system(ht->object->figure.cylinder.normal, NULL, &rotated_point);
		return (get_base_pattern(&rotated_point, &base, ht->object->material.pattern_dim, &ht->object->material.color));
	}
	else
		return (get_cylinder_body_pattern(ht));
}

void	resize_cylinder(t_object *object, t_vect transformation)
{
	object->figure.cylinder.radius *= transformation.x;
	object->figure.cylinder.height *= transformation.y;
	printf("New Cylinder radius: %f\n", object->figure.cylinder.radius);
	printf("New Cylinder height: %f\n\n", object->figure.cylinder.height);
	return ;
}

t_vect	get_origin_cylinder(t_object *object)
{
	return (object->figure.cylinder.center);
}

void	rotate_cylinder(t_object *object, t_camera *camera, t_vect transformation)
{
	if (transformation.x)
		rotate_vector(&object->figure.cylinder.normal, camera->u, transformation.x);
	else if (transformation.y)
		rotate_vector(&object->figure.cylinder.normal, camera->v, transformation.y);
	else if (transformation.z)
		rotate_vector(&object->figure.cylinder.normal, camera->orientation, transformation.z);
	object->figure.cylinder.normal = unit_vect(object->figure.cylinder.normal);
	print_vec_s(object->figure.cylinder.normal, "New Cylinder orientation: ");
	return ;
}

void	translate_cylinder(t_object *object, t_vect transformation)
{
	object->figure.cylinder.center = vect_add(object->figure.cylinder.center, transformation);
	print_vec_s(object->figure.cylinder.center, "New Cylinder center: ");
	return ;
}

bool	hit_cylinder(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	bool				hit;
	t_reference_system 	ref_sys;
	t_hit_info 			internal_hit_info;
	float 				internal_bounds[2];

	hit = false;
	internal_bounds[MIN] = bounds[MIN];
	internal_bounds[MAX] = bounds[MAX];	
	ft_bzero(&internal_hit_info, sizeof(t_hit_info));
	internal_hit_info.normal = new_vect(1.0, 0.0, 0.0);
	ref_sys.ray.origin = vect_subtract(ray.origin, fig.cylinder.center);
	ref_sys.ray.dir = ray.dir;
	ref_sys.center = new_vect(0.0, 0.0, 0.0);
	rotate_reference_system(fig.cylinder.normal, &ref_sys.ray.dir, &ref_sys.ray.origin);
	hit = hit_cylinder_base(&ref_sys, fig, &internal_hit_info, internal_bounds);
	hit |= hit_cylinder_body(&ref_sys, fig, &internal_hit_info, internal_bounds);
	fig.cylinder.height *= -1.0; // change this || figure pointer
	hit |= hit_cylinder_base(&ref_sys, fig, &internal_hit_info, internal_bounds);
	fig.cylinder.height *= -1.0;
	if (hit)
	{
		hit_info->t = internal_hit_info.t;
	}
	return (hit);
}

bool	cone_body_intersections(t_reference_system *ref_sys, t_figure fig, t_eq_params *params)
{
	float		hr_ratio;

	hr_ratio = fig.cone.height / fig.cone.radius;
	params->a = ((hr_ratio * hr_ratio) * ((ref_sys->ray.dir.x * ref_sys->ray.dir.x)
				+ (ref_sys->ray.dir.y * ref_sys->ray.dir.y)))
		- (ref_sys->ray.dir.z * ref_sys->ray.dir.z);
	params->b = 2.0 * (hr_ratio * ((hr_ratio * ref_sys->ray.origin.x * ref_sys->ray.dir.x)
				+ (ref_sys->ray.dir.x * ref_sys->center.x)
				+ (hr_ratio * ref_sys->ray.origin.y * ref_sys->ray.dir.y)
				+ (ref_sys->ray.dir.y * ref_sys->center.y))
			- (ref_sys->ray.origin.z * ref_sys->ray.dir.z)
			- (ref_sys->ray.dir.z * ref_sys->center.z));
	params->c = pow(ref_sys->center.x - (hr_ratio * ref_sys->ray.origin.x), 2)
		+ pow(ref_sys->center.y - (hr_ratio * ref_sys->ray.origin.y), 2)
		- pow(ref_sys->center.z - ref_sys->ray.origin.z, 2);
	params->discr = (params->b * params->b)
		- (4.0 * params->a * params->c);
	if (params->discr < 0.0)
		return (false);
	params->root = (-params->b - sqrt(params->discr))
		/ (2.0 * params->a);
	return (true);
}

bool	hit_cone_body(t_reference_system *ref_sys, t_figure fig, t_hit_info *internal_hit_info, float *bounds)
{
	t_eq_params			params;
	t_vect				point;
	float				point_height;

	ft_bzero(&params, sizeof(t_eq_params));
	if (!(cone_body_intersections(ref_sys, fig, &params)))
		return (false);
	point = ray_at(ref_sys->ray, params.root);
	point_height = point.z;
	if (params.root <= bounds[MIN] || params.root >= bounds[MAX]
		|| fabsf(point_height) > fig.cone.height || point_height < 0.0)
	{
		params.root = (-params.b + sqrtf(params.discr)) / (2.0 * params.a);
		point = ray_at(ref_sys->ray, params.root);
		point_height = point.z;
		if (params.root <= bounds[MIN] || params.root >= bounds[MAX]
			|| fabsf(point_height) > fig.cone.height || point_height < 0.0)
		{
			return (false);
		}
	}
	internal_hit_info->t = params.root;
	internal_hit_info->point = ray_at(ref_sys->ray, internal_hit_info->t);
	bounds[MAX] = internal_hit_info->t;
	return (true);
}

bool	hit_cone_base(t_reference_system *ref_sys, t_figure fig, t_hit_info *internal_hit_info, float *bounds)
{
	t_figure		disk_figure;
	t_vect			base_center;

	ft_bzero(&disk_figure, sizeof(t_figure));
	disk_figure.disk.normal = new_vect(0.0, 0.0, 1.0);
	base_center = new_vect(0.0, 0.0, 0.0);
	base_center.z = ref_sys->center.z + (fig.cone.height);
	disk_figure.disk.center = base_center;
	disk_figure.disk.radius = fig.cone.radius;
	if (!(hit_disk(ref_sys->ray, disk_figure, internal_hit_info, bounds)))
		return (false);
	bounds[MAX] = internal_hit_info->t;
	return (true);
}

float	get_vector_arc_height(t_vect *point)
{
	t_vect	point_arc_vector;

	point_arc_vector = *point;
	point_arc_vector.z = 0.0f;
	point_arc_vector = unit_vect(point_arc_vector);
	return (f_clamp(point_arc_vector.y, -1.0, 1.0));
}

t_vect	get_cone_body_pattern(t_hit_info *hit_info)
{
	t_vect			rotated_point;
	float			point_radius;
	float			point_pattern_dim;
	t_pattern_vars	p_var;

	rotated_point = vect_subtract(hit_info->point, hit_info->object->figure.cone.center);
	rotate_reference_system(hit_info->object->figure.cone.normal, NULL, &rotated_point);
	point_radius = rotated_point.z	* (hit_info->object->figure.cone.radius / hit_info->object->figure.cone.height);
	point_pattern_dim = point_radius * (hit_info->object->material.pattern_dim / hit_info->object->figure.cone.radius);
	p_var.x_index_square = (int)(fabs(acos(get_vector_arc_height(&rotated_point)) * point_radius) / point_pattern_dim);
	p_var.y_index_square = (int)(rotated_point.z / hit_info->object->material.pattern_dim);
	if (rotated_point.x < 0.0)
		p_var.x_index_square++;
	if (rotated_point.z < 0.0)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2) + (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return(hit_info->object->material.color);
	else
		return(vect_simple_div(hit_info->object->material.color, 3.0));	
}

t_vect	get_cone_pattern(t_hit_info *ht)
{
	t_figure	base;
	t_vect		rotated_point;

	if (belongs_to_base(ht->point, ht->object->figure.cone.center, ht->object->figure.cone.normal, ht->object->figure.cone.height))
	{
		base.disk.radius = ht->object->figure.cone.radius;
		base.disk.center.y = ht->object->figure.cone.height;
		base.disk.radius = ht->object->figure.cone.radius;
		rotated_point = vect_subtract(ht->point, ht->object->figure.cone.center);
		rotate_reference_system(ht->object->figure.cone.normal, NULL, &rotated_point);
		return (get_base_pattern(&rotated_point, &base, ht->object->material.pattern_dim, &ht->object->material.color));
	}
	else
		return (get_cone_body_pattern(ht));
}

void	resize_cone(t_object *object, t_vect transformation)
{
	object->figure.cone.radius *= transformation.x;
	object->figure.cone.height *= transformation.y;
	printf("New Cone radius: %f\n", object->figure.cone.radius);
	printf("New Cone height: %f\n\n", object->figure.cone.height);
	return ;
}

t_vect	get_origin_cone(t_object *object)
{
	return (object->figure.cone.center);
}

void	rotate_cone(t_object *object, t_camera *camera, t_vect transformation)
{
	(void)camera;
	t_ray	cone_ray;

	cone_ray = new_ray(object->figure.cone.normal, object->figure.cone.center);
	object->figure.cone.center = ray_at(cone_ray, (object->figure.cone.height / 2));
	if (transformation.x)
	{
		rotate_vector(&object->figure.cone.normal, camera->u, transformation.x);
	}
	else if (transformation.y)
	{
		rotate_vector(&object->figure.cone.normal, camera->v, transformation.y);
	}
	else if (transformation.z)
	{
		rotate_vector(&object->figure.cone.normal, camera->orientation, transformation.z);
	}
	cone_ray = new_ray(object->figure.cone.normal, object->figure.cone.center);
	object->figure.cone.center = ray_at(cone_ray, -(object->figure.cone.height / 2));
	object->figure.cone.normal = unit_vect(object->figure.cone.normal);
	print_vec_s(object->figure.cone.normal, "New Cone orientation: ");
	return ;
}

void	translate_cone(t_object *object, t_vect transformation)
{
	object->figure.cone.center = vect_add(object->figure.cone.center, transformation);
	print_vec_s(object->figure.cone.center, "New Cone center: ");
	return ;
}

t_vect	calculate_ideal_normal(t_vect point, t_figure fig, float *refsys_angle)
{
	float		angle;
	t_vect		res;
	t_vect		axis;
	t_vect		projected;
	t_vect		center_to_point;

	center_to_point = vect_subtract(point, fig.cone.center);
	*refsys_angle = rotate_reference_system(fig.cone.normal,
			NULL, &center_to_point);
	projected = center_to_point;
	projected.z = 0;
	projected = unit_vect(projected);
	axis = vect_cross(center_to_point, projected);
	axis = unit_vect(axis);
	angle = sin(fig.cone.radius
			/ hypot(fig.cone.radius, fig.cone.height));
	rotate_vector(&projected, axis, angle);
	res = unit_vect(projected);
	return (res);
}

t_vect	compute_cone_normal(t_figure *fig, t_hit_info *hit_info, int is_base)
{
	t_vect		ideal;
	t_vect		axis;
	t_vect		normal;
	float		refsys_angle;

	if (is_base == 1)
		normal = fig->cone.normal;
	else
	{
		normal = calculate_ideal_normal(hit_info->point, *fig, &refsys_angle);
		ideal = new_vect(0.0, 0.0, 1.0);
		if (vect_dot(fig->cone.normal, ideal) == -1.0)
			axis = new_vect(0.0, 1.0, 0.0);
		else
			axis = vect_cross(fig->cone.normal, ideal);
		axis = unit_vect(axis);
		rotate_vector(&normal, axis, -refsys_angle);
	}
	return (normal);
}

void	rotate_texture_normal_cone(t_vect *point, t_vect *normal, t_figure *fig)
{
	t_vect	axis;
	float	angle;
	t_vect	point_normal;

	point_normal = *point;
	point_normal.z = 0;
	point_normal = unit_vect(point_normal);
	axis = unit_vect(vect_cross(*point, point_normal));
	angle = sin(fig->cone.radius / hypot(fig->cone.radius, fig->cone.height));
	rotate_vector(&point_normal, axis, angle);
	point_normal = unit_vect(point_normal);
	rotate_texture_normal(&point_normal, normal);
}

void	remove_point_texture_offset_cone(t_vect *point, float *arc, t_vect *texture_dims)
{
	if (point->x < 0.0)
		*arc = -*arc + texture_dims->x + (texture_dims->x * (int)(*arc / texture_dims->x));
	if (point->z < 0.0)
		point->z = point->z + texture_dims->y + (texture_dims->y * (int)(fabs(point->z) / texture_dims->y));
	if (*arc >= texture_dims->x)
		*arc = *arc	- (texture_dims->x * (int)(*arc / texture_dims->x));
	if (point->z >= texture_dims->y)
		point->z = point->z	- (texture_dims->y * (int)(point->z / texture_dims->y));
}

void	set_bump_map_normal_cone(t_vect *point, t_vect *normal, t_texture *tx, t_figure *fig)
{
	float	arc;
	t_texel	texel;
	uint8_t	*pixel;
	t_vect	texture_dims;
	float	point_radius;

	point_radius = point->z * (fig->cone.radius / fig->cone.height);
	texture_dims.x = tx->texture_dim * (point_radius / fig->cone.radius);
	texture_dims.y = tx->texture_dim * (tx->texture->height / (float) tx->texture->width);
	arc = get_point_angle(point) * point_radius;
	remove_point_texture_offset_cone(point, &arc, &texture_dims);
	texel.x = f_clamp(arc * (tx->texture->width / texture_dims.x), 0.0, tx->texture->width - 1);
	texel.y = f_clamp(point->z * (tx->texture->height / texture_dims.y), 0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels + ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
	rotate_texture_normal_cone(point, normal, fig);
}

t_vect	get_cone_texture(t_hit_info *ht, t_texture *tx, t_figure *fig, int is_base)
{
	float	angle;
	t_vect	rotated_point;
	t_vect	texture_normal;

	rotated_point = vect_subtract(ht->point, fig->cone.center);
	angle = rotate_reference_system(fig->cone.normal, NULL, &rotated_point);
	if (is_base)
		set_bump_map_normal_base(&rotated_point, &texture_normal, tx, fig->cone.radius, fig->cone.height);
	else
		set_bump_map_normal_cone(&rotated_point, &texture_normal, tx, fig);
	rotate_by_angle(&texture_normal, &fig->cone.normal, -angle);
	return (texture_normal);
}

t_vect	get_cone_normal(t_hit_info *hit_info, t_figure *fig)
{
	int	is_base;

	is_base = belongs_to_base(hit_info->point, fig->cone.center, fig->cone.normal, fig->cone.height);
	if (hit_info->object->texture)
	{
		return (get_cone_texture(hit_info, hit_info->object->texture, fig, is_base));
	}
	else
	{
		return (compute_cone_normal(fig, hit_info, is_base));
	}
}

bool	hit_cone(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	t_reference_system 	ref_sys;
	t_hit_info 			internal_hit_info;
	float 				internal_bounds[2];
	bool				hit;

	hit = false;
	internal_bounds[MIN] = bounds[MIN];
	internal_bounds[MAX] = bounds[MAX];	
	ft_bzero(&internal_hit_info, sizeof(t_hit_info));
	internal_hit_info.normal = new_vect(1.0, 0.0, 0.0);
	ref_sys.ray.origin = vect_subtract(ray.origin, fig.cone.center);
	ref_sys.ray.dir = ray.dir;
	ref_sys.center = new_vect(0.0, 0.0, 0.0);
	rotate_reference_system(fig.cone.normal, &ref_sys.ray.dir, &ref_sys.ray.origin);
	hit = hit_cone_base(&ref_sys, fig, &internal_hit_info, internal_bounds);
	hit |= hit_cone_body(&ref_sys, fig, &internal_hit_info, internal_bounds);
	if (hit)
	{
		hit_info->t = internal_hit_info.t;
	}
	return (hit);
}

void	set_base_params(t_base_params *params, t_vect *point, float radius)
{
	params->point_to_base = *point;
	params->point_to_base.z = 0.0;
	params->point_radius = vect_length(params->point_to_base);
	params->point_to_base = unit_vect(params->point_to_base);
	params->point_to_base = clamp_vect(params->point_to_base, -1.0, 1.0);
	params->point_arc = acosf(params->point_to_base.y) * params->point_radius;
	params->base_height = radius - params->point_radius;
}

void	remove_point_texture_offset_disk(t_vect *point, t_vect *texture_dims, float *point_arc, float base_height)
{
	if (point->x < 0.0)
	{
		*point_arc = (-1 * (*point_arc)) + texture_dims->x + (texture_dims->x * (int)(*point_arc / texture_dims->x));
	}
	if (*point_arc >= texture_dims->x)
	{
		*point_arc = *point_arc - (texture_dims->x * (int)(*point_arc / texture_dims->x));
	}
	if (0.0 < texture_dims->y)
	{
		point->z = base_height;
	}
	if (base_height >= texture_dims->y)
	{
		point->z = (base_height) - (texture_dims->y * (int)((base_height) / texture_dims->y));
	}
}

void	remove_point_texture_offset_base(t_vect *point,	t_vect *texture_dims, t_base_params *bp, float base_distance)
{
	if (point->x < 0.0)
		bp->point_arc = -bp->point_arc + texture_dims->x
			+ (texture_dims->x * (int)(bp->point_arc / texture_dims->x));
	if (bp->point_arc >= texture_dims->x)
		bp->point_arc = bp->point_arc
			- (texture_dims->x * (int)(bp->point_arc / texture_dims->x));
	if (base_distance < 0.0)
		point->z = (base_distance - bp->base_height)
			+ texture_dims->y
			+ (texture_dims->y * (int)((fabs(base_distance)
						+ bp->base_height) / texture_dims->y));
	if (base_distance >= 0.0
		&& base_distance < texture_dims->y)
		point->z = base_distance + bp->base_height;
	if (base_distance >= 0.0
		&& base_distance + bp->base_height >= texture_dims->y)
		point->z = (base_distance + bp->base_height)
			- (texture_dims->y * (int)((base_distance
						+ bp->base_height) / texture_dims->y));
}

void	set_bump_map_normal_base(t_vect *point, t_vect *normal, t_texture *tx, float radius, float base_distance)
{
	t_base_params	bp;
	t_texel			texel;
	uint8_t			*pixel;
	t_vect			texture_dims;

	set_base_params(&bp, point, radius);
	texture_dims.x = tx->texture_dim * (bp.point_radius / radius);
	texture_dims.y = tx->texture_dim * (tx->texture->height / (float) tx->texture->width);
	remove_point_texture_offset_base(point, &texture_dims, &bp, base_distance);
	texel.x = f_clamp(bp.point_arc * (tx->texture->width / texture_dims.x), 0.0, tx->texture->width - 1);
	texel.y = f_clamp(point->z * (tx->texture->height / texture_dims.y), 0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels + ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
}

void	set_bump_map_normal_disk(t_figure *fig, t_vect *point, t_vect *normal, t_texture *tx)
{
	t_base_params	bp;
	t_texel			texel;
	uint8_t			*pixel;
	t_vect			texture_dims;

	set_base_params(&bp, point, fig->disk.radius);
	texture_dims.x = tx->texture_dim * (bp.point_radius / fig->disk.radius);
	texture_dims.y = tx->texture_dim * (tx->texture->height / (float)tx->texture->width);
	remove_point_texture_offset_disk(point, &texture_dims, &bp.point_arc, bp.base_height);
	texel.x = f_clamp(bp.point_arc * (tx->texture->width / texture_dims.x), 0.0, tx->texture->width - 1);
	texel.y = f_clamp(point->z * (tx->texture->height / texture_dims.y), 0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels	+ ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
}

t_vect	get_disk_texture(t_hit_info *hit_info, t_texture *tx, t_figure *fig)
{
	float			angle;
	t_vect			rotated_point;
	t_vect			texture_normal;

	rotated_point = vect_subtract(hit_info->point, fig->disk.center);
	angle = rotate_reference_system(fig->disk.normal, NULL, &rotated_point);
	set_bump_map_normal_disk(fig, &rotated_point, &texture_normal, tx);
	rotate_by_angle(&texture_normal, &fig->disk.normal, -angle);
	return (texture_normal);
}

t_vect	get_base_pattern(t_vect *point, t_figure *figure, float pattern_dim, t_color *obj_color)
{	
	t_pattern_vars	p_var;
	t_base_params	bp;
	float			point_pattern_dim;

	set_base_params(&bp, point, figure->disk.radius);
	point_pattern_dim = bp.point_radius * (pattern_dim / figure->disk.radius);
	p_var.x_index_square = (int)(fabs(bp.point_arc)/ point_pattern_dim);
	p_var.y_index_square = (int)((fabs(bp.base_height) + figure->disk.center.y)  / pattern_dim);
	if (point->x > 0.0)
		p_var.x_index_square++;
	if (point->z > 0.0 && fabs(point->z) > 0.0001)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2) + (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return(*obj_color);
	else
		return(vect_simple_div(*obj_color, 3.0));
}

t_vect	get_disk_pattern(t_hit_info *hit_info)
{	
	t_base_params	bp;
	t_pattern_vars	p_var;
	t_vect			rotated_point;
	float			point_pattern_dim;

	rotated_point = vect_subtract(hit_info->point, hit_info->object->figure.disk.center);
	rotate_reference_system(hit_info->object->figure.disk.normal, NULL, &rotated_point);
	set_base_params(&bp, &rotated_point, hit_info->object->figure.disk.radius);
	point_pattern_dim = bp.point_radius * (hit_info->object->material.pattern_dim / hit_info->object->figure.disk.radius);
	p_var.x_index_square = (int)(fabs(bp.point_arc)/ point_pattern_dim);
	p_var.y_index_square = (int)(fabs(bp.base_height) / hit_info->object->material.pattern_dim);
	if (rotated_point.x > 0.0)
		p_var.x_index_square++;
	if (rotated_point.z > 0.0 && fabs(rotated_point.z) > 0.0001)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2) + (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return(hit_info->object->material.color);
	else
		return(vect_simple_div(hit_info->object->material.color, 3.0));
}

void	resize_disk(t_object *object, t_vect transformation)
{
	object->figure.disk.radius *= transformation.x;
	printf("New Disk radius: %f\n\n", object->figure.disk.radius);
	return ;
}

t_vect	get_origin_disk(t_object *object)
{
	return (object->figure.disk.center);
}

void	rotate_disk(t_object *object, t_camera *camera, t_vect transformation)
{
	if (transformation.x)
		rotate_vector(&object->figure.disk.normal, camera->u, transformation.x);
	else if (transformation.y)
		rotate_vector(&object->figure.disk.normal, camera->v, transformation.y);
	else if (transformation.z)
		rotate_vector(&object->figure.disk.normal, camera->orientation, transformation.z);
	object->figure.disk.normal = unit_vect(object->figure.disk.normal);
	print_vec_s(object->figure.disk.normal, "New Disk orientation: ");
	return ;
}

void	translate_disk(t_object *object, t_vect transformation)
{
	object->figure.disk.center = vect_add(object->figure.disk.center, transformation);
	print_vec_s(object->figure.disk.center, "New Disk center: ");
	return ;
}

t_vect	get_disk_normal(t_hit_info *hit_info, t_figure *fig)
{
	if (hit_info->object->texture)
	{
		return (get_disk_texture(hit_info, hit_info->object->texture, fig));
	}
	else
	{
		return (fig->disk.normal);
	}
}

bool	hit_disk(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	float	denominator;
	float	root;
	float	q;
	t_vect	hit_origin;

	denominator = vect_dot(fig.disk.normal, ray.dir);
	if (fabs(denominator) < 1e-8)
		return (false);
	q = vect_dot(fig.disk.center, fig.disk.normal);
	root = (q - vect_dot(ray.origin, fig.disk.normal)) / denominator;
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
	return (true);	
}

int	correct_box_pattern_index(t_vect *dimensions, int face_index, int pattern_index)
{
	if ((face_index == 2 || face_index == 3))
	{
		if (!((int)((dimensions->z - 0.0001) / 2) % 2))
			pattern_index = !pattern_index;
		if (((int)((dimensions->x - 0.0001) / 2) % 2))
			pattern_index = !pattern_index;		
	}
	if ((face_index == 4 || face_index == 5))
	{
		if (((int)((dimensions->z - 0.0001) / 2) % 2))
			pattern_index = !pattern_index;
		if (((int)((dimensions->y - 0.0001) / 2) % 2))
			pattern_index = !pattern_index;
	}
	return (pattern_index);
}

t_vect	get_rotated_point_quad(t_hit_info *hit_info)
{
	t_vect	axis;
	float	angle;
	t_vect	rotated_point;
	t_vect	u_vect_rotated;

	u_vect_rotated = unit_vect(hit_info->object->figure.quad.u_vect);
	rotated_point = vect_subtract(hit_info->point, hit_info->object->figure.quad.center);
	rotate_reference_system(hit_info->object->figure.quad.normal, &u_vect_rotated, &rotated_point);
	u_vect_rotated = clamp_vect(u_vect_rotated, -1.0, 1.0);
	axis = new_vect(0.0, 0.0, 1.0);
	angle = acos(-u_vect_rotated.x);
	if (u_vect_rotated.y > 0.0)
		rotate_vector(&rotated_point, axis, angle);
	else if (u_vect_rotated.y < 0.0)
		rotate_vector(&rotated_point, axis, -angle);
	rotated_point.x = round(rotated_point.x * 10000.0) / 10000.0;
	rotated_point.y = round(rotated_point.y * 10000.0) / 10000.0;
	rotated_point.z = round(rotated_point.z * 10000.0) / 10000.0;
	return (rotated_point);
}

t_vect	get_quad_texture(t_hit_info *hit_info, t_texture *tx, t_figure *fig)
{
	float	angle;
	float	aux_angle;
	t_vect	texture_normal;
	t_vect	rotated_point;
	t_vect	u_vect_rotated;

	u_vect_rotated = unit_vect(fig->quad.u_vect);
	rotate_reference_system(fig->quad.normal, &u_vect_rotated, NULL);
	u_vect_rotated = clamp_vect(u_vect_rotated, -1.0, 1.0);
	if (u_vect_rotated.y > 0.0)
		aux_angle = acos(-u_vect_rotated.x);
	else if (u_vect_rotated.y < 0.0)
		aux_angle = -acos(-u_vect_rotated.x);
	else
		aux_angle = 0.0;
	rotated_point = get_rotated_point_quad(hit_info);
	angle = rotate_reference_system(fig->quad.normal, NULL, NULL);
	set_bump_map_normal_plane(&rotated_point, tx, &texture_normal);
	rotate_vector(&texture_normal, new_vect(0.0, 0.0, 1.0), -aux_angle);
	rotate_by_angle(&texture_normal, &fig->quad.normal, -angle);
	return (texture_normal);
}

t_vect	get_face_pattern(t_hit_info *hit_info, t_vect *dimensions, int face_index)
{
	t_pattern_vars	p_var;
	t_vect			rotated_point;

	rotated_point = get_rotated_point_quad(hit_info);
	p_var.x_index_square = (int)(fabs(rotated_point.x) / hit_info->object->material.pattern_dim);
	p_var.y_index_square = (int)(fabs(rotated_point.y) / hit_info->object->material.pattern_dim);
	if (rotated_point.x < 0.0)
		p_var.x_index_square++;
	if (rotated_point.y < 0.0)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2) + (p_var.y_index_square % 2)) % 2;
	p_var.pattern_index = correct_box_pattern_index(dimensions, face_index, p_var.pattern_index);
	if (p_var.pattern_index == 0)
		return(hit_info->object->material.color);
	else
		return(vect_simple_div(hit_info->object->material.color, 3.0));
}

t_vect	get_quad_pattern(t_hit_info *hit_info)
{
	t_vect	rotated_point;

	rotated_point = get_rotated_point_quad(hit_info);
	return (get_plane_pattern_color(&rotated_point, hit_info->object->material.pattern_dim, &hit_info->object->material.color));
}

void	resize_quad(t_object *object, t_vect transformation)
{
	object->figure.quad.u_vect = vect_simple_mult(object->figure.quad.u_vect, transformation.x);
	object->figure.quad.v_vect = vect_simple_mult(object->figure.quad.v_vect, transformation.x);
	return ;
}

t_vect	get_origin_quad(t_object *object)
{
	return (object->figure.quad.center);
}

void	rotate_quad(t_object *object, t_camera *camera, t_vect transformation)
{
	if (transformation.x)
	{
		rotate_vector(&object->figure.quad.u_vect, camera->u, transformation.x);
		rotate_vector(&object->figure.quad.v_vect, camera->u, transformation.x);
	}
	else if (transformation.y)
	{
		rotate_vector(&object->figure.quad.u_vect, camera->v, transformation.y);
		rotate_vector(&object->figure.quad.v_vect, camera->v, transformation.y);
	}
	else if (transformation.z)
	{
		rotate_vector(&object->figure.quad.u_vect, camera->orientation, transformation.z);
		rotate_vector(&object->figure.quad.v_vect, camera->orientation, transformation.z);
	}
	object->figure.quad.normal = unit_vect(vect_cross(object->figure.quad.u_vect, object->figure.quad.v_vect));
	print_vec_s(object->figure.quad.normal, "New Quad orientation: ");
	return ;
}

void	translate_quad(t_object *object, t_vect transformation)
{
	object->figure.quad.center = vect_add(object->figure.quad.center, transformation);
	print_vec_s(object->figure.quad.center, "New Quad center: ");
	return ;
}

t_vect	get_quad_normal(t_hit_info *hit_info, t_figure *fig)
{
	if (hit_info->object->texture)
	{
		return (get_quad_texture(hit_info, hit_info->object->texture, fig));
	}
	else
	{
		return (fig->quad.normal);
	}
}

bool	hit_quad(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	t_eq_params	params;
	t_vect		hit_origin;
	t_vect		n;
	t_vect		w;

	n = vect_cross(fig.quad.u_vect, fig.quad.v_vect);
	w = vect_simple_div(n, vect_dot(n, n));
	params.c = vect_dot(fig.quad.normal, ray.dir);
	if (fabs(params.c) < 1e-8)
		return (false);
	params.root = ((vect_dot(fig.quad.normal, fig.quad.center)) - vect_dot(ray.origin, fig.quad.normal)) / params.c;
	if (params.root <= bounds[MIN] || bounds[MAX] <= params.root)
	{
		return (false);
	}
	hit_origin = vect_subtract(ray_at(ray, params.root), fig.quad.center);
	params.a = vect_dot(w, vect_cross(hit_origin, fig.quad.v_vect));
	params.b = vect_dot(w, vect_cross(fig.quad.u_vect, hit_origin));
	if ((params.a > 0.5 || params.a < -0.5) || (params.b > 0.5 || params.b < -0.5))
	{
		return (false);
	}
	hit_info->t = params.root;
	return (true);
}

t_object	*get_box_face(t_hit_info *hit_info, int *face_index)
{
	t_vect		compare_vect;
	t_vect		normal;
	t_object	*face;

	face = hit_info->object->figure.box.faces;
	while (face)
	{
		compare_vect = vect_subtract(hit_info->point, face->get_origin(face));
		normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
		if (fabsf(vect_dot(compare_vect, normal)) < 1e-4)
		{
			return (face);
		}
		if (face_index)
			(*face_index)++;
		face = face->next;
	}
	return (NULL);
}

t_vect	get_box_pattern(t_hit_info *hit_info)
{
	int			face_index;
	t_hit_info	face_hit_info;

	face_index = 0;
	if (hit_info->object->material.pattern)
	{
		face_hit_info = *hit_info;
		face_hit_info.object = get_box_face(hit_info, &face_index);
		face_hit_info.object->material.color = hit_info->object->material.color;
		if (face_hit_info.object)
			return (get_face_pattern(&face_hit_info, &hit_info->object->figure.box.dimensions, face_index));
		else
			return (hit_info->object->material.color);
	}
	else
	{
		return (hit_info->object->material.color);
	}
}

void	resize_box(t_object *object, t_vect transformation)
{
	object->figure.box.dimensions = vect_mult(object->figure.box.dimensions, transformation);
	recalculate_faces(object, object->figure.box.dimensions);
	print_vec_s(object->figure.box.dimensions, "New Box dimensions: ");
	return ;
}

t_vect	get_origin_box(t_object *object)
{
	return (object->figure.box.center);
}

void	rotate_box(t_object *object, t_camera *camera, t_vect transformation)
{
	if (transformation.x)
	{
		rotate_vector(&object->figure.box.u_vect, camera->u, transformation.x);
		rotate_vector(&object->figure.box.v_vect, camera->u, transformation.x);
	}
	else if (transformation.y)
	{
		rotate_vector(&object->figure.box.u_vect, camera->v, transformation.y);
		rotate_vector(&object->figure.box.v_vect, camera->v, transformation.y);
	}
	else if (transformation.z)
	{
		rotate_vector(&object->figure.box.u_vect, camera->orientation, transformation.z);
		rotate_vector(&object->figure.box.v_vect, camera->orientation, transformation.z);
	}
	recalculate_faces(object, object->figure.box.dimensions);
	print_vec_s(vect_cross(object->figure.box.u_vect, object->figure.box.v_vect), "New Box orientation: ");
	return ;
}

void	translate_box(t_object *object, t_vect transformation)
{
	t_object	*face;

	face = object->figure.box.faces;
	object->figure.box.center = vect_add(object->figure.box.center, transformation);
	while (face)
	{
		translate_quad(face, transformation);
		face = face->next;
	}
	print_vec_s(object->figure.box.center, "New Box center: ");
	return ;
}

t_vect	get_box_normal(t_hit_info *hit_info, t_figure *fig)
{
	t_hit_info	face_hit_info;

	(void)fig;
	face_hit_info = *hit_info;
	face_hit_info.object = get_box_face(hit_info, NULL);
	return (face_hit_info.object->get_normal(&face_hit_info, &face_hit_info.object->figure));
}

bool	hit_box(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	t_hit_info	internal_hit_info;

	if (ray_hit(fig.box.faces, ray, &internal_hit_info, NULL))
	{
		if (internal_hit_info.t <= bounds[MIN] || bounds[MAX] <= internal_hit_info.t)
			return (false);
		hit_info->t = internal_hit_info.t;
		return (true);
	}
	return (false);
}

void	remove_point_texture_offset_plane(t_vect *point, t_vect *texture_dims)
{
	if (point->x < 0.0)
		point->x = point->x + texture_dims->x
			+ (texture_dims->x * (int)(fabs(point->x / texture_dims->x)));
	if (point->y > 0.0)
		point->y = point->y - texture_dims->y
			- (texture_dims->y * (int)(point->y / texture_dims->y));
	if (point->x >= texture_dims->x)
		point->x = point->x
			- (texture_dims->x * (int)(point->x / texture_dims->x));
	if (fabs(point->y) >= texture_dims->y)
		point->y = point->y
			+ (texture_dims->y * (int)(fabs(point->y) / texture_dims->y));
}

void	set_bump_map_normal_plane(t_vect *point, t_texture *tx, t_vect *normal)
{
	t_texel		texel;
	uint8_t		*pixel;
	t_vect		texture_dims;

	texture_dims.x = tx->texture_dim;
	texture_dims.y = tx->texture_dim * (tx->texture->height / (float) tx->texture->width);
	remove_point_texture_offset_plane(point, &texture_dims);
	texel.x = f_clamp(point->x * (tx->texture->width / texture_dims.x), 0.0, tx->texture->width - 1);
	texel.y = f_clamp(fabs(point->y) * (tx->texture->height / texture_dims.y), 0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels	+ ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
}

t_vect	get_plane_texture(t_hit_info *hit_info, t_texture *tx, t_figure *fig)
{
	float	angle;
	t_vect	texture_normal;
	t_vect	rotated_point;

	rotated_point = vect_subtract(hit_info->point, fig->plane.center);
	angle = rotate_reference_system(fig->plane.normal, NULL, &rotated_point);
	set_bump_map_normal_plane(&rotated_point, tx, &texture_normal);
	rotate_by_angle(&texture_normal, &fig->plane.normal, -angle);
	return (texture_normal);
}

t_vect	get_plane_pattern_color(t_vect *rotated_point, float pattern_dim, t_vect *material_color)
{
	t_pattern_vars	p_var;

	p_var.x_index_square = (int)(fabs(rotated_point->x) / pattern_dim);
	p_var.y_index_square = (int)(fabs(rotated_point->y) / pattern_dim);
	if (rotated_point->x < 0.0)
		p_var.x_index_square++;
	if (rotated_point->y < 0.0)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2) + (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return (*material_color);
	else
		return (vect_simple_div(*material_color, 3.0));	
}

t_vect	get_plane_pattern(t_hit_info *hit_info)
{
	t_vect	rotated_point;

	rotated_point = vect_subtract(hit_info->point, hit_info->object->figure.plane.center);
	rotate_reference_system(hit_info->object->figure.plane.normal, NULL, &rotated_point);
	return (get_plane_pattern_color(&rotated_point, hit_info->object->material.pattern_dim, &hit_info->object->material.color));
}

t_vect	get_obj_color(t_hit_info *hit_info)
{
	if (hit_info->object->material.pattern)
		return (hit_info->object->get_visual(hit_info));
	else
		return (hit_info->object->material.color);
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

void	rotate_plane(t_object *object, t_camera *camera, t_vect transformation)
{
	if (transformation.x)
		rotate_vector(&object->figure.plane.normal, camera->u, transformation.x);
	else if (transformation.y)
		rotate_vector(&object->figure.plane.normal, camera->v, transformation.y);
	else if (transformation.z)
		rotate_vector(&object->figure.plane.normal, camera->orientation, transformation.z);
	object->figure.plane.normal = unit_vect(object->figure.plane.normal);
	print_vec_s(object->figure.plane.normal, "New Plane orientation: ");
	return ;
}

void	translate_plane(t_object *object, t_vect transformation)
{
	object->figure.plane.center = vect_add(object->figure.plane.center, transformation);
	print_vec_s(object->figure.plane.center, "New Plane center: ");
	return ;
}

t_vect	get_plane_normal(t_hit_info *hit_info, t_figure *fig)
{
	if (hit_info->object->texture)
	{

		return (get_plane_texture(hit_info, hit_info->object->texture, fig));
	}
	else
	{
		return (fig->plane.normal);
	}
}

bool	hit_plane(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	float	denominator;
	float	root;
	t_vect	point;

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
	return (true);	
}

void	remove_point_texture_offset_sphere(t_vect *point, float *polar_coords, t_vect *texture_dims)
{
	if (point->x < 0.0)
		polar_coords[LATITUDE] = -polar_coords[LATITUDE] + texture_dims->x
			+ (texture_dims->x * (int)(polar_coords[LATITUDE] / texture_dims->x));
	if (point->y > 0.0)
		polar_coords[LONGITUDE] = -polar_coords[LONGITUDE] + texture_dims->y
			+ (texture_dims->y * (int)(polar_coords[LONGITUDE] / texture_dims->y));
	if (polar_coords[LATITUDE] >= texture_dims->x)
		polar_coords[LATITUDE] = polar_coords[LATITUDE]
			- (texture_dims->x * (int)(polar_coords[LATITUDE] / texture_dims->x));
	if (polar_coords[LONGITUDE] >= texture_dims->y)
		polar_coords[LONGITUDE] = polar_coords[LONGITUDE]
			- (texture_dims->y * (int)(polar_coords[LONGITUDE] / texture_dims->y));
}

void	rotate_texture_normal_sphere(t_vect *point, t_vect *normal)
{
	t_vect	point_normal;

	point_normal = unit_vect(*point);
	rotate_texture_normal(&point_normal, normal);
}

t_vect	translate_texture_to_normal(uint8_t *pixel)
{
	t_vect	normal;
	t_color	pixel_color;

	pixel_color.x = *pixel / (float) 255;
	pixel_color.y = *(pixel + 1) / (float) 255;
	pixel_color.z = *(pixel + 2) / (float) 255;
	normal.x = (pixel_color.x / 0.5) - 1;
	normal.y = (pixel_color.y / 0.5) - 1;
	normal.z = (pixel_color.z / 0.5) - 1;
	return (normal);
}

void	set_bump_map_normal_sphere(t_hit_info *hit_info, t_vect *point, t_texture *tx, t_vect *normal)
{
	t_texel	texel;
	uint8_t	*pixel;
	float	point_radius;
	t_vect	texture_dims;
	float	polar_coord[2];

	set_polar_coords(point, &hit_info->object->figure, polar_coord);
	point_radius = sqrtf(pow(point->x, 2) + pow(point->z, 2));
	texture_dims.x = tx->texture_dim * (point_radius / hit_info->object->figure.sphere.radius);
	texture_dims.y = tx->texture_dim * (tx->texture->height / (float)tx->texture->width);
	remove_point_texture_offset_sphere(point, polar_coord, &texture_dims);
	texel.x = f_clamp(polar_coord[LATITUDE] * (tx->texture->width / texture_dims.x), 0.0, tx->texture->width - 1);
	texel.y = f_clamp(polar_coord[LONGITUDE] * (tx->texture->height/ texture_dims.y), 0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels	+ ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
	rotate_texture_normal_sphere(point, normal);
}

t_vect	get_sphere_texture(t_hit_info *hit_info, t_texture *texture)
{
	t_vect	texture_normal;
	t_vect	translated_point;

	translated_point = vect_subtract(hit_info->point, hit_info->object->figure.sphere.center);
	set_bump_map_normal_sphere(hit_info, &translated_point, texture, &texture_normal);
	return (texture_normal);
}

void	set_polar_coords(t_vect *point, t_figure *fig, float *polar_coords)
{
	float		projected_radius;
	t_vect		point_normal;
	t_vect		latitude_normal;

	point_normal = *point;
	latitude_normal = *point;
	latitude_normal.y = 0.0;
	latitude_normal = unit_vect(latitude_normal);
	point_normal = unit_vect(point_normal);
	projected_radius = sqrtf(pow(point->x, 2) + pow(point->z, 2));
	polar_coords[LATITUDE] = acosf(f_clamp(latitude_normal.z, -1.0, 1.0)) * projected_radius;
	polar_coords[LONGITUDE] = acosf(f_clamp(vect_dot(point_normal, latitude_normal), -1.0, 1.0)) * fig->sphere.radius;
}

t_vect	get_sphere_pattern(t_hit_info *hit_info)
{
	t_vect			point;
	t_pattern_vars	p_var;
	float			polar_coords[2];
	float			projected_pattern;

	point = vect_subtract(hit_info->point, hit_info->object->figure.sphere.center);
	set_polar_coords(&point, &hit_info->object->figure, polar_coords);
	projected_pattern = sqrtf(pow(point.x, 2) + pow(point.z, 2)) * ((M_PI / 8) / hit_info->object->figure.sphere.radius); // Pattern-dim / radius
	p_var.x_index_square = (int)(fabs(polar_coords[LATITUDE]) / projected_pattern);
	p_var.y_index_square = (int)(fabs(polar_coords[LONGITUDE]) / (M_PI / 8));
	if (point.x < 0.0)
		p_var.x_index_square++;
	if (point.y < 0.0)
		p_var.y_index_square++;
	p_var.pattern_index = ((p_var.x_index_square % 2) + (p_var.y_index_square % 2)) % 2;
	if (p_var.pattern_index == 0)
		return(hit_info->object->material.color);
	else
		return(vect_simple_div(hit_info->object->material.color, 3.0));
}

void	resize_sphere(t_object *object, t_vect transformation)
{
	object->figure.sphere.radius *= transformation.x;
	printf("New sphere radius: %f\n", object->figure.sphere.radius);
	return ;
}

t_vect	get_origin_sphere(t_object *object)
{
	return (object->figure.sphere.center);
}

void	rotate_sphere(t_object *object, t_camera *camera, t_vect transformation)
{
	(void)object;
	(void)transformation;
	(void)camera;
	return ;
}

void	translate_sphere(t_object *object, t_vect transformation)
{
	object->figure.sphere.center = vect_add(object->figure.sphere.center, transformation);
	print_vec_s(object->figure.sphere.center, "New Sphere center: ");
	return ;
}

t_vect	get_sphere_normal(t_hit_info *hit_info, t_figure *fig)
{
	if (hit_info->object->texture)
	{
		return (get_sphere_texture(hit_info, hit_info->object->texture));
	}
	else
	{
		return (vect_simple_div(vect_subtract(hit_info->point, fig->sphere.center), fig->sphere.radius));
	}
}

bool	hit_sphere(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	t_vect		oc;
	t_eq_params	params;
	float		sqrt_disc;

	oc = vect_subtract(fig.sphere.center, ray.origin);
	params.a = vect_dot(ray.dir, ray.dir);
	params.b = vect_dot(ray.dir, oc);
	params.c = vect_dot(oc, oc) - (fig.sphere.radius * fig.sphere.radius);
	params.discr = (params.b * params.b) - (params.a * params.c);
	if (params.discr < 0)
		return (false);
	sqrt_disc = sqrtf(params.discr); 
	params.root = (params.b - sqrt_disc) / params.a;
	if (params.root <= bounds[MIN] || bounds[MAX] <= params.root)
	{
		params.root = (params.b + sqrt_disc) / params.a;
		if (params.root <= bounds[MIN] || bounds[MAX] <= params.root)
			return (false);
	}
	hit_info->t = params.root;
	return (true);	
}

t_vect	get_light_normal(t_hit_info *hit_info, t_figure *fig)
{
	(void)hit_info;
	(void)fig;
	return(new_vect(0.0, 1.0, 0.0));
}

t_vect	get_light_pattern(t_hit_info *hit_info)
{
	return (hit_info->object->material.color);
}

void	resize_point_light(t_object *object, t_vect transformation)
{
	object->figure.p_light.radius_shadow *= transformation.x;
	printf("New Point Light radius: %f\n", object->figure.p_light.radius_shadow);
	return ;
}

t_vect	get_origin_point_light(t_object *object)
{
	return (object->figure.p_light.location);
}

void	translate_point_light(t_object *object, t_vect transformation)
{
	object->figure.p_light.location = vect_add(object->figure.p_light.location, transformation);
	print_vec_s(object->figure.p_light.location, "New Point Light center: ");
	return ;
}

bool	hit_point_light(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	t_eq_params	params;
	t_vect		oc;
	float		sqrt_disc;

	oc = vect_subtract(fig.p_light.location, ray.origin);
	params.a = vect_dot(ray.dir, ray.dir);
	params.b = vect_dot(ray.dir, oc);
	params.c = vect_dot(oc, oc) - (0.2 * 0.2);
	params.discr = (params.b * params.b) - (params.a * params.c);
	if (params.discr < 0)
		return (false);
	sqrt_disc = sqrtf(params.discr); 
	params.root = (params.b - sqrt_disc) / params.a;
	if (params.root <= bounds[MIN] || bounds[MAX] <= params.root)
	{
		params.root = (params.b + sqrt_disc) / params.a;
		if (params.root <= bounds[MIN] || bounds[MAX] <= params.root)
			return (false);
	}
	hit_info->t = params.root;
	hit_info->point = ray_at(ray, params.root);
	hit_info->normal = vect_simple_div(vect_subtract(hit_info->point, fig.p_light.location), 0.2);
	return (true);	
}

void	resize_file_selector(t_scene *scene)
{
	if (scene->map_count)
	{
		free_buttons(scene->buttons, scene->map_count);
	}
	if (scene->cumulative_image)
	{
		free(scene->cumulative_image);
	}
	scene->cumulative_image = ft_calloc((scene->height * scene->width), sizeof(t_vect));
	if (!scene->cumulative_image)
	{
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	}
	draw_file_menu(scene);
}

void	resize_rendering(t_scene *scene)
{
	set_stop_status(scene);
	wait_for_threads(scene);
	scene->stop = false;
	if (scene->cumulative_image)
	{
		free(scene->cumulative_image);
	}
	recalculate_view(scene);
	scene->cumulative_image = ft_calloc((scene->height * scene->width), sizeof(t_vect));
	if (!scene->cumulative_image)
	{
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	}
	set_new_image(scene);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	main_loop(scene);
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

t_texture	*get_texture(char *path, float texture_dim)
{
	t_texture	*res;

	if (!path)
		return (NULL);
	res = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!res)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 1), NULL);
	res->path = ft_strdup(path);
	if (!res->path)
		return (free_texture(&res), exit_err(ERR_MEM_MSG, "(malloc)", 2), NULL);
	res->texture = mlx_load_png(path);
	if (!res->texture)
		return (exit_err(ERR_MEM_MSG, res->path, 2), free_texture(&res), NULL);
	res->texture_dim = texture_dim;
	return (res);
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

void	add_box_face(t_object *box, t_figure face, t_material mat)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	new_obj->type = QUAD;
	new_obj->figure.quad.center = face.quad.center;
	new_obj->figure.quad.u_vect = face.quad.u_vect;
	new_obj->figure.quad.v_vect = face.quad.v_vect;
	new_obj->figure.quad.normal = unit_vect(vect_cross(face.quad.u_vect, face.quad.v_vect));
	new_obj->material = mat;
	if (box->texture)
		new_obj->texture = get_texture(box->texture->path, box->texture->texture_dim);
	else
		new_obj->texture = NULL;
	new_obj->hit_func = hit_quad;
	new_obj->edit_origin = translate_quad;
	new_obj->edit_orientation = rotate_quad;
	new_obj->get_origin = get_origin_quad;
	new_obj->edit_dimensions = resize_quad;
	new_obj->get_visual = get_quad_pattern;
	new_obj->get_normal = get_quad_normal;
	new_obj->next = NULL;
	add_object(&box->figure.box.faces, new_obj);
}
void	recalculate_faces(t_object *box, t_vect dimensions)
{
	t_object	*face;
	t_vect		normal;
	t_vect		anti_normal;

	face = box->figure.box.faces;
	normal = unit_vect(vect_cross(box->figure.box.u_vect, box->figure.box.v_vect));
	anti_normal = vect_simple_mult(normal, -1);

	face->figure.quad.u_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, dimensions.y);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(normal, dimensions.z * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(anti_normal, dimensions.z * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, dimensions.y);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.u_vect, dimensions.x * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.u_vect, -1 * dimensions.x * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.u_vect, -1 * dimensions.x);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.v_vect, dimensions.y * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y * 0.5));
	face = face->next;
}

void	init_faces(t_object *box, t_material mat, t_vect dimensions)
{
	t_figure	fig;
	t_vect		normal;
	t_vect		anti_normal;

	normal = unit_vect(vect_cross(box->figure.box.u_vect, box->figure.box.v_vect));
	anti_normal = vect_simple_mult(normal, -1);

	fig.quad.u_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, dimensions.y);
	fig.quad.center = vect_add(box->figure.box.center, vect_simple_mult(normal, dimensions.z * 0.5));
	add_box_face(box, fig, mat);

	fig.quad.u_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y);
	fig.quad.center = vect_add(box->figure.box.center, vect_simple_mult(anti_normal, dimensions.z * 0.5));
	add_box_face(box, fig, mat);

	fig.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, dimensions.y);
	fig.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.u_vect, dimensions.x * 0.5));
	add_box_face(box, fig, mat);

	fig.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y);
	fig.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.u_vect, -1 * dimensions.x * 0.5));
	add_box_face(box, fig, mat);

	fig.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.u_vect, -1 * dimensions.x);
	fig.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.v_vect, dimensions.y * 0.5));
	add_box_face(box, fig, mat);

	fig.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	fig.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y * 0.5));
	add_box_face(box, fig, mat);
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

int	init_sphere(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = SPHERE;
	new_obj->figure.sphere.center = fig.sphere.center;
	new_obj->figure.sphere.radius = fig.sphere.radius;
	new_obj->texture = tx;
	new_obj->hit_func = hit_sphere;
	new_obj->edit_origin = translate_sphere;
	new_obj->edit_orientation = rotate_sphere;
	new_obj->get_origin = get_origin_sphere;
	new_obj->edit_dimensions = resize_sphere;
	new_obj->get_visual = get_sphere_pattern;
	new_obj->get_normal = get_sphere_normal;
	new_obj->next = NULL;
	add_object(&scene->objects, new_obj);
	return (0);
}

int	init_plane(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = PLANE;
	new_obj->figure.plane.center = fig.plane.center;
	new_obj->figure.plane.normal = unit_vect(fig.plane.normal);
	new_obj->texture = tx;
	new_obj->hit_func = hit_plane;
	new_obj->edit_origin = translate_plane;
	new_obj->edit_orientation = rotate_plane;
	new_obj->get_origin = get_origin_plane;
	new_obj->edit_dimensions = resize_plane;
	new_obj->get_visual = get_plane_pattern;
	new_obj->get_normal = get_plane_normal;
	new_obj->next = NULL;
	add_object(&scene->objects, new_obj);
	return (0);
}

int	init_quad(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = QUAD;
	new_obj->figure.quad.center = fig.quad.center;
	new_obj->figure.quad.u_vect = fig.quad.u_vect;
	new_obj->figure.quad.v_vect = fig.quad.v_vect;
	new_obj->figure.quad.normal = unit_vect(vect_cross(fig.quad.u_vect, fig.quad.v_vect));
	new_obj->texture = tx;
	new_obj->hit_func = hit_quad;
	new_obj->edit_origin = translate_quad;
	new_obj->edit_orientation = rotate_quad;
	new_obj->get_origin = get_origin_quad;
	new_obj->edit_dimensions = resize_quad;
	new_obj->get_visual = get_quad_pattern;
	new_obj->get_normal = get_quad_normal;
	new_obj->next = NULL;
	add_object(&scene->objects, new_obj);
	return (0);
}

int	init_disk(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = DISK;
	new_obj->figure.disk.center = fig.disk.center;
	new_obj->figure.disk.normal = unit_vect(fig.disk.normal);
	new_obj->figure.disk.radius = fig.disk.radius;
	new_obj->texture = tx;
	new_obj->hit_func = hit_disk;
	new_obj->edit_origin = translate_disk;
	new_obj->edit_orientation = rotate_disk;
	new_obj->get_origin = get_origin_disk;
	new_obj->edit_dimensions = resize_disk;
	new_obj->get_visual = get_disk_pattern;
	new_obj->get_normal = get_disk_normal;
	new_obj->next = NULL;
	add_object(&scene->objects, new_obj);
	return (0);
}

int	init_box(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = BOX;
	new_obj->figure.box.center = fig.box.center;
	new_obj->figure.box.u_vect = fig.box.u_vect;
	new_obj->figure.box.v_vect = fig.box.v_vect;
	new_obj->figure.box.dimensions = fig.box.dimensions;
	new_obj->figure.box.faces = NULL;
	new_obj->texture = tx;
	new_obj->hit_func = hit_box;
	new_obj->edit_origin = translate_box;
	new_obj->edit_orientation = rotate_box;
	new_obj->get_origin = get_origin_box;
	new_obj->edit_dimensions = resize_box;
	new_obj->get_visual = get_box_pattern;
	new_obj->get_normal = get_box_normal;
	new_obj->next = NULL;
	init_faces(new_obj, new_obj->material, new_obj->figure.box.dimensions);
	add_object(&scene->objects, new_obj);
	return (0);
}

int	init_cylinder(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = CYLINDER;
	new_obj->figure.cylinder.center = fig.cylinder.center;
	new_obj->figure.cylinder.normal = unit_vect(fig.cylinder.normal);
	new_obj->figure.cylinder.radius = fig.cylinder.radius;
	new_obj->figure.cylinder.height = fig.cylinder.height;
	new_obj->texture = tx;
	new_obj->hit_func = hit_cylinder;
	new_obj->edit_origin = translate_cylinder;
	new_obj->edit_orientation = rotate_cylinder;
	new_obj->get_origin = get_origin_cylinder;
	new_obj->edit_dimensions = resize_cylinder;
	new_obj->get_visual = get_cylinder_pattern;
	new_obj->get_normal = get_cylinder_normal;
	new_obj->next = NULL;
	add_object(&scene->objects, new_obj);
	return (0);
}

int	init_cone(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = CONE;
	new_obj->figure.cone.normal = unit_vect(fig.cone.normal);
	new_obj->figure.cone.radius = fig.cone.radius;
	new_obj->figure.cone.height = fig.cone.height;
	new_obj->figure.cone.center = vect_add(fig.cone.center, vect_simple_mult(fig.cone.normal, -fig.cone.height / 2));
	new_obj->texture = tx;
	new_obj->hit_func = hit_cone;
	new_obj->edit_origin = translate_cone;
	new_obj->edit_orientation = rotate_cone;
	new_obj->get_origin = get_origin_cone;
	new_obj->edit_dimensions = resize_cone;
	new_obj->get_visual = get_cone_pattern;
	new_obj->get_normal = get_cone_normal;
	new_obj->next = NULL;
	add_object(&scene->objects, new_obj);
	return (0);
}

int	init_p_light(t_scene *scene, t_figure fig, t_material mat)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = LIGHT;
	new_obj->figure.p_light.location = fig.p_light.location;
	new_obj->figure.p_light.radius_shadow = fig.p_light.radius_shadow;
	new_obj->texture = NULL;
	new_obj->hit_func = hit_point_light;
	new_obj->edit_origin = translate_point_light;
	new_obj->edit_orientation = rotate_sphere;
	new_obj->get_origin = get_origin_point_light;
	new_obj->edit_dimensions = resize_point_light;
	new_obj->get_visual = get_light_pattern;
	new_obj->get_normal = get_light_normal;
	new_obj->next = NULL;
	add_object(&scene->lights, new_obj);
	return (0);
}

char	*check_spaces_and_comments(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
	{
		i++;
	}
	return (0);
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
