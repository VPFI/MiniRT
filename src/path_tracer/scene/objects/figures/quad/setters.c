/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:03:19 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 22:09:42 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	set_new_fig_quad(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.quad.center = *offset_origin;
	fig.quad.u_vect = scene->camera.u;
	fig.quad.v_vect = scene->camera.v;
	init_quad(scene, fig, mat, NULL);
}

int	init_quad(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = QUAD;
	new_obj->figure.quad.center = fig.quad.center;
	new_obj->figure.quad.u_vect = fig.quad.u_vect;
	new_obj->figure.quad.v_vect = fig.quad.v_vect;
	new_obj->figure.quad.normal = unit_vect(vect_cross(fig.quad.u_vect, fig.quad.v_vect));
	new_obj->texture = tx;
	new_obj->hit_func = hit_quad;
	new_obj->edit_origin = translate_quad;
	new_obj->edit_orientation = rotate_quad;
	new_obj->get_origin = get_origin_quad;
	new_obj->edit_dimensions = resize_quad;
	new_obj->get_visual = get_quad_pattern;
	new_obj->get_normal = get_quad_normal;
	new_obj->next = NULL;
	add_object(&scene->objects, new_obj);
	return (0);
}