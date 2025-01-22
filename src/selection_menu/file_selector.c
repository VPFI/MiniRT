/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_selector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:50:57 by vpf               #+#    #+#             */
/*   Updated: 2025/01/22 19:57:37 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "mlx/mlx_utils.h"
#include "path_tracer/scene/scene.h"
#include "path_tracer/path_tracer.h"
#include "selection_menu/draw/draw_menu.h"
#include "error_management/error_management.h"
#include "mlx/MLX42/include/MLX42/MLX42.h"
#include <dirent.h>

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

static void	set_buttons_params(t_scene *scene, struct dirent *dir, int *xy)
{
	int		i;
	size_t aux;

	i = 0;
	aux = 0;
	while (dir->d_name[aux] != '.')
		aux++;
	if (aux != ft_strlen(dir->d_name))
	{
		if (aux > 11)
		{
			scene->buttons[i].text = ft_substr(dir->d_name, 0, 11);
			scene->buttons[i].text = ft_strappend(&scene->buttons[i].text, "\\");
		}
		else
			scene->buttons[i].text = ft_substr(dir->d_name, 0, aux);
	}
	else
		scene->buttons[i].text = ft_strdup(dir->d_name);
	if ((i % 20) > 9)
		xy[0] = scene->width * 0.55;
	else
		xy[0] = scene->width * 0.05;
	scene->buttons[i].i_pt.x = xy[0];
	scene->buttons[i].i_pt.y = xy[1] + ((scene->height * 0.087) * (i % 10));
	scene->buttons[i].f_pt.x = scene->buttons[i].i_pt.x + scene->width * 0.4;
	scene->buttons[i].f_pt.y = scene->buttons[i].i_pt.y + scene->height * 0.07;
	i++;	
}

static void	draw_available_maps(t_scene *scene)
{
	DIR				*d;
	struct dirent	*dir;
	int				xy[2];

	xy[0] = scene->width * 0.05;
	xy[1] = scene->height * 0.08;
	d = opendir("./assets/maps");
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			if (dir->d_name[0] && dir->d_name[0] != '.'
				&& ft_strnstr(dir->d_name, ".rt", ft_strlen(dir->d_name)))
			{
				set_buttons_params();
			}
			dir = readdir(d);
		}
		closedir(d);
	}
	draw_buttons(scene->buttons, scene);
}

void	display_file_menu(t_scene *scene)
{
	scene->map_count = count_maps();
	if (!scene->map_count)
	{
		draw_no_maps_found(scene);
		return ;
	}
	else
	{
		scene->buttons = ft_calloc(((int)(scene->map_count / 20) * 20)
		+ 20, sizeof(t_button));
		if (!scene->buttons)
			exit_err(ERR_MEM_MSG, "(malloc) Buttons", 1);
		draw_available_maps(scene);
	}
}
