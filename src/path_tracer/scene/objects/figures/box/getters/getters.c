/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:45:46 by vpf               #+#    #+#             */
/*   Updated: 2025/01/10 18:06:03 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_object	*get_box_face(t_hit_info *hit_info, int *face_index)
{
	t_vect		compare_vect;
	t_vect		normal;
	t_object	*face;

	face = hit_info->object->figure.box.faces;
	while (face)
	{
		compare_vect = vect_subtract(hit_info->point, face->get_origin(face));
		normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
		if (fabsf(vect_dot(compare_vect, normal)) < 1e-4)
		{
			return (face);
		}
		if (face_index)
			(*face_index)++;
		face = face->next;
	}
	return (NULL);
}

t_vect	get_box_pattern(t_hit_info *hit_info)
{
	int			face_index;
	t_hit_info	face_hit_info;

	face_index = 0;
	if (hit_info->object->material.pattern)
	{
		face_hit_info = *hit_info;
		face_hit_info.object = get_box_face(hit_info, &face_index);
		face_hit_info.object->material.color = hit_info->object->material.color;
		if (face_hit_info.object)
			return (get_face_pattern(&face_hit_info, &hit_info->object->figure.box.dimensions, face_index));
		else
			return (hit_info->object->material.color);
	}
	else
	{
		return (hit_info->object->material.color);
	}
}

t_vect	get_origin_box(t_object *object)
{
	return (object->figure.box.center);
}

t_vect	get_box_normal(t_hit_info *hit_info, t_figure *fig)
{
	t_hit_info	face_hit_info;

	(void)fig;
	face_hit_info = *hit_info;
	face_hit_info.object = get_box_face(hit_info, NULL);
	return (face_hit_info.object->get_normal(&face_hit_info, &face_hit_info.object->figure));
}
