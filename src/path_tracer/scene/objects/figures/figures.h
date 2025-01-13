/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:37:39 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/11 22:57:58 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIGURES_H
# define FIGURES_H

# include "src/path_tracer/utils/vectors/vectors.h"

struct t_object;

typedef enum e_fig_type
{
	SPHERE = 0,
	PLANE = 1,
	QUAD = 2,
	BOX = 3,
	DISK = 4,
	CYLINDER = 5,
	CONE = 6,
	LIGHT = 7,
}			t_fig_type;

typedef struct s_point_light
{
	t_vect		location;
	float		radius_shadow;
}				t_point_light;

typedef struct s_cylinder
{
	t_vect		center;
	t_vect		normal;
	float		radius;
	float		height;
}				t_cylinder;

typedef struct s_cone
{
	t_vect		center;
	t_vect		normal;
	float		radius;
	float		height;
}				t_cone;

typedef struct s_sphere
{
	t_vect		center;
	float		radius;
}				t_sphere;

typedef struct s_plane
{
	t_vect		center;
	t_vect		normal;
}				t_plane;

typedef struct s_quad
{
	t_vect		u_vect;
	t_vect		v_vect;
	t_vect		normal;
	t_vect		center;
}				t_quad;

typedef struct s_box
{
	t_vect		u_vect;
	t_vect		v_vect;
	t_vect		dimensions;
	t_vect		center;
	struct t_object	*faces;
}				t_box;

typedef struct s_disk
{
	t_vect		center;
	t_vect		normal;
	float		radius;
}				t_disk;

typedef union s_figure
{
	t_sphere		sphere;
	t_plane			plane;
	t_quad			quad;
	t_box			box;
	t_disk			disk;
	t_cylinder		cylinder;
	t_cone			cone;
	t_point_light	p_light;
}					t_figure;

#endif