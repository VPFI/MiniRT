/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:03:19 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 22:10:28 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	set_new_fig_disk(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.disk.center = *offset_origin;
	fig.disk.normal = vect_simple_mult(scene->camera.orientation, -1.0);
	fig.disk.radius = 0.5;
	init_disk(scene, fig, mat, NULL);
}

int	init_disk(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = DISK;
	new_obj->figure.disk.center = fig.disk.center;
	new_obj->figure.disk.normal = unit_vect(fig.disk.normal);
	new_obj->figure.disk.radius = fig.disk.radius;
	new_obj->texture = tx;
	new_obj->hit_func = hit_disk;
	new_obj->edit_origin = translate_disk;
	new_obj->edit_orientation = rotate_disk;
	new_obj->get_origin = get_origin_disk;
	new_obj->edit_dimensions = resize_disk;
	new_obj->get_visual = get_disk_pattern;
	new_obj->get_normal = get_disk_normal;
	new_obj->next = NULL;
	add_object(&scene->objects, new_obj);
	return (0);
}
