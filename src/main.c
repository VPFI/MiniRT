/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:26 by vperez-f          #+#    #+#             */
/*   Updated: 2024/10/15 19:15:07 by vperez-f         ###   ########.fr       */
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

t_ray	metal_scatter(uint32_t *state, t_hit_info hit_info, t_ray inc_ray)
{
	t_vect		bounce_dir;
	t_ray		bounce_ray;

	bounce_dir = vect_subtract(inc_ray.dir, vect_simple_mult(hit_info.normal, 2 * vect_dot(inc_ray.dir, hit_info.normal)));
	if (hit_info.object->material.metal_roughness)
		bounce_dir = vect_add(unit_vect(bounce_dir), vect_simple_mult(get_random_uvect(state), hit_info.object->material.metal_roughness));
	bounce_ray = new_ray(bounce_dir, hit_info.point);
	return (bounce_ray);
}

t_color	test_light(t_thread *thread, t_hit_info hit_info, t_color color)
{
	t_hit_info	test_hit;
	t_ray		shadow_ray;
	float		mod;
	float		mod2;

	shadow_ray = new_ray((vect_subtract(new_vect(-3, 1, -1), hit_info.point)), hit_info.point);
	if (ray_hit(thread->scene, shadow_ray, &test_hit))
	{
		color = vect_simple_mult(color, thread->scene->amb_light);
	}
	else
	{
		mod = vect_dot(hit_info.normal, shadow_ray.dir);
		mod2 = 1 / sqrtf(vect_dot(shadow_ray.dir, shadow_ray.dir));
		if (mod < 0)
			mod = 0;
		color = vect_simple_mult(color, (thread->scene->amb_light + 3 * mod * mod2));
	}
	return (color);
}

t_color	test_lambert(t_thread *thread, t_hit_info hit_info, t_ray ray)
{
	t_color	color;
	float	norm;

	color = hit_info.object->material.color;
	norm = vect_dot(hit_info.normal, ray.dir);
	if (norm < 0)
		norm *= -1;
	color = vect_simple_mult(color, norm);
	color = test_light(thread, hit_info, color);
	return (color);
}

t_ray	lambertian_scatter(uint32_t *state, t_hit_info hit_info)
{
	t_vect		bounce_dir;
	t_vect		target_on_sphere;
	t_ray		bounce_ray;

	bounce_dir = get_random_uvect(state);
	target_on_sphere = vect_add(bounce_dir, hit_info.normal);
	if (zero_vect(bounce_dir))
		target_on_sphere = hit_info.normal;
	target_on_sphere = vect_add(target_on_sphere, hit_info.point);
	bounce_ray = new_ray(unit_vect(vect_subtract(target_on_sphere, hit_info.point)), hit_info.point);
	return (bounce_ray);
}

//Schlick's approximation || R0 = R0 + (1 - R0)(1 - cos0)^5 || R0 = (n1 - n2) / (n1 + n2)
float	reflectance(float index, float cos)
{
	float	r;
	float	aux;
	float	res;

	aux = 1 - cos;
	r = (1 - index) / (1 + index);
	r = r * r;
	res = r + (1 - r) * (aux * aux * aux * aux * aux);
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
	res = new_ray(vect_add(perp, parallel), hit_info.normal);
	return (res);
}

t_ray	dielectric_scatter(uint32_t *state, t_hit_info hit_info, t_ray inc_ray)
{
	//check face vect_dot etc...
	t_ray	bounce_ray;
	bool	front_face;
	t_vect	unit_dir;
	float	index;
	float	cos;
	float	sin;

	unit_dir = unit_vect(inc_ray.dir);
	index = 1.5;
	front_face = vect_dot(hit_info.normal, inc_ray.dir) < 0;
	if (!front_face)
		index = 1.0 / index;
	cos = vect_dot(vect_simple_mult(unit_dir, -1), hit_info.normal);
	if (cos < 1.0)
		cos = 1;
	sin = sqrtf(1.0 - cos * cos);
	if ((index * sin) > 1.0 || reflectance(index, cos) > fast_rand(state))
		bounce_ray = metal_scatter(state, hit_info, inc_ray);
	else
		bounce_ray = refract(hit_info, unit_dir, index, cos);
	return (bounce_ray);
}

