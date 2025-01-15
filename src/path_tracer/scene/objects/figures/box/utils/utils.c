/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:48:26 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 22:08:04 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	add_box_face(t_object *box, t_figure face, t_material mat)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2));
	new_obj->type = QUAD;
	new_obj->figure.quad.center = face.quad.center;
	new_obj->figure.quad.u_vect = face.quad.u_vect;
	new_obj->figure.quad.v_vect = face.quad.v_vect;
	new_obj->figure.quad.normal = unit_vect(vect_cross(face.quad.u_vect, face.quad.v_vect));
	new_obj->material = mat;
	if (box->texture)
		new_obj->texture = get_texture(box->texture->path, box->texture->texture_dim);
	else
		new_obj->texture = NULL;
	new_obj->hit_func = hit_quad;
	new_obj->edit_origin = translate_quad;
	new_obj->edit_orientation = rotate_quad;
	new_obj->get_origin = get_origin_quad;
	new_obj->edit_dimensions = resize_quad;
	new_obj->get_visual = get_quad_pattern;
	new_obj->get_normal = get_quad_normal;
	new_obj->next = NULL;
	add_object(&box->figure.box.faces, new_obj);
}
