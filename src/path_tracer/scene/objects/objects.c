/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:56:04 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/24 00:59:15 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path_tracer/scene/objects/objects.h"
#include <stdbool.h>

t_vect	get_obj_color(t_hit_info *hit_info)
{
	if (hit_info->object->material.pattern)
		return (hit_info->object->get_visual(hit_info));
	else
		return (hit_info->object->material.color);
}

bool	is_2d(t_object *object)
{
	if (object->type == PLANE || object->type == QUAD || object->type == DISK)
	{
		return (true);
	}
	return (false);
}

t_object	*last_object(t_object *objects)
{
	if (objects)
	{
		if (objects->next)
			return (last_object(objects->next));
	}
	return (objects);
}

int	add_object(t_object **objects, t_object *new)
{
	t_object	*last_obj;

	if (objects)
	{
		if ((*objects))
		{
			last_obj = last_object((*objects));
			last_obj->next = new;
		}
		else
			(*objects) = new;
	}
	return (0);
}
