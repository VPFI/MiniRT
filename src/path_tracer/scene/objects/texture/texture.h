/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:16:13 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 00:09:06 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "libraries/mlx/MLX42/include/MLX42/MLX42.h"

typedef struct s_texel
{
	int	x;
	int	y;
}		t_texel;

typedef struct s_texture
{
	char			*path;
	mlx_texture_t	*texture;
	float			texture_dim;
}					t_texture;

t_vect		translate_texture_to_normal(uint8_t *pixel);
t_texture	*get_texture(char *path, float texture_dim);
void		rotate_texture_normal(t_vect *point_normal, t_vect *normal);

#endif