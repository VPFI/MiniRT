/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:51:13 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:40:36 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	rotate_texture_normal_cylinder(t_vect *point, t_vect *normal)
{
	t_vect	point_normal;

	point_normal = *point;
	point_normal.z = 0;
	point_normal = unit_vect(point_normal);
	rotate_texture_normal(&point_normal, normal);
}

void	remove_point_texture_offset_cylinder(t_vect *point, float *arc, t_vect *texture_dims)
{
	if (point->x < 0.0)
		*arc = -*arc + texture_dims->x + (texture_dims->x * (int)(*arc / texture_dims->x));
	if (point->z < 0.0)
		point->z = point->z + texture_dims->y + (texture_dims->y * (int)(fabs(point->z) / texture_dims->y));
	if (*arc >= texture_dims->x)
		*arc = *arc	- (texture_dims->x * (int)(*arc / texture_dims->x));
	if (point->z >= texture_dims->y)
		point->z = point->z	- (texture_dims->y * (int)(point->z / texture_dims->y));
}

void	set_bump_map_normal_cylinder(t_vect *point, t_vect *normal, t_texture *tx, t_figure *fig)
{
	float	arc;
	float	angle;
	t_texel	texel;
	uint8_t	*pixel;
	t_vect	texture_dims;

	texture_dims.x = tx->texture_dim;
	texture_dims.y = tx->texture_dim * (tx->texture->height / (float) tx->texture->width);
	angle = get_point_angle(point);
	arc = angle * fig->cylinder.radius;
	remove_point_texture_offset_cylinder(point, &arc, &texture_dims);
	texel.x = f_clamp(arc * (tx->texture->width / texture_dims.x), 0.0, tx->texture->width - 1);
	texel.y = f_clamp(point->z * (tx->texture->height / texture_dims.y), 0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels + ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
	rotate_texture_normal_cylinder(point, normal);
}
