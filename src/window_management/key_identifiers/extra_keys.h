/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_keys.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:26:01 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 00:35:11 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRA_KEYS_H
# define EXTRA_KEYS_H

# include "libraries/mlx/MLX42/include/MLX42/MLX42.h"

int	is_num_key_down(mlx_key_data_t key_data);
int	is_extra_key_down(mlx_key_data_t key_data);
int	is_press_and_ctrl(mlx_key_data_t key_data);
int	is_camera_key_down(mlx_key_data_t key_data);
int	is_copy_delete_key_down(mlx_key_data_t key_data);

#endif