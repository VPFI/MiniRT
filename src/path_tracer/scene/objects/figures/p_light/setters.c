/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 22:03:19 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 22:11:30 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	set_new_fig_p_light(t_scene *scene, t_vect *offset_origin)
{
	t_figure	fig;
	t_material	mat;

	mat = new_standard_plight();
	fig.p_light.location = *offset_origin;
	fig.p_light.radius_shadow = 1.0;
	init_p_light(scene, fig, mat);
}


int	init_p_light(t_scene *scene, t_figure fig, t_material mat)
{
	t_object 	*new_obj;

	new_obj = (t_object *)ft_calloc(1, sizeof(t_object));
	if (!new_obj)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 2), 2);
	new_obj->material = mat;
	deselect_objects(scene->objects, scene->lights, &scene->object_selected);
	new_obj->selected = true;
	scene->object_selected = true;
	new_obj->type = LIGHT;
	new_obj->figure.p_light.location = fig.p_light.location;
	new_obj->figure.p_light.radius_shadow = fig.p_light.radius_shadow;
	new_obj->texture = NULL;
	new_obj->hit_func = hit_point_light;
	new_obj->edit_origin = translate_point_light;
	new_obj->edit_orientation = rotate_sphere;
	new_obj->get_origin = get_origin_point_light;
	new_obj->edit_dimensions = resize_point_light;
	new_obj->get_visual = get_light_pattern;
	new_obj->get_normal = get_light_normal;
	new_obj->next = NULL;
	add_object(&scene->lights, new_obj);
	return (0);
}