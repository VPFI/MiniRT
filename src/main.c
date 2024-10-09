/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:26 by vperez-f          #+#    #+#             */
/*   Updated: 2024/10/09 20:50:11 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

float	get_rnd_norm_float(void)
{
	float	res;

	res = rand();
	return (res / (float)RAND_MAX);
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

t_vect	set_pixel_offset(t_camera camera, uint32_t x, uint32_t y)
{
	t_vect	res;
	t_vect	aux1;
	t_vect	aux2;

	aux1 = vect_simple_mult(camera.pixel_delta_h, (x + (get_rnd_norm_float() - 0.5)));
	aux2 = vect_simple_mult(camera.pixel_delta_v, (y + (get_rnd_norm_float() - 0.5)));
	res = vect_add(aux1, aux2);
	res = vect_add(res, camera.viewport_pixel0);
	return (res);
}

bool	ray_hit(t_scene *scene, t_ray ray, t_hit_info *hit_info)
{
	t_object	*temp;
	float		bounds[2];
	bool		hit;

	hit = false;
	bounds[MIN] = 0.001;
	bounds[MAX] = __FLT_MAX__;
	temp = scene->objects;
	while (temp)
	{
		if (temp->hit_func(ray, temp->figure, hit_info, bounds))
		{
			hit = true;
			bounds[MAX] = hit_info->t;
			hit_info->object = temp;
		}
		temp = temp->next;
	}
	return (hit);
}

t_color	calc_pixel_color_normal(t_scene *scene, t_ray ray)
{
	t_color		color;
	t_hit_info	hit_info;

	if (ray_hit(scene, ray, &hit_info))
	{
		if (vect_dot(hit_info.normal, ray.dir) > 0.0)
			color = new_color(0, 0, 0);
		else
			color = new_color(((hit_info.normal.x + 1) * 0.5), ((hit_info.normal.y + 1) * 0.5), ((hit_info.normal.z + 1) * 0.5));
	}
	else
	{
		color = new_color(0, 0.8, 1);
	}
	return (color);
}

int	get_sphere_specular(t_object *object)
{
	return (object->figure.sphere.material.specular);
}

t_color	get_sphere_color(t_object *object)
{
	return (object->figure.sphere.material.color);
}

t_vect	get_random_uvect(void)
{
	t_vect	res;
	float	bound;

	while (1)
	{
		res.x = (get_rnd_norm_float() - 0.5) * 2;
		res.y = (get_rnd_norm_float() - 0.5) * 2;
		res.z = (get_rnd_norm_float() - 0.5) * 2;
		bound = vect_dot(res, res);
		if ( 0.000000001 < bound && bound <= 1)
		{
			res = vect_simple_div(res, sqrtf(bound));
			return (res);
		}
	}
}

t_color	calc_pixel_color(t_scene *scene, t_ray ray, int depth)
{
	t_color		color;
	float		mod;
	//float		norm;
	t_hit_info	hit_info;
	t_vect		test;

	if (depth <= 0)
		return (new_color(0, 0, 0));
	ft_bzero(&hit_info, sizeof(hit_info));
	if (ray_hit(scene, ray, &hit_info))
	{
		//color = hit_info.object->get_color_func(hit_info.object);
		//color = vect_simple_mult(color, scene->amb_light);
		//norm = vect_dot(hit_info.normal, ray.dir);
		//if (norm < 0)
		//	norm *= -1;
		//color = vect_simple_mult(color, norm);
		test = get_random_uvect();
		if (vect_dot(test, hit_info.normal) < 0.0)
			test = vect_simple_mult(test, -1);
		test = vect_add(test, hit_info.normal);
		return (vect_mult(vect_simple_mult(calc_pixel_color(scene, new_ray(test, hit_info.point), depth - 1), 0.8), hit_info.object->get_color_func(hit_info.object)));
		if (!hit_info.object->get_specular_func(hit_info.object))
			return (color);
		test = vect_subtract(ray.dir, vect_simple_mult(hit_info.normal, 2 * vect_dot(ray.dir, hit_info.normal)));
		return (vect_simple_mult(calc_pixel_color(scene, new_ray(test, hit_info.point), depth - 1), 0.8));
	}
	t_vect	unit_dir = unit_vect(ray.dir);
	mod = 0.5 * (unit_dir.y + 1);
	color = vect_add(vect_simple_mult(new_color(1, 1, 1), (1 - mod)), vect_simple_mult(new_color(0.3, 0.7, 1), mod));
	color = vect_simple_mult(color, scene->amb_light);
	return (color);
}

void	set_thread(t_thread *thread)
{
	//refine x/y divisions for correct bounds
	thread->y_start = (int)roundf((thread->scene->height / (float)(THREADS)) * thread->id);
	thread->y_end = thread->y_start + (int)roundf(thread->scene->height / (float)(THREADS));
	thread->x_start = 0;
	thread->x_end = thread->scene->width;
	printf("%i -- %i -- %i -- %i\n", thread->y_start, thread->y_end, thread->x_start, thread->x_end);
}

void	init_render(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < THREADS)
	{
		scene->threads[i].id = i;
		scene->threads[i].scene = scene;
		set_thread(&scene->threads[i]);
		pthread_create(&scene->threads[i].self, NULL, &set_rendering, (void *)&scene->threads[i]);
		i++;
	}
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

void	*set_rendering(void *args)
{
	t_ray		ray;
	//t_vect		pixel_center;
	t_vect		pixel_offset;
	int			aa_sample;
	t_color		color;
	uint32_t	x;
	uint32_t	y;
	t_thread 	*thread;

	color = new_color(0, 0, 0);
	thread = args;
	aa_sample = 0;
	x = thread->x_start;
	y = thread->y_start;
	ray.origin = thread->scene->camera.origin;
	while (y < thread->y_end)
	{
		x = 0;
		while (x < thread->x_end)
		{
			aa_sample = 0;
			color = new_color(0, 0, 0);
			//pixel_center = set_pixel_center(thread->scene->camera, x,y);
			while(aa_sample < AA)
			{
				pixel_offset = set_pixel_offset(thread->scene->camera, x, y);
				ray.dir = unit_vect(vect_subtract(pixel_offset, ray.origin));
				color = vect_add(color, calc_pixel_color(thread->scene, ray, MAX_DEPTH));
				aa_sample++;
			}
			safe_pixel_put(thread->scene, x, y, vect_simple_mult(color, 1 / (float)aa_sample));
			x++;
		}
		y++;
	}
	return (NULL);
}

void	main_loop(void *sc)
{
	t_scene		*scene;
	char		*fps;
	double		time;

	scene = sc;
	if (!scene->choose_file)
		return ;
	set_new_image(scene);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	time = mlx_get_time();
	init_render(scene);
	time = mlx_get_time() - time;
	printf("after threads || %f\n", time);
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
	scene->camera.viewport_width = 4;
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
		new_obj->figure.sphere.material.color = fig.sphere.material.color;
		new_obj->figure.sphere.material.specular = fig.sphere.material.specular;
		new_obj->hit_func = hit_sphere;
		new_obj->get_specular_func = get_sphere_specular;
		new_obj->get_color_func = get_sphere_color;
		new_obj->next = NULL;
	}
	add_object(objects, new_obj);
	return (0);
}

t_color	hexa_to_vect(int color)
{
	t_color	res;

	res.x = get_r(color) / 255.0;
	res.y = get_g(color) / 255.0;
	res.z = get_b(color) / 255.0;
	return (res);
}

void	init_figures(t_scene *scene)
{
	t_figure	fig;

	fig.sphere.center = new_vect(0.1, -0.4, -0.75);
	fig.sphere.radius = 0.1;
	fig.sphere.material.color = hexa_to_vect(GREEN);
	fig.sphere.material.specular = 1;
	init_object(&scene->objects, fig, SPHERE);
	fig.sphere.center = new_vect(-0.55, 0, -1);
	fig.sphere.radius = 0.5;
	fig.sphere.material.color = hexa_to_vect(DEF_COLOR);
	fig.sphere.material.specular = 1;
	init_object(&scene->objects, fig, SPHERE);
	fig.sphere.center = new_vect(0.35, 0, -1.5);
	fig.sphere.radius = 0.5;
	fig.sphere.material.color = hexa_to_vect(CYAN_GULF);
	fig.sphere.material.specular = 1;
	init_object(&scene->objects, fig, SPHERE);
	fig.sphere.center = new_vect(0, 3, -10);
	fig.sphere.radius = 3;
	fig.sphere.material.color = hexa_to_vect(RED);
	fig.sphere.material.specular = 1;
	init_object(&scene->objects, fig, SPHERE);
	fig.sphere.center = new_vect(0, -50.5, -1);
	fig.sphere.radius = 50;
	fig.sphere.material.color = hexa_to_vect(RED);
	fig.sphere.material.specular = 0;
	init_object(&scene->objects, fig, SPHERE);
}

void	init_scene(t_scene *scene)
{
	ft_bzero(scene, sizeof(t_scene));
	scene->width = WINW;
	scene->height = WINH;
	scene->amb_light = AMB;
	scene->aspect_ratio = scene->width / (float)scene->height;
	scene->choose_file = 1;
	scene->current_file = 0;
	scene->mlx = mlx_init(scene->width, scene->height, "miniRT", true);
	scene->image = mlx_new_image(scene->mlx, scene->width, scene->height);
	init_figures(scene);
	init_camera(scene);
	srand(mlx_get_time());
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
