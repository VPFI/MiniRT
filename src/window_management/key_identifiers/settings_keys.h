/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_keys.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:25:13 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 00:34:46 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_KEYS_H
# define SETTINGS_KEYS_H

# include "libraries/mlx/MLX42/include/MLX42/MLX42.h"

int	is_reset_key_down(mlx_key_data_t key_data);
int	is_settings_key_down(mlx_key_data_t key_data);
int	is_scene_settings_key_down(mlx_key_data_t key_data);

#endif