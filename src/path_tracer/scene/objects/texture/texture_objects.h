/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_objects.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:16:13 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:15:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_OBJECTS_H
# define TEXTURE_OBJECTS_H

# include "mlx/MLX42/include/MLX42/MLX42.h"
# include "path_tracer/utils/vectors/vectors.h"
# include <stdint.h>

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