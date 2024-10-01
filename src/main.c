/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:26 by vperez-f          #+#    #+#             */
/*   Updated: 2024/10/01 18:09:24 by vperez-f         ###   ########.fr       */
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
	mlx_image_to_window(scene->mlx, scene->image, adv % scene->width, 0);
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

void	draw_button_frame(t_scene *scene, t_coords i_pt, t_coords f_pt)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (i_pt.y < f_pt.y)
	{
		i_pt.x = 0;
		while (i_pt.x < f_pt.x)
		{
			safe_pixel_put(scene, (int)round(i_pt.x), (int)round(i_pt.y), DEF_COLOR);
			i_pt.x++;
		}
		i_pt.y++;
	}
}

void	draw_buttons(t_button *buttons, t_scene *scene)
{
	int	i;

	i = 0;
	printf("-----------------------------------------------------------\n");
	while (i < 20)
	{
		printf("akjhdkajdhasd || I: %i:::::%f\n", i, buttons[i].i_pt.x);
		printf("akjhdkajdhasd || FFFF: %i:::::%f\n", i, buttons[i].f_pt.x);
		draw_button_frame(scene, buttons[i].i_pt, buttons[i].f_pt);
		i++;
	}
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
	int	xy[2];
	int	i;
	DIR *d;
	struct dirent *dir;
	t_button	buttons[20];

	i = 0;
	xy[0] = scene->width * 0.1;
	xy[1] = scene->height * 0.15;
	ft_bzero(buttons, sizeof(t_button) * 20);
	d = opendir("./maps");
	if (d) {
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_name[0] && dir->d_name[0] != '.')
			{
				buttons[i].text = ft_strdup(dir->d_name);
				if (i > 9)
					xy[0] = scene->width * 0.75;
				buttons[i].i_pt.x = xy[0];
				printf("akjhdkajdhasd || I: %i:::::%f\n", i, buttons[i].i_pt.x);
				buttons[i].i_pt.y = xy[1] + (xy[1] * (i % 10));
				buttons[i].f_pt.x = buttons[i].i_pt.x + scene->width * 0.2;
				printf("akjhdkajdhasd || FFFF: %i:::::%f\n", i, buttons[i].f_pt.x);
				buttons[i].f_pt.y = buttons[i].i_pt.y + scene->height * 0.1;
				i++;
			}
		}
	closedir(d);
	}
	draw_buttons(buttons, scene);
	free_buttons(buttons);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
	scene->choose_file = 0;
}

void	mouse_handle(mouse_key_t button, action_t action, modifier_key_t mods, void *sc)
{
	t_scene *scene;

	scene = sc;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		scene->choose_file = 1;
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
