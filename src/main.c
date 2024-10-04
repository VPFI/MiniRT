/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:26 by vperez-f          #+#    #+#             */
/*   Updated: 2024/10/04 19:28:17 by vperez-f         ###   ########.fr       */
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
	if ((x >= scene->width) || (x < 0) || (y < 0) || y >= scene->height)
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
		{
			scene->current_file--;
			draw_buttons(scene->buttons, scene);
		}
	}
	else if (key == MLX_KEY_DOWN)
	{
		if (scene->current_file < 20 && scene->buttons[scene->current_file + 1].text) 
		{
			scene->current_file++;
			draw_buttons(scene->buttons, scene);
		}
	}
	else if (key == MLX_KEY_LEFT)
	{
		if (scene->current_file >= 10 && scene->buttons[scene->current_file - 10].text)
		{
			scene->current_file -= 10;
			draw_buttons(scene->buttons, scene);
		}
	}
	else if (key == MLX_KEY_RIGHT)
	{
		if (scene->current_file < 10 && scene->buttons[scene->current_file + 10].text)
		{
			scene->current_file += 10;
			draw_buttons(scene->buttons, scene);
		}		
	}
}

int		is_arrow_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_UP || key_data.key == MLX_KEY_DOWN
		|| key_data.key == MLX_KEY_LEFT || key_data.key == MLX_KEY_RIGHT)
		&& (key_data.action == MLX_PRESS || key_data.action == KEYDOWN))
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

