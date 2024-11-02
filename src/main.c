/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:26 by vperez-f          #+#    #+#             */
/*   Updated: 2024/11/02 04:06:21 by vpf              ###   ########.fr       */
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
	front_face = vect_dot(hit_info.normal, inc_ray.dir) <= 0.0;
	if (front_face)
		index = AIR_REF_INDEX / index;
	else
		adj_hit.normal = vect_simple_mult(hit_info.normal, -1); //if not inverted + normal in point inception material
	cos = fminf(vect_dot(vect_simple_mult(udir, -1.0), adj_hit.normal), 1.0);
	sin = sqrtf(1.0 - (cos * cos));
	if (((index * sin) > 1.0) || (reflectance(index, cos) > fast_rand(state)))
		bounce_ray = metal_scatter(state, adj_hit, inc_ray, emittance, thread);
	else
		bounce_ray = refract(adj_hit, udir, index, cos);
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
		if (hit_info.object->material.specular > fast_rand(thread->state))
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
	if (ray_hit(thread->scene, ray, &hit_info))
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
	background = hexa_to_vect(AMB_COLOR);
	background = vect_simple_mult(background, thread->scene->amb_light);
	//background = vect_add(color, BG_COLOR);
	//background = vect_div(color, BG_COLOR);
	return (background);
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

