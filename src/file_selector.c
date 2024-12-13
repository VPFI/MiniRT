/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_selector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:50:57 by vpf               #+#    #+#             */
/*   Updated: 2024/12/13 23:15:03 by vperez-f         ###   ########.fr       */
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
	int	page;
	int	xy[2];

	page = (int)(scene->current_file / 20);
	i = page * 20;
	printf("current %i || page: %i|| i: %i |||||| %i \n\n", scene->current_file, page, i, (20 + (page * 20)));
	xy[0] = (int)round(buttons->i_pt.x);
	xy[1] = (int)round(buttons->i_pt.y);
	set_new_image(scene);
	while (i < (20 + (page * 20)))
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

void	free_buttons(t_button *buttons, int n)
{
	int	i;

	i = 0;
	if (!buttons)
		return ;
	while (i < n)
	{
		if (buttons[i].text)
			free(buttons[i].text);
		i++;
	}
	free(buttons);
}

int	count_maps(void)
{
	int				i;
	DIR 			*d;
	struct dirent	*dir;

	i = 0;
	d = opendir("./maps");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_name[0] && dir->d_name[0] != '.' && ft_strnstr(dir->d_name, ".rt", ft_strlen(dir->d_name)))
			{
				i++;
			}
		}
		closedir(d);
	}
	return (i);
}

int	get_texture_color(t_texture *tx, uint32_t x, uint32_t y)
{
	uint8_t *pixel;

	if (x < 0 || y < 0 || x >= tx->texture->width || y >= tx->texture->height)
		return (0);
	pixel = tx->texture->pixels	+ ((4 * tx->texture->width) * y) + (4 * x);
	return (get_rgba(*pixel, *(pixel + 1), *(pixel + 2), 0xFF));
}

void	draw_no_maps_found(t_scene *scene)
{
	uint32_t	x;
	int			offset_x;
	uint32_t	y;
	int			offset_y;
	t_texture	*tx;

	x = 0;
	offset_x = 0;
	y = 0;
	offset_y = 0;
	tx = malloc(sizeof(t_texture));
	if (!tx)
		exit (1);
	tx->path = ft_strdup("./textures/Sad_face1.png");
	tx->texture = mlx_load_png(tx->path);
	tx->texture_dim = tx->texture->width;
	if (!tx->texture)
		exit (1);
	tx->texture_dim = tx->texture->width;
	set_new_image(scene);
	while (y < scene->image->height)
	{
		x = 0;
		while (x < scene->image->width)
		{
			offset_x = fmin(((scene->image->width / 2) - tx->texture->width / 2), 0);
			offset_y = fmin(((scene->image->height / 2) - tx->texture->height / 2), 0);
			if (((int)x > offset_x) && x < ((scene->image->width / 2) + tx->texture->width / 2)
				&& ((int)y > offset_y) && y < ((scene->image->height / 2) + tx->texture->height / 2))
				safe_pixel_put_bres(scene, (int)round(x), (int)round(y), get_texture_color(tx, x - ((scene->image->width / 2) - tx->texture->width / 2), y - ((scene->image->height / 2) - tx->texture->height / 2)));
			x++;
		}
		y++;
	}
	free_texture(&tx);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
}

void	draw_file_menu(t_scene *scene)
{
	int				i;
	int				xy[2];
	size_t			aux;
	DIR 			*d;
	struct dirent	*dir;

	i = 0;
	aux = 0;
	scene->map_count = count_maps();
	if (!scene->map_count)
	{
		draw_no_maps_found(scene);
		return ;
	}
	scene->buttons = ft_calloc(((int)(scene->map_count / 20) * 20) + 20, sizeof(t_button));
	if (!scene->buttons)
		exit(1);
	xy[0] = scene->width * 0.05;
	xy[1] = scene->height * 0.075;
	d = opendir("./maps");
	if (d)
	{
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
		}
		closedir(d);
	}
	draw_buttons(scene->buttons, scene);
}
