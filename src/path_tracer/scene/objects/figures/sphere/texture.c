/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:51:13 by vpf               #+#    #+#             */
/*   Updated: 2024/12/24 23:51:48 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	remove_point_texture_offset_sphere(t_vect *point, float *polar_coords, t_vect *texture_dims)
{
	if (point->x < 0.0)
		polar_coords[LATITUDE] = -polar_coords[LATITUDE] + texture_dims->x
			+ (texture_dims->x * (int)(polar_coords[LATITUDE] / texture_dims->x));
	if (point->y > 0.0)
		polar_coords[LONGITUDE] = -polar_coords[LONGITUDE] + texture_dims->y
			+ (texture_dims->y * (int)(polar_coords[LONGITUDE] / texture_dims->y));
	if (polar_coords[LATITUDE] >= texture_dims->x)
		polar_coords[LATITUDE] = polar_coords[LATITUDE]
			- (texture_dims->x * (int)(polar_coords[LATITUDE] / texture_dims->x));
	if (polar_coords[LONGITUDE] >= texture_dims->y)
		polar_coords[LONGITUDE] = polar_coords[LONGITUDE]
			- (texture_dims->y * (int)(polar_coords[LONGITUDE] / texture_dims->y));
}

void	rotate_texture_normal_sphere(t_vect *point, t_vect *normal)
{
	t_vect	point_normal;

	point_normal = unit_vect(*point);
	rotate_texture_normal(&point_normal, normal);
}

void	set_bump_map_normal_sphere(t_hit_info *hit_info, t_vect *point, t_texture *tx, t_vect *normal)
{
	t_texel	texel;
	uint8_t	*pixel;
	float	point_radius;
	t_vect	texture_dims;
	float	polar_coord[2];

	set_polar_coords(point, &hit_info->object->figure, polar_coord);
	point_radius = sqrtf(pow(point->x, 2) + pow(point->z, 2));
	texture_dims.x = tx->texture_dim * (point_radius / hit_info->object->figure.sphere.radius);
	texture_dims.y = tx->texture_dim * (tx->texture->height / (float)tx->texture->width);
	remove_point_texture_offset_sphere(point, polar_coord, &texture_dims);
	texel.x = f_clamp(polar_coord[LATITUDE] * (tx->texture->width / texture_dims.x), 0.0, tx->texture->width - 1);
	texel.y = f_clamp(polar_coord[LONGITUDE] * (tx->texture->height/ texture_dims.y), 0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels	+ ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
	rotate_texture_normal_sphere(point, normal);
}