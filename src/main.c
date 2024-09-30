/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:26 by vperez-f          #+#    #+#             */
/*   Updated: 2024/09/30 20:51:02 by vperez-f         ###   ########.fr       */
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
	t_scene	*scene;
	char	*fps;

	x = 0;
	y = 0;
	scene = sc;
	if (scene->image)
		mlx_delete_image(scene->mlx, scene->image);
	scene->image = mlx_new_image(scene->mlx, scene->width / 2, scene->height / 2);
	while (y < scene->height / 2)
	{
		x = 0;
		while (x < scene->width / 2)
		{
			safe_pixel_put(scene, x, y, get_rgba(0, (adv) % 255 ,0 ,255));
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
	main_loop(scene);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_scene	scene;
	uint32_t x = 0;
	uint32_t y = 0;

	x = y;
	scene.width = 1500;
	scene.height = 1000;
	scene.mlx = mlx_init(scene.width, scene.height, "miniRT", true);
	scene.image = mlx_new_image(scene.mlx, scene.width, scene.height);
	memset(scene.image->pixels, 255, scene.width * scene.height * sizeof(int32_t));
	mlx_image_to_window(scene.mlx, scene.image, 0, 0);
	mlx_key_hook(scene.mlx, key_down, &scene);
	mlx_resize_hook(scene.mlx, resize_minirt, &scene);
	mlx_loop_hook(scene.mlx, main_loop, &scene);
	mlx_loop(scene.mlx);
	if (scene.mlx)
		mlx_terminate(scene.mlx);
	return (0);
}
