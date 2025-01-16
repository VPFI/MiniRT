/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:40:48 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:42:48 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	rotate_texture_normal(t_vect *point_normal, t_vect *normal)
{
	t_vect	axis;
	float	angle;
	t_vect	ideal_normal;

	ideal_normal = new_vect(0.0, 0.0, 1.0);
	axis = vect_cross(ideal_normal, *point_normal);
	if (zero_vect(axis))
		return ;
	axis = unit_vect(axis);
	angle = acosf(f_clamp(vect_dot(ideal_normal, *point_normal), -1.0, 1.0));
	rotate_vector(normal, axis, angle);
}

t_vect	translate_texture_to_normal(uint8_t *pixel)
{
	t_vect	normal;
	t_color	pixel_color;

	pixel_color.x = *pixel / (float) 255;
	pixel_color.y = *(pixel + 1) / (float) 255;
	pixel_color.z = *(pixel + 2) / (float) 255;
	normal.x = (pixel_color.x / 0.5) - 1;
	normal.y = (pixel_color.y / 0.5) - 1;
	normal.z = (pixel_color.z / 0.5) - 1;
	return (normal);
}

t_texture	*get_texture(char *path, float texture_dim)
{
	t_texture	*res;

	if (!path)
		return (NULL);
	res = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!res)
		return (exit_err(ERR_MEM_MSG, "(calloc)", 1), NULL);
	res->path = ft_strdup(path);
	if (!res->path)
		return (free_texture(&res), exit_err(ERR_MEM_MSG, "(malloc)", 2), NULL);
	res->texture = mlx_load_png(path);
	if (!res->texture)
		return (exit_err(ERR_MEM_MSG, res->path, 2), free_texture(&res), NULL);
	res->texture_dim = texture_dim;
	return (res);
}