bool	scatter_ray(t_thread *thread, t_hit_info hit_info, t_ray *bounce_ray, t_ray ray)
{
	if (hit_info.object->material.type == LAMBERTIAN)
	{
		(*bounce_ray) = lambertian_scatter(thread->state, hit_info);
	}
	else if (hit_info.object->material.type == METAL)
	{
		(*bounce_ray) = metal_scatter( thread->state, hit_info, ray);
		if (vect_dot((*bounce_ray).dir, hit_info.normal) <= 0)
			return (false);
	}
	else if (hit_info.object->material.type == DIELECTRIC)
	{
		(*bounce_ray) = dielectric_scatter(thread->state, hit_info, ray);
	}
	return (true);
}

t_color	calc_pixel_color(t_thread *thread, t_ray ray, int depth)
{
	t_color		color;
	t_color		throughput;
	float		time_aux;
	float		norm;
	float		mod;
	t_hit_info	hit_info;
	t_ray		bounce_ray;

	if (depth <= 0)
		return (new_color(0, 0, 0));
	ft_bzero(&hit_info, sizeof(hit_info));
	time_aux = 0;
	throughput = new_color(1, 1, 1);
	color = new_color(0, 0, 0);
	time_aux = mlx_get_time();
	if (ray_hit(thread->scene, ray, &hit_info))
	{
		thread->time_hit += mlx_get_time() - time_aux;
		if (hit_info.object->material.type == EMISSIVE)
		{
			color = vect_mult(throughput, hit_info.object->material.color);
			color = vect_simple_mult(color, hit_info.object->material.emission_intensity);
			if (depth == MAX_DEPTH)
			{
				norm = vect_dot(hit_info.normal, ray.dir);
				if (norm < 0)
					norm *= -1;
				//color = vect_simple_mult(color, norm);
			}
			return (color);
		}
		if (!scatter_ray(thread, hit_info, &bounce_ray, ray))
		{
			//color = test_lambert(thread, hit_info, ray);
			return (color);
		}
		//vect_add(vect_simple_mult(vect_mult(calc_pixel_color(thread, bounce_ray, depth - 1), hit_info.object->material.color), 0.8), color)
		//vect_add(vect_mult(calc_pixel_color(thread, bounce_ray, depth - 1), hit_info.object->material.color), color)
		return (vect_add(vect_simple_mult(vect_mult(calc_pixel_color(thread, bounce_ray, depth - 1), hit_info.object->material.color), 1), color));
	}
	thread->time_hit += mlx_get_time() - time_aux;
	t_vect	unit_dir = unit_vect(ray.dir);
	mod = 0.5 * (unit_dir.y + 1.0);
	color = vect_add(vect_simple_mult(new_color(1, 1, 1), (1.0 - mod)), vect_simple_mult(new_color(0.3, 0.7, 1), mod));
	//color = hexa_to_vect(AMB_COLOR);
	color = vect_simple_mult(color, thread->scene->amb_light);
	//color = vect_add(color, BG_COLOR);
	//color = vect_div(color, BG_COLOR);
	return (color);
}

