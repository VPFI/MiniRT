/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:51:13 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:25:50 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	remove_point_texture_offset_plane(t_vect *point, t_vect *texture_dims)
{
	if (point->x < 0.0)
		point->x = point->x + texture_dims->x
			+ (texture_dims->x * (int)(fabs(point->x / texture_dims->x)));
	if (point->y > 0.0)
		point->y = point->y - texture_dims->y
			- (texture_dims->y * (int)(point->y / texture_dims->y));
	if (point->x >= texture_dims->x)
		point->x = point->x
			- (texture_dims->x * (int)(point->x / texture_dims->x));
	if (fabs(point->y) >= texture_dims->y)
		point->y = point->y
			+ (texture_dims->y * (int)(fabs(point->y) / texture_dims->y));
}

void	set_bump_map_normal_plane(t_vect *point, t_texture *tx, t_vect *normal)
{
	t_texel		texel;
	uint8_t		*pixel;
	t_vect		texture_dims;

	texture_dims.x = tx->texture_dim;
	texture_dims.y = tx->texture_dim * (tx->texture->height / (float) tx->texture->width);
	remove_point_texture_offset_plane(point, &texture_dims);
	texel.x = f_clamp(point->x * (tx->texture->width / texture_dims.x), 0.0, tx->texture->width - 1);
	texel.y = f_clamp(fabs(point->y) * (tx->texture->height / texture_dims.y), 0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels	+ ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
}
