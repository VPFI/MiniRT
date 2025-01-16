/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:39:50 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 22:17:38 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "mlx/mlx_utils.h"
#include "path_tracer/scene/scene.h"
#include "selection_menu/buttons/buttons.h"
#include "selection_menu/utils/selector_utils.h"
#include "selection_menu/custom_writer/writer.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

void	draw_no_maps_found(t_scene *scene)
{
	uint32_t	x;	
	uint32_t	y;
	int			offset_x;
	int			offset_y;

	x = 0;
	y = 0;
	offset_x = 0;
	offset_y = 0;
	set_new_image(scene);
	while (y < scene->image->height)
	{
		x = 0;
		while (x < scene->image->width)
		{
			offset_x = (scene->image->width / 2) - (scene->menu_tx->texture->width / 2);
			offset_y = (scene->image->height / 2) - (scene->menu_tx->texture->height / 2);
			if (((int)x > fmin(offset_x, 0)) && x < ((scene->image->width / 2) + scene->menu_tx->texture->width / 2)
				&& ((int)y > fmin(offset_y, 0)) && y < ((scene->image->height / 2) + scene->menu_tx->texture->height / 2))
				safe_pixel_put_bres(scene, (int)round(x), (int)round(y),
					get_texture_color(scene->menu_tx, x - offset_x, y - offset_y));
			x++;
		}
		y++;
	}
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
}

static void	draw_headers(t_scene *scene)
{
	char	*aux;
	int		coords[3];
	char	*pagination;

	coords[0] = (scene->width / 2) - scene->width  * 0.08;
	coords[1] = scene->height * 0.05;
	coords[2] = 6;
	write_str(scene, "MiniRT", coords, DEF_COLOR);
	pagination = ft_itoa((int)(scene->current_file / 20) + 1);
	pagination = ft_strappend(&pagination, "\\");
	aux = ft_itoa((int)(scene->map_count / 20) + 1);
	pagination = ft_strappend(&pagination, aux);
	coords[0] = (scene->width / 2) - scene->width  * 0.0335;
	coords[1] = scene->height * 0.975;
	coords[2] = 8;
	write_str(scene, pagination, coords, DEF_COLOR);
	free(aux);
	free(pagination);
}

static void	draw_center_line(t_scene *scene)
{
	int		x;
	int		y;
	int		aux;


	aux = scene->width * 0.498;
	x = aux;
	y = scene->height * 0.1;
	while (y < scene->height * 0.9)
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

static void	draw_button_frame(t_scene *scene, t_coords i_pt, t_coords f_pt)
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

void	draw_buttons(t_button *buttons, t_scene *scene)
{
	int	i;
	int	page;
	int	xy[3];

	page = (int)(scene->current_file / 20);
	i = page * 20;
	xy[0] = (int)round(buttons->i_pt.x);
	xy[1] = (int)round(buttons->i_pt.y);
	xy[2] = 6;
	set_new_image(scene);
	while (i < (20 + (page * 20)))
	{
		if (i == scene->current_file && buttons[i].text)
			draw_button_frame(scene, buttons[i].i_pt, buttons[i].f_pt);
		if (buttons[i].text)
		{
			xy[0] = buttons[i].i_pt.x + scene->width * 0.02;
			xy[1] = buttons[i].f_pt.y - scene->height * 0.018;
			write_str(scene, buttons[i].text, xy, CYAN_GULF);
		}
		i++;
	}
	draw_headers(scene);
	draw_center_line(scene);
	mlx_image_to_window(scene->mlx, scene->image, 0, 0);
}
