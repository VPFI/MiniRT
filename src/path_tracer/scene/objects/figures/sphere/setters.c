/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:03:19 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 22:08:44 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	set_new_fig_sphere(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_material();
	fig.sphere.center = *offset_origin;
	fig.sphere.radius = 0.5;
	init_sphere(scene, fig, mat, NULL);
}

int	init_sphere(t_scene *scene, t_figure fig, t_material mat, t_texture *tx)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = SPHERE;
	new_obj->figure.sphere.center = fig.sphere.center;
	new_obj->figure.sphere.radius = fig.sphere.radius;
	new_obj->texture = tx;
	new_obj->hit_func = hit_sphere;
	new_obj->edit_origin = translate_sphere;
	new_obj->edit_orientation = rotate_sphere;
	new_obj->get_origin = get_origin_sphere;
	new_obj->edit_dimensions = resize_sphere;
	new_obj->get_visual = get_sphere_pattern;
	new_obj->get_normal = get_sphere_normal;
	new_obj->next = NULL;
	add_object(&scene->objects, new_obj);
	return (0);
}