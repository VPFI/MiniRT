/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:16:13 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 21:16:01 by vperez-f         ###   ########.fr       */
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

#endif