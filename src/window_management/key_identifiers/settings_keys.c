/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:24:55 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 15:18:28 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/MLX42/include/MLX42/MLX42.h"

int	is_reset_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_O || key_data.key == MLX_KEY_T)
		&& (key_data.action == MLX_PRESS))
	{
		return (1);
	}
	return (0);
}

int	is_settings_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_F
			|| key_data.key == MLX_KEY_G
			|| key_data.key == MLX_KEY_V)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
	{
		return (1);
	}
	return (0);
}

int	is_scene_settings_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_COMMA
			|| key_data.key == MLX_KEY_PERIOD
			|| key_data.key == MLX_KEY_RIGHT_SHIFT)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
	{
		return (1);
	}
	return (0);
}
