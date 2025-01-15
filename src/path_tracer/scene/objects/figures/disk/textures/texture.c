/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:51:13 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:32:22 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



void	remove_point_texture_offset_disk(t_vect *point, t_vect *texture_dims, float *point_arc, float base_height)
{
	if (point->x < 0.0)
	{
		*point_arc = (-1 * (*point_arc)) + texture_dims->x + (texture_dims->x * (int)(*point_arc / texture_dims->x));
	}
	if (*point_arc >= texture_dims->x)
	{
		*point_arc = *point_arc - (texture_dims->x * (int)(*point_arc / texture_dims->x));
	}
	if (0.0 < texture_dims->y)
	{
		point->z = base_height;
	}
	if (base_height >= texture_dims->y)
	{
		point->z = (base_height) - (texture_dims->y * (int)((base_height) / texture_dims->y));
	}
}

void	set_bump_map_normal_disk(t_figure *fig, t_vect *point, t_vect *normal, t_texture *tx)
{
	t_base_params	bp;
	t_texel			texel;
	uint8_t			*pixel;
	t_vect			texture_dims;

	set_base_params(&bp, point, fig->disk.radius);
	texture_dims.x = tx->texture_dim * (bp.point_radius / fig->disk.radius);
	texture_dims.y = tx->texture_dim * (tx->texture->height / (float)tx->texture->width);
	remove_point_texture_offset_disk(point, &texture_dims, &bp.point_arc, bp.base_height);
	texel.x = f_clamp(bp.point_arc * (tx->texture->width / texture_dims.x), 0.0, tx->texture->width - 1);
	texel.y = f_clamp(point->z * (tx->texture->height / texture_dims.y), 0.0, tx->texture->height - 1);
	pixel = tx->texture->pixels	+ ((4 * tx->texture->width) * texel.y) + (4 * texel.x);
	*normal = translate_texture_to_normal(pixel);
}
