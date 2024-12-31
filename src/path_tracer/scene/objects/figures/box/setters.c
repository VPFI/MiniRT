/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:03:19 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 22:09:55 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	set_new_fig_box(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.box.center = *offset_origin;
	fig.box.u_vect = scene->camera.u;
	fig.box.v_vect = scene->camera.v;
	fig.box.dimensions = new_vect(1.0, 1.0, 1.0);
	init_box(scene, fig, mat, NULL);
}

void	recalculate_faces(t_object *box, t_vect dimensions)
{
	t_object	*face;
	t_vect		normal;
	t_vect		anti_normal;

	face = box->figure.box.faces;
	normal = unit_vect(vect_cross(box->figure.box.u_vect, box->figure.box.v_vect));
	anti_normal = vect_simple_mult(normal, -1);

	face->figure.quad.u_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, dimensions.y);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(normal, dimensions.z * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(anti_normal, dimensions.z * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, dimensions.y);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.u_vect, dimensions.x * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.u_vect, -1 * dimensions.x * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.u_vect, -1 * dimensions.x);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.v_vect, dimensions.y * 0.5));
	face = face->next;

	face->figure.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	face->figure.quad.v_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	face->figure.quad.normal = unit_vect(vect_cross(face->figure.quad.u_vect, face->figure.quad.v_vect));
	face->figure.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y * 0.5));
	face = face->next;
}

void	init_faces(t_object *box, t_material mat, t_vect dimensions)
{
	t_figure	fig;
	t_vect		normal;
	t_vect		anti_normal;

	normal = unit_vect(vect_cross(box->figure.box.u_vect, box->figure.box.v_vect));
	anti_normal = vect_simple_mult(normal, -1);

	fig.quad.u_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, dimensions.y);
	fig.quad.center = vect_add(box->figure.box.center, vect_simple_mult(normal, dimensions.z * 0.5));
	add_box_face(box, fig, mat);

	fig.quad.u_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y);
	fig.quad.center = vect_add(box->figure.box.center, vect_simple_mult(anti_normal, dimensions.z * 0.5));
	add_box_face(box, fig, mat);

	fig.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, dimensions.y);
	fig.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.u_vect, dimensions.x * 0.5));
	add_box_face(box, fig, mat);

	fig.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y);
	fig.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.u_vect, -1 * dimensions.x * 0.5));
	add_box_face(box, fig, mat);

	fig.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.u_vect, -1 * dimensions.x);
	fig.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.v_vect, dimensions.y * 0.5));
	add_box_face(box, fig, mat);

	fig.quad.u_vect = vect_simple_mult(anti_normal, dimensions.z);
	fig.quad.v_vect = vect_simple_mult(box->figure.box.u_vect, dimensions.x);
	fig.quad.center = vect_add(box->figure.box.center, vect_simple_mult(box->figure.box.v_vect, -1 * dimensions.y * 0.5));
	add_box_face(box, fig, mat);
}

int	init_box(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = BOX;
	new_obj->figure.box.center = fig.box.center;
	new_obj->figure.box.u_vect = fig.box.u_vect;
	new_obj->figure.box.v_vect = fig.box.v_vect;
	new_obj->figure.box.dimensions = fig.box.dimensions;
	new_obj->figure.box.faces = NULL;
	new_obj->texture = tx;
	new_obj->hit_func = hit_box;
	new_obj->edit_origin = translate_box;
	new_obj->edit_orientation = rotate_box;
	new_obj->get_origin = get_origin_box;
	new_obj->edit_dimensions = resize_box;
	new_obj->get_visual = get_box_pattern;
	new_obj->get_normal = get_box_normal;
	new_obj->next = NULL;
	init_faces(new_obj, new_obj->material, new_obj->figure.box.dimensions);
	add_object(&scene->objects, new_obj);
	return (0);
}
