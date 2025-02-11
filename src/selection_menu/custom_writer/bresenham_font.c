/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_font.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:49:27 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 15:07:54 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx_utils.h"
#include "path_tracer/scene/scene.h"
#include "selection_menu/utils/selector_utils.h"
#include "selection_menu/custom_writer/bresenham_font.h"
#include <math.h>

static void	calculate_bresenham_font(t_scene *scene, t_bresenham *bres)
{
	int	res_x;
	int	res_y;

	res_x = bres->i_pt.x;
	res_y = bres->i_pt.y;
	while (!(res_x == bres->f_pt.x) || !(res_y == bres->f_pt.y))
	{
		safe_pixel_put_bres(scene, res_x, res_y, bres->color);
		bres->d2 = bres->d * 2;
		if (bres->d2 >= bres->dy)
		{
			bres->d += bres->dy;
			res_x += bres->i_one;
		}
		if (bres->d2 <= bres->dx)
		{
			bres->d += bres->dx;
			res_y += bres->i_two;
		}
	}
	safe_pixel_put_bres(scene, res_x, res_y, bres->color);
}

void	init_bresenham_line_font(t_scene *scene, t_coords *i_pt,
	t_coords *f_pt, int color)
{
	t_bresenham	bres;

	bres.i_pt.x = (int)round(i_pt->x);
	bres.i_pt.y = (int)round(i_pt->y);
	bres.i_pt.color = 0x00000000;
	bres.f_pt.x = (int)round(f_pt->x);
	bres.f_pt.y = (int)round(f_pt->y);
	bres.f_pt.color = 0x00000000;
	bres.color = color;
	bres.i_one = -1;
	bres.i_two = -1;
	bres.dx = fabs(bres.f_pt.x - bres.i_pt.x);
	bres.dy = -fabs(bres.f_pt.y - bres.i_pt.y);
	if (bres.i_pt.x < bres.f_pt.x)
		bres.i_one = 1;
	if (bres.i_pt.y < bres.f_pt.y)
		bres.i_two = 1;
	bres.d = bres.dx + bres.dy;
	calculate_bresenham_font(scene, &bres);
}
