/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:22:57 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 15:39:11 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "src/path_tracer/scene/ray/ray.h"
# include "src/path_tracer/scene/camera/camera.h"
# include "src/path_tracer/utils/vectors/vectors.h"
# include "src/path_tracer/scene/objects/figures/figures.h"
# include "src/path_tracer/scene/objects/material/material.h"
# include "src/path_tracer/scene/objects/texture/texture_objects.h"

typedef struct s_object t_object;

typedef struct s_hit_info
{
	t_vect		point;
	t_vect		normal;
	t_object	*object;
	float		t;
}				t_hit_info;

typedef struct s_object
{
	union s_figure 	figure;
	t_material		material;
	t_texture		*texture;
	t_fig_type		type;
	struct s_object	*next;
	bool			selected;
	bool			(*hit_func)(t_ray ray, t_figure figure, t_hit_info *hit_info, float *bounds);
	t_vect			(*get_origin)(t_object *object);
	t_vect			(*get_visual)(t_hit_info *hit_info);
	t_vect			(*get_normal)(t_hit_info *hit_info, t_figure *fig);
	void			(*edit_origin)(t_object *object, t_vect transformation);
	void			(*edit_orientation)(t_object *object, t_camera *camera, t_vect transformation);
	void			(*edit_dimensions)(t_object *object, t_vect transformation);
}					t_object;

bool		is_2d(t_object *object);
t_object	*last_object(t_object *objects);
t_vect		get_obj_color(t_hit_info *hit_info);
int			add_object(t_object **objects, t_object *new);

#endif