/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:26 by vperez-f          #+#    #+#             */
/*   Updated: 2024/10/07 02:37:19 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	print_vec(t_vect vect)
{
	printf("VECT X: %f\n", vect.x);
	printf("VECT Y: %f\n", vect.y);
	printf("VECT Z: %f\n", vect.z);
}

void	safe_pixel_put(t_scene *scene, uint32_t x, uint32_t y, uint32_t color)
{
	if ((x >= scene->width) || y >= scene->height)
		return ;
	mlx_put_pixel(scene->image, x, y, color);
}

void	close_all(t_scene *scene)
{
	if (scene->image)
	{
		mlx_delete_image(scene->mlx, scene->image);
	}
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

void	key_down(mlx_key_data_t key_data, void *sc)
{
	t_scene	*scene;

	scene = sc;
	if (key_data.key == MLX_KEY_ESCAPE)
		close_all(scene);
	else if (!scene->choose_file && is_arrow_key_down(key_data))
		move_menu(scene, key_data.key);
	else if (!scene->choose_file && key_data.key == MLX_KEY_ENTER)
	{
		scene->choose_file = 1;
		set_new_image(scene);
		mlx_image_to_window(scene->mlx, scene->image, 0 ,0);
		printf("YOU CHOSE %s.rt\n", scene->buttons[scene->current_file].text);
	}
		
}

t_vect	set_pixel_center(t_camera camera, uint32_t x, uint32_t y)
{
	t_vect	res;
	t_vect	temp1;
	t_vect	temp2;

	temp1 = vect_simple_mult(camera.pixel_delta_h, x);
	temp2 = vect_simple_mult(camera.pixel_delta_v, y);
	res = vect_add(temp1, temp2);
	res = vect_add(res, camera.viewport_pixel0);
	return (res);
}

bool	ray_hit(t_scene *scene, t_ray ray, t_hit_info *hit_info)
{
	t_object	*temp;
	float		bounds[2];
	bool		hit;

	hit = false;
	bounds[MIN] = 0;
	bounds[MAX] = __FLT_MAX__;
	temp = scene->objects;
	while (temp)
	{
		if (temp->hit_func(ray, temp->figure, hit_info, bounds))
		{
			hit = true;
			bounds[MAX] = hit_info->t;
		}
		temp = temp->next;
	}
	return (hit);
}

void	main_loop(void *sc)
{
	t_vect		pixel_center;
	t_ray		ray;
	t_hit_info	hit_info;
	t_scene		*scene;
	char		*fps;
	uint32_t	x;
	uint32_t	y;
	int			color;

	x = 0;
	y = 0;
	color = DEF_COLOR;
	scene = sc;
	ray.origin = scene->camera.origin;
	if (!scene->choose_file)
		return ;
	set_new_image(scene);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	while (y < scene->height)
	{
		x = 0;
		while (x < scene->width)
		{
			pixel_center = set_pixel_center(scene->camera, x,y);
			ray.dir = vect_subtract(pixel_center, scene->camera.origin);
			if (ray_hit(scene, ray, &hit_info))
			{
				if (vect_dot(hit_info.normal, ray.dir) > 0.0)
					color = get_rgba(0, 0, 0, 255);
				else
					color = get_rgba(((hit_info.normal.x + 1) * 0.5) * 255, ((hit_info.normal.y + 1) * 0.5) * 255, ((hit_info.normal.z + 1) * 0.5) * 255, 255);
				safe_pixel_put(scene, x, y, color);
			}
			else
			{
				color = get_rgba(0, 50, 200, (int)round((y / (float)scene->height) * 255));
				safe_pixel_put(scene, x, y, color);
			}
			x++;
		}
		y++;
	}
	fps = ft_itoa((int)round(1 / scene->mlx->delta_time));
	mlx_set_window_title(scene->mlx, fps);
	free(fps);
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
		mlx_resize_image(scene->image, scene->width, scene->height);
}


void	set_new_image(t_scene *scene)
{
	if (scene->image)
		mlx_delete_image(scene->mlx, scene->image);
	scene->image = mlx_new_image(scene->mlx, scene->width, scene->height);
}

void	mouse_handle(mouse_key_t button, action_t action, modifier_key_t mods, void *sc)
{
	t_scene *scene;

	scene = sc;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
		scene->choose_file = 1;
}

void	init_camera(t_scene *scene)
{
	t_vect temp;

	scene->camera.origin = new_vect(0, 0, 0);
	scene->camera.view_distance = 1;
	scene->camera.viewport_height = 2;
	scene->camera.viewport_width = scene->camera.viewport_height * (scene->width / (float)scene->height);
	scene->camera.vp_edge_horizntl = new_vect(scene->camera.viewport_width, 0, 0);
	scene->camera.vp_edge_vert = new_vect(0, (scene->camera.viewport_height) * -1, 0);
	scene->camera.pixel_delta_h = vect_simple_div(scene->camera.vp_edge_horizntl, scene->width);
	scene->camera.pixel_delta_v = vect_simple_div(scene->camera.vp_edge_vert, scene->height);
	scene->camera.viewport_origin.x = scene->camera.origin.x - (scene->camera.vp_edge_horizntl.x / 2) - (scene->camera.vp_edge_vert.x / 2);	
	scene->camera.viewport_origin.y = scene->camera.origin.y - (scene->camera.vp_edge_horizntl.y / 2) - (scene->camera.vp_edge_vert.y / 2);
	scene->camera.viewport_origin.z = scene->camera.origin.z - (scene->camera.vp_edge_horizntl.z / 2) - (scene->camera.vp_edge_vert.z / 2) - scene->camera.view_distance;
	temp = vect_add(scene->camera.pixel_delta_h, scene->camera.pixel_delta_v);
	scene->camera.viewport_pixel0.x = scene->camera.viewport_origin.x + (0.5 * temp.x);
	scene->camera.viewport_pixel0.y = scene->camera.viewport_origin.y + (0.5 * temp.y);
	scene->camera.viewport_pixel0.z = scene->camera.viewport_origin.z + (0.5 * temp.z);
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

int	init_object(t_object **objects, t_figure fig, t_fig_type type)
{
	t_object 	*new_obj;

	new_obj = (t_object *)malloc(sizeof(t_object));
	if (!new_obj)
		return (-1);
	if (type == SPHERE)
	{
		new_obj->type = type;
		new_obj->figure.sphere.center = fig.sphere.center;
		new_obj->figure.sphere.radius = fig.sphere.radius;
		new_obj->hit_func = hit_sphere;
		new_obj->next = NULL;
	}
	add_object(objects, new_obj);
	return (0);
}

void	init_figures(t_scene *scene)
{
	t_figure	fig;

	fig.sphere.center = new_vect(-0.55, 0, -1);
	fig.sphere.radius = 0.5;
	init_object(&scene->objects, fig, SPHERE);
	fig.sphere.center = new_vect(0.35, 0, -1.5);
	fig.sphere.radius = 0.5;
	init_object(&scene->objects, fig, SPHERE);
	fig.sphere.center = new_vect(0, 3, -10);
	fig.sphere.radius = 3;
	init_object(&scene->objects, fig, SPHERE);
	fig.sphere.center = new_vect(0, -50.5, -1);
	fig.sphere.radius = 50;
	init_object(&scene->objects, fig, SPHERE);
}

void	init_scene(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
	scene->width = WINW;
	scene->height = WINH;
	scene->aspect_ratio = scene->width / (float)scene->height;
	scene->choose_file = 1;
	scene->current_file = 0;
	scene->mlx = mlx_init(scene->width, scene->height, "miniRT", true);
	scene->image = mlx_new_image(scene->mlx, scene->width, scene->height);
	init_figures(scene);
	init_camera(scene);
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

int	main(int argc, char **argv)
{
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
	if (scene.mlx)
		mlx_terminate(scene.mlx);
	free_objects(&scene.objects);
	//free_buttons(scene.buttons);
	return (0);
}
