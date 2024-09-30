/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:26 by vperez-f          #+#    #+#             */
/*   Updated: 2024/09/30 21:56:55 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

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

void	key_down(mlx_key_data_t key_data, void *sc)
{
	t_scene	*scene;

	scene = sc;
	if (key_data.key == MLX_KEY_ESCAPE)
		close_all(scene);

}

void	main_loop(void *sc)
{
	static int	adv = 0;
	uint32_t	x;
	uint32_t	y;
	t_scene		*scene;
	char		*fps;
	int			color;

	scene = sc;
	if (!scene->choose_file)
		return ;
	x = 0;
	y = 0;
	color = get_rgba(0, (adv) % 255 ,0 ,255);
	if (scene->image)
		mlx_delete_image(scene->mlx, scene->image);
	scene->image = mlx_new_image(scene->mlx, scene->width / 2, scene->height / 2);
	while (y < scene->height / 2)
	{
		x = 0;
		while (x < scene->width / 2)
		{
			safe_pixel_put(scene, x, y, color);
			x++;
		}
		y++;
	}
	fps = ft_itoa((int)round(1 / scene->mlx->delta_time));
	mlx_set_window_title(scene->mlx, fps);
	free(fps);
	mlx_image_to_window(scene->mlx, scene->image, (0 + (adv)) % scene->width, 0);
	adv++;
}

void	resize_minirt(int32_t width, int32_t height, void *sc)
{
	t_scene *scene;

	scene = sc;
	scene->height = height;
	scene->width = width;
	mlx_resize_image(scene->image, scene->width, scene->height);
}

void	draw_file_menu(t_scene *scene)
{
	int	xy[2];
	DIR *d;
	struct dirent *dir;

	xy[0] = scene->width * 0.15;
	xy[1] = scene->height * 0.15;
	d = opendir(".");
	if (d) {
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_name[0] && dir->d_name[0] != '.')
			{
				write_str(scene, dir->d_name, xy, 4);
				xy[1] += (scene->height * 0.1);
			}
		}
	closedir(d);
	}
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	scene->choose_file = 0;
}

void	mouse_handle(mouse_key_t button, action_t action, modifier_key_t mods, void *sc)
{
	t_scene *scene;

	scene = sc;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		scene->choose_file = 1;
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_scene	scene;
	uint32_t x = 0;
	uint32_t y = 0;

	x = y;
	scene.width = WINW;
	scene.height = WINH;
	scene.choose_file = 0;
	scene.mlx = mlx_init(scene.width, scene.height, "miniRT", true);
	scene.image = mlx_new_image(scene.mlx, scene.width, scene.height);
	draw_file_menu(&scene);
	mlx_key_hook(scene.mlx, key_down, &scene);
	mlx_mouse_hook(scene.mlx, mouse_handle, &scene);
	mlx_resize_hook(scene.mlx, resize_minirt, &scene);
	mlx_loop_hook(scene.mlx, main_loop, &scene);
	mlx_loop(scene.mlx);
	if (scene.mlx)
		mlx_terminate(scene.mlx);
	return (0);
}
