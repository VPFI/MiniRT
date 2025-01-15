/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_keys.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:25:40 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 00:30:57 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATION_KEYS_H
# define TRANSFORMATION_KEYS_H

# include "libraries/mlx/MLX42/include/MLX42/MLX42.h"

int	is_rgb_key_down(mlx_key_data_t key_data);
int	is_aspect_key_down(mlx_key_data_t key_data);
int	is_movement_key_down(mlx_key_data_t key_data);
int	is_rotation_key_down(mlx_key_data_t key_data);
int	is_material_key_down(mlx_key_data_t key_data);

#endif