void	main_loop(void *sc)
{
	t_vect		pixel_center;
	t_ray		ray;
	t_scene		*scene;
	char		*fps;
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	scene = sc;
	if (!scene->choose_file)
		return ;
	set_new_image(scene);
	while (y < scene->height)
	{
		x = 0;
		while (x < scene->width)
		{
			pixel_center = set_pixel_center(scene->camera, x,y);
			ray.dir = vect_subtract(pixel_center, scene->camera.origin);
			ray.origin = scene->camera.origin;
			safe_pixel_put(scene, x, y, get_rgba(0, 0, 250, (int)round((y / (float)scene->height) * 255)));
			x++;
		}
		y++;
	}
	fps = ft_itoa((int)round(1 / scene->mlx->delta_time));
	mlx_set_window_title(scene->mlx, fps);
	free(fps);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
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

void	draw_button_frame(t_scene *scene, t_coords i_pt, t_coords f_pt)
{
	float	x;
	float	y;

	x = i_pt.x;
	y = i_pt.y;
	while (y < i_pt.y + 3)
	{
		x = i_pt.x;
		while (x < f_pt.x)
		{
			safe_pixel_put(scene, (int)round(x), (int)round(y), DEF_COLOR);
			safe_pixel_put(scene, (int)round(x), (int)round(y + (f_pt.y - i_pt.y - 3)), DEF_COLOR);
			x++;
		}
		y++;
	}
	x = i_pt.x - 3;
	y = i_pt.y;
	while (y < f_pt.y)
	{
		x = i_pt.x - 3;
		while (x < i_pt.x)
		{
			safe_pixel_put(scene, (int)round(x), (int)round(y), DEF_COLOR);
			safe_pixel_put(scene, (int)round(x + (f_pt.x - i_pt.x)), (int)round(y), DEF_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_center_line(t_scene *scene)
{
	int	x;
	int	aux;
	int	y;

	aux = scene->width * 0.498;
	x = aux;
	y = scene->height * 0.05;
	while (y < scene->height * 0.95)
	{
		x = aux;
		while (x < scene->width * 0.502)
		{
			safe_pixel_put(scene, x, y, CYAN_GULF);
			x++;
		}
		y++;
	}
}

void	set_new_image(t_scene *scene)
{
	if (scene->image)
		mlx_delete_image(scene->mlx, scene->image);
	scene->image = mlx_new_image(scene->mlx, scene->width, scene->height);
}

void	draw_buttons(t_button *buttons, t_scene *scene)
{
	int	i;
	int	xy[2];

	i = 0;
	xy[0] = (int)round(buttons->i_pt.x);
	xy[1] = (int)round(buttons->i_pt.y);
	set_new_image(scene);
	while (i < 20)
	{
		if (i == scene->current_file && buttons[i].text)
			draw_button_frame(scene, buttons[i].i_pt, buttons[i].f_pt);
		if (buttons[i].text)
		{
			xy[0] = buttons[i].i_pt.x + scene->width * 0.03;
			xy[1] = buttons[i].f_pt.y - scene->height * 0.02;
			write_str(scene, buttons[i].text, xy, 5);
		}
		i++;
	}
	draw_center_line(scene);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
}

void	free_buttons(t_button *buttons)
{
	int	i;

	i = 0;
	while (i < 20)
	{
		if (buttons[i].text)
			free(buttons[i].text);
		i++;
	}
}

void	draw_file_menu(t_scene *scene)
{
	int				xy[2];
	int				i;
	size_t			aux;
	DIR 			*d;
	struct dirent	*dir;

	i = 0;
	aux = 0;
	xy[0] = scene->width * 0.1;
	xy[1] = scene->height * 0.075;
	ft_bzero(scene->buttons, sizeof(t_button) * 20);
	d = opendir("./maps");
	if (d) {
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_name[0] && dir->d_name[0] != '.' && ft_strnstr(dir->d_name, ".rt", ft_strlen(dir->d_name)))
			{
				aux = 0;
				while (dir->d_name[aux] != '.')
					aux++;
				if (aux != ft_strlen(dir->d_name))
					scene->buttons[i].text = ft_substr(dir->d_name, 0, aux);
				else
					scene->buttons[i].text = ft_strdup(dir->d_name);
				if (i > 9)
					xy[0] = scene->width * 0.6;
				scene->buttons[i].i_pt.x = xy[0];
				scene->buttons[i].i_pt.y = xy[1] + ((scene->height * 0.087) * (i % 10));
				scene->buttons[i].f_pt.x = scene->buttons[i].i_pt.x + scene->width * 0.3;
				scene->buttons[i].f_pt.y = scene->buttons[i].i_pt.y + scene->height * 0.07;
				i++;
			}
		}
	closedir(d);
	}
	draw_buttons(scene->buttons, scene);
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
	scene->camera.viewport_width = scene->camera.viewport_height * (scene->width / scene->height);
	scene->camera.vp_edge_horizntl = new_vect(scene->camera.viewport_width, 0, 0);
	scene->camera.vp_edge_vert = new_vect(0, (scene->camera.viewport_height) * -1, 0);
	scene->camera.pixel_delta_h = vect_simple_div(scene->camera.vp_edge_horizntl, scene->width);
	scene->camera.pixel_delta_v = vect_simple_div(scene->camera.vp_edge_vert, scene->width);
	scene->camera.viewport_origin.x = 0 - (scene->camera.vp_edge_horizntl.x / 2) - (scene->camera.vp_edge_vert.x / 2);	
	scene->camera.viewport_origin.y = 0 - (scene->camera.vp_edge_horizntl.y / 2) - (scene->camera.vp_edge_vert.y / 2);
	scene->camera.viewport_origin.z = 0 - (scene->camera.vp_edge_horizntl.z / 2) - (scene->camera.vp_edge_vert.z / 2) - scene->camera.view_distance;
	temp = vect_add(scene->camera.pixel_delta_h, scene->camera.pixel_delta_v);
	scene->camera.viewport_pixel0.x = scene->camera.viewport_origin.x + (0.5 * temp.x);
	scene->camera.viewport_pixel0.y = scene->camera.viewport_origin.y + (0.5 * temp.y);
	scene->camera.viewport_pixel0.z = scene->camera.viewport_origin.z + (0.5 * temp.z);
}

void	init_scene(t_scene *scene)
{
	scene->width = WINW;
	scene->height = WINH;
	scene->aspect_ratio = scene->width / scene->height;
	scene->choose_file = 1;
	scene->current_file = 0;
	scene->mlx = mlx_init(scene->width, scene->height, "miniRT", true);
	scene->image = mlx_new_image(scene->mlx, scene->width, scene->height);
	init_camera(scene);
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
	//free_buttons(scene.buttons);
	return (0);
}