void	set_thread(t_thread *thread)
{
	thread->y_start = 0;
	thread->y_end = thread->scene->height;
	thread->x_start = thread->id;
	thread->x_end = thread->scene->width;
	thread->x_increment = THREADS;
	thread->pix_rendered = 0;
	thread->time_hit = 0;
	thread->state = malloc(sizeof(uint32_t));
	if (!thread->state)
		exit (205);
	*(thread->state) = mlx_get_time() * (thread->id + 1) * 123456;
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
	//t_vect	pixel_center;
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
		x = thread->x_start;
		while (x < thread->x_end)
		{
			aa_sample = 0;
			color = new_color(0, 0, 0);
			//pixel_center = set_pixel_center(thread->scene->camera, x,y);
			while(aa_sample < SPP)
			{
				//better offset | stratified offset etc...
				pixel_offset = set_pixel_offset(thread->scene->camera, x, y, thread->state);
				ray.dir = unit_vect(vect_subtract(pixel_offset, ray.origin));
				color = vect_add(color, calc_pixel_color(thread, ray, MAX_DEPTH));
				aa_sample++;
			}
			color = clamp_vect(vect_simple_mult(color, 1 / (float)aa_sample), 0.0, 1.0);
			safe_pixel_put(thread->scene, x, y, color);
			thread->pix_rendered++;
			x += thread->x_increment;
		}
		y++;
	}
	free(thread->state);
	printf("THREAD: %i --- || %i || TIME: %f || TIME_HIT: %f\n", thread->id, thread->pix_rendered, mlx_get_time(), thread->time_hit);
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
	printf("TOT PIX %i || %i\n", scene->height * scene->width, scene->height * scene->width / THREADS);
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
	scene->camera.viewport_height = 2.0;
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

int	init_object(t_object **objects, t_figure fig, t_material mat, t_fig_type type)
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
		new_obj->material.color = mat.color;
		new_obj->material.specular = mat.specular;
		new_obj->material.albedo = mat.albedo;
		new_obj->material.type = mat.type;
		new_obj->material.metal_roughness = mat.metal_roughness;
		new_obj->material.emission_intensity = mat.emission_intensity;
		new_obj->hit_func = hit_sphere;
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
	t_material	mat;

	fig.sphere.center = new_vect(0, -0.5, -1.8);
	fig.sphere.radius = 0.3;
	mat.color = hexa_to_vect(RED);
	mat.specular = 0;
	mat.albedo = 0.8;
	mat.type = LAMBERTIAN;
	init_object(&scene->objects, fig, mat, SPHERE);
	fig.sphere.center = new_vect(0.6, -0.5, -1.5);
	fig.sphere.radius = 0.3;
	mat.color = new_color(255, 255, 255);
	mat.specular = 0.5;
	mat.albedo = 0.8;
	mat.type = DIELECTRIC;
	init_object(&scene->objects, fig, mat, SPHERE);
	fig.sphere.center = new_vect(-0.6, -0.5, -1.5);
	fig.sphere.radius = 0.3;
	mat.color = hexa_to_vect(WHITE);
	mat.specular = 0;
	mat.albedo = 0.8;
	mat.type = LAMBERTIAN;
	init_object(&scene->objects, fig, mat, SPHERE);
	fig.sphere.center = new_vect(0.6, -0.5, -2.1);
	fig.sphere.radius = 0.3;
	mat.color = hexa_to_vect(WHITE);
	mat.specular = 0;
	mat.albedo = 0.8;
	mat.type = LAMBERTIAN;
	init_object(&scene->objects, fig, mat, SPHERE);
	fig.sphere.center = new_vect(-0.6, -0.5, -2.1);
	fig.sphere.radius = 0.3;
	mat.color = hexa_to_vect(WHITE);
	mat.specular = 0;
	mat.albedo = 0.8;
	mat.type = LAMBERTIAN;
	init_object(&scene->objects, fig, mat, SPHERE);
	fig.sphere.center = new_vect(0, 0.1, -2.1);
	fig.sphere.radius = 0.3;
	mat.color = hexa_to_vect(WHITE);
	mat.specular = 1;
	mat.albedo = 0.2;
	mat.type = METAL;
	init_object(&scene->objects, fig, mat, SPHERE);
	fig.sphere.center = new_vect(0, -50.8, -1);
	fig.sphere.radius = 50;
	mat.color = hexa_to_vect(WHITE);
	mat.specular = 1;
	mat.albedo = 0.8;
	mat.type = LAMBERTIAN;
	init_object(&scene->objects, fig, mat, SPHERE);
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
