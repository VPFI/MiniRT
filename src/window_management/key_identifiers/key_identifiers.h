/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_identifiers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:46:21 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:15:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_IDENTIFIERS_H
# define KEY_IDENTIFIERS_H

# include "mlx/MLX42/include/MLX42/MLX42.h"

int	is_num_key_down(mlx_key_data_t key_data);
int	is_extra_key_down(mlx_key_data_t key_data);
int	is_press_and_ctrl(mlx_key_data_t key_data);
int	is_camera_key_down(mlx_key_data_t key_data);
int	is_copy_delete_key_down(mlx_key_data_t key_data);

int	is_reset_key_down(mlx_key_data_t key_data);
int	is_settings_key_down(mlx_key_data_t key_data);
int	is_scene_settings_key_down(mlx_key_data_t key_data);

int	is_rgb_key_down(mlx_key_data_t key_data);
int	is_aspect_key_down(mlx_key_data_t key_data);
int	is_movement_key_down(mlx_key_data_t key_data);
int	is_rotation_key_down(mlx_key_data_t key_data);
int	is_material_key_down(mlx_key_data_t key_data);

#endif