/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:33:10 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:41:28 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	belongs_to_base(t_vect point, t_vect center, t_vect normal, float height)
{
	t_vect		top_to_point;
	t_vect		bottom_to_point;
	float		dot_top;
	float		dot_bottom;

	top_to_point = vect_add(center, vect_simple_mult(normal, height));
	top_to_point = vect_subtract(point, top_to_point);
	top_to_point = unit_vect(top_to_point);
	bottom_to_point = vect_subtract(center, vect_simple_mult(normal, height));
	bottom_to_point = vect_subtract(point, bottom_to_point);
	bottom_to_point = unit_vect(bottom_to_point);
	dot_top = vect_dot(normal, top_to_point);
	dot_bottom = vect_dot(normal, bottom_to_point);
	if (fabs(dot_top) > 0.0001 && fabs(dot_bottom) > 0.0001)
		return (0);
	if (fabs(dot_top) < 0.0001)
		return (1);
	else
		return (-1);
}


void	set_base_params(t_base_params *params, t_vect *point, float radius)
{
	params->point_to_base = *point;
	params->point_to_base.z = 0.0;
	params->point_radius = vect_length(params->point_to_base);
	params->point_to_base = unit_vect(params->point_to_base);
	params->point_to_base = clamp_vect(params->point_to_base, -1.0, 1.0);
	params->point_arc = acosf(params->point_to_base.y) * params->point_radius;
	params->base_height = radius - params->point_radius;
}

void	remove_point_texture_offset_base(t_vect *point,	t_vect *texture_dims, t_base_params *bp, float base_distance)
{
	if (point->x < 0.0)
		bp->point_arc = -bp->point_arc + texture_dims->x
			+ (texture_dims->x * (int)(bp->point_arc / texture_dims->x));
	if (bp->point_arc >= texture_dims->x)
		bp->point_arc = bp->point_arc
			- (texture_dims->x * (int)(bp->point_arc / texture_dims->x));
	if (base_distance < 0.0)
		point->z = (base_distance - bp->base_height)
			+ texture_dims->y
			+ (texture_dims->y * (int)((fabs(base_distance)
						+ bp->base_height) / texture_dims->y));
	if (base_distance >= 0.0
		&& base_distance < texture_dims->y)
		point->z = base_distance + bp->base_height;
	if (base_distance >= 0.0
		&& base_distance + bp->base_height >= texture_dims->y)
		point->z = (base_distance + bp->base_height)
			- (texture_dims->y * (int)((base_distance
						+ bp->base_height) / texture_dims->y));
}

void	set_bump_map_normal_base(t_vect *point, t_vect *normal, t_texture *tx, float radius, float base_distance)
{
	t_base_params	bp;
	t_texel			texel;
	uint8_t			*pixel;
	t_vect			texture_dims;

	set_base_params(&bp, point, radius);
	texture_dims.x = tx->texture_dim * (bp.point_radius / radius);
	texture_dims.y = tx->texture_dim * (tx->texture->height / (float) tx->texture->width);
	remove_point_texture_offset_base(point, &texture_dims, &bp, base_distance);
	texel.x = f_clamp(bp.point_arc * (tx->texture->width / texture_dims.x), 0.0, tx->texture->width - 1);
	texel.y = f_clamp(point->z * (tx->texture->height / texture_dims.y), 0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels + ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
}