t_vect	get_random_disk_sample(uint32_t *state)
{
	t_vect	res;

	while (true)
	{
		res = new_vect((fast_rand(state) * 2.0) - 1.0, (fast_rand(state) * 2.0) - 1.0, 0.0);
		if (sqrtf(vect_dot(res, res)) < 1.0) //sample from -1,1 square | keep only the ones inside disk
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

void	*set_rendering(void *args)
{
	int			aa_sample;
	uint32_t	x;
	uint32_t	y;
	t_ray		ray;
	t_vect		pixel_offset;
	t_color		color;
	t_thread 	*thread;

	thread = args;
	color = new_color(0, 0, 0);
	x = thread->x_start;
	y = thread->y_start;
	while (y < thread->y_end)
	{
		x = thread->x_start;
		while (x < thread->x_end)
		{
			aa_sample = 0;
			color = new_color(0, 0, 0);
			while(aa_sample < SPP)
			{
				//better offset | stratified offset etc...
				ray.origin = defocus_sample(thread->scene->camera, thread->state);
				pixel_offset = set_pixel_offset(thread->scene->camera, x, y, thread->state);
				ray.dir = unit_vect(vect_subtract(pixel_offset, ray.origin));
				color = vect_add(color, calc_pixel_color(thread, ray, MAX_DEPTH));
				//color = calc_pixel_color_normal(thread->scene, ray);
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

bool	hit_quad(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	float	denominator;
	float	root;
	float	q;
	t_vect	point;
	t_vect	normal;

	//careful with dot products close to 0 || floating point etc...
	normal = unit_vect(vect_cross(fig.quad.u_vect, fig.quad.v_vect));
	denominator = vect_dot(normal, ray.dir);
	if (fabs(denominator) < 1e-8)
		return (false);
	q = vect_dot(fig.quad.origin, normal);
	point = vect_subtract(ray.origin, fig.plane	.center);
	root = q - (vect_dot(point, normal)) / denominator;
	if (root <= bounds[MIN] || bounds[MAX] <= root)
	{
		return (false);
	}
	hit_info->t = root;
	hit_info->point = ray_at(ray, root);
	hit_info->normal = normal;
	// pointer in hit_info to object node hit so as to only calc normal once (after knowing closest hit)
	return (true);	
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
	point = vect_subtract(ray.origin, fig.plane	.center);
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

	//scene->camera.origin = new_vect(0, 3, 2);
	//scene->camera.orientation = unit_vect(new_vect(0, -2.75, -3));
	scene->camera.origin = new_vect(0.0, 0.0, 15.0);
	scene->camera.orientation = unit_vect(new_vect(0.0, 0.0, -1.0));
	scene->camera.fov = FOV;
	scene->camera.defocus_angle = DEFOCUS;
	scene->camera.focus_dist = FOCUS_DIST;
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
	
	scene->camera.viewport_origin.x = scene->camera.origin.x + (scene->camera.focus_dist * scene->camera.w.x) - (scene->camera.vp_edge_horizntl.x / 2) - (scene->camera.vp_edge_vert.x / 2);	
	scene->camera.viewport_origin.y = scene->camera.origin.y + (scene->camera.focus_dist * scene->camera.w.y) - (scene->camera.vp_edge_horizntl.y / 2) - (scene->camera.vp_edge_vert.y / 2);
	scene->camera.viewport_origin.z = scene->camera.origin.z + (scene->camera.focus_dist * scene->camera.w.z) - (scene->camera.vp_edge_horizntl.z / 2) - (scene->camera.vp_edge_vert.z / 2);
	temp = vect_add(scene->camera.pixel_delta_h, scene->camera.pixel_delta_v);
	scene->camera.viewport_pixel0.x = scene->camera.viewport_origin.x + (0.5 * temp.x);
	scene->camera.viewport_pixel0.y = scene->camera.viewport_origin.y + (0.5 * temp.y);
	scene->camera.viewport_pixel0.z = scene->camera.viewport_origin.z + (0.5 * temp.z);
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
		new_obj->next = NULL;
	}
	if (type == PLANE)
	{
		new_obj->type = type;
		new_obj->figure.plane.center = fig.plane.center;
		new_obj->figure.plane.normal = fig.plane.normal;
		new_obj->material.color = mat.color;
		new_obj->material.specular = mat.specular;
		new_obj->material.albedo = mat.albedo;
		new_obj->material.type = mat.type;
		new_obj->material.metal_roughness = mat.metal_roughness;
		new_obj->material.emission_intensity = mat.emission_intensity;
		new_obj->material.refraction_index = mat.refraction_index;
		new_obj->hit_func = hit_plane;
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
		new_obj->hit_func = NULL;
		new_obj->next = NULL;
	}
	if (mat.type == EMISSIVE)
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
	fig.p_light.location = new_vect(0, 0.0, -7.0);
	mat.color = hexa_to_vect(BLUE);
	mat.specular = 0.0;
	mat.metal_roughness = 0.0;
	mat.albedo = mat.color;
	mat.emission_intensity = 2.5;
	mat.type = EMISSIVE;
	//init_object(scene, fig, mat, LIGHT);
	fig.p_light.location = new_vect(-5.0, -4.0, -7.0);
	mat.color = hexa_to_vect(GREEN);
	mat.specular = 0.0;
	mat.metal_roughness = 0.0;
	mat.albedo = mat.color;
	mat.emission_intensity = 2.5;
	mat.type = EMISSIVE;
	//init_object(scene, fig, mat, LIGHT);
	fig.p_light.location = new_vect(5.0, 4.0, -7.0);
	mat.color = hexa_to_vect(RED);
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

	fig.plane.center = new_vect(0, 0.0, -10.0);
	fig.plane.normal = unit_vect(new_vect(0, 0, 1));
	mat.color = hexa_to_vect(BLACK);
	mat.specular = 0.1;
	mat.metal_roughness = 0.2;
	mat.albedo = mat.color;
	mat.type = LAMBERTIAN;
	init_object(scene, fig, mat, PLANE);

	fig.plane.center = new_vect(0, -10.0, 0);
	fig.plane.normal = unit_vect(new_vect(0, 1, 0));
	mat.color = hexa_to_vect(SILVER);
	mat.specular = 1.0;
	mat.metal_roughness = 0.0;
	mat.albedo = mat.color;
	mat.emission_intensity = 2.0;
	mat.type = LAMBERTIAN;
	init_object(scene, fig, mat, PLANE);

	fig.plane.center = new_vect(0, 10.0, 0);
	fig.plane.normal = unit_vect(new_vect(0, -1, 0));
	mat.color = hexa_to_vect(WHITE);
	mat.specular = 1.0;
	mat.metal_roughness = 0.81;
	mat.albedo = mat.color;
	mat.emission_intensity = 1.5;
	mat.type = EMISSIVE;
	init_object(scene, fig, mat, PLANE);

	fig.plane.center = new_vect(-10.0, 0.0, 0);
	fig.plane.normal = unit_vect(new_vect(1, 0, 0));
	mat.color = hexa_to_vect(GREEN);
	mat.specular = 0.4;
	mat.metal_roughness = 0.81;
	mat.albedo = mat.color;
	mat.refraction_index = 1.0;
	mat.type = LAMBERTIAN;
	init_object(scene, fig, mat, PLANE);

	fig.plane.center = new_vect(10.0, 0.0, 0);
	fig.plane.normal = unit_vect(new_vect(-1, 0, 0));
	mat.color = hexa_to_vect(RED);
	mat.specular = 0.2;
	mat.metal_roughness = 0.51;
	mat.albedo = mat.color;
	mat.refraction_index = 1.0;
	mat.type = LAMBERTIAN;
	init_object(scene, fig, mat, PLANE);

	fig.sphere.center = new_vect(7.0, -5.0, -7);
	fig.sphere.radius = 3;
	mat.color = hexa_to_vect(WHITE);
	mat.specular = 0.1;
	mat.metal_roughness = 0.2;
	mat.albedo = mat.color;
	mat.emission_intensity = 4.0;
	mat.type = GLOSSY;
	init_object(scene, fig, mat, SPHERE);

	fig.sphere.center = new_vect(-7.0, 5.0, -7);
	fig.sphere.radius = 3;
	mat.color = hexa_to_vect(WHITE);
	mat.specular = 1.0;
	mat.metal_roughness = 0.0;
	mat.emission_intensity = 2.0;
	mat.albedo = mat.color;
	mat.refraction_index = 1.0;
	mat.type = METAL;
	init_object(scene, fig, mat, SPHERE);

	fig.sphere.center = new_vect(0.0, -3.0, -5);
	fig.sphere.radius = 3;
	mat.color = hexa_to_vect(WHITE);
	mat.specular = 1.0;
	mat.metal_roughness = 1.0;
	mat.emission_intensity = 2.0;
	mat.albedo = mat.color;
	mat.refraction_index = 1.7;
	mat.type = DIELECTRIC;
	init_object(scene, fig, mat, SPHERE);

	fig.sphere.center = new_vect(0.0, 0.0, -110);
	fig.sphere.radius = 100;
	mat.color = hexa_to_vect(BLACK);
	mat.specular = 0.4;
	mat.metal_roughness = 0.81;
	mat.emission_intensity = 2.0;
	mat.albedo = mat.color;
	mat.refraction_index = 1.0;
	mat.type = LAMBERTIAN;
	//init_object(scene, fig, mat, SPHERE);





	fig.quad.u_vect = new_vect(4.0, 0.0, 0.0);
	fig.quad.v_vect = new_vect(0.0, 4.0, 0.0);
	fig.quad.origin = new_vect(0.0, 0.0, -2);
	mat.color = hexa_to_vect(RED);
	mat.specular = 0.1;
	mat.metal_roughness = 0.1;
	mat.albedo = mat.color;
	mat.type = LAMBERTIAN;
	//init_object(scene, fig, mat, QUAD);
	
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
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	init_figures(scene);
	init_lights(scene);
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
	free_objects(&scene.lights);
	//free_buttons(scene.buttons);
	return (0);
}
