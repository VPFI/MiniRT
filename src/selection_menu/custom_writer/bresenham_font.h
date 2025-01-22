/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_font.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:54:53 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 15:06:34 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRESENHAM_FONT_H
# define BRESENHAM_FONT_H

# include "path_tracer/scene/scene.h"
# include "selection_menu/utils/selector_utils.h"

typedef struct s_bresenham
{
	t_coords	i_pt;
	t_coords	f_pt;
	int			d;
	int			d2;
	int			dx;
	int			dy;
	int			i_one;
	int			i_two;
	int			n;
	int			max;
	int			color;
	float		fade_comp[4];
}				t_bresenham;

void	init_bresenham_line_font(t_scene *scene, t_coords *i_pt,
			t_coords *f_pt, int color);

#endif