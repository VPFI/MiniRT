/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_selector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:50:57 by vpf               #+#    #+#             */
/*   Updated: 2024/10/09 17:04:09 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"


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
			safe_pixel_put_bres(scene, (int)round(x), (int)round(y), DEF_COLOR);
			safe_pixel_put_bres(scene, (int)round(x), (int)round(y + (f_pt.y - i_pt.y - 3)), DEF_COLOR);
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
			safe_pixel_put_bres(scene, (int)round(x), (int)round(y), DEF_COLOR);
			safe_pixel_put_bres(scene, (int)round(x + (f_pt.x - i_pt.x)), (int)round(y), DEF_COLOR);
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
			safe_pixel_put_bres(scene, x, y, CYAN_GULF);
			x++;
		}
		y++;
	}
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
