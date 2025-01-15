/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:25:52 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 21:01:26 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/mlx/MLX42/include/MLX42/MLX42.h"
#include "src/window_management/key_identifiers/key_identifiers.h"

int	is_extra_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_F
		|| key_data.key == MLX_KEY_G
		|| key_data.key == MLX_KEY_V
		|| key_data.key == MLX_KEY_T
		|| key_data.key == MLX_KEY_O
		|| key_data.key == MLX_KEY_Z
		|| key_data.key == MLX_KEY_X
		|| key_data.key == MLX_KEY_C
		|| key_data.key == MLX_KEY_B
		|| key_data.key == MLX_KEY_J
		|| key_data.key == MLX_KEY_K
		|| key_data.key == MLX_KEY_L
		|| key_data.key == MLX_KEY_P
		|| key_data.key == MLX_KEY_TAB
		|| key_data.key == MLX_KEY_EQUAL
		|| key_data.key == MLX_KEY_MINUS
		|| key_data.key == MLX_KEY_ENTER
		|| key_data.key == MLX_KEY_SEMICOLON
		|| key_data.key == MLX_KEY_APOSTROPHE
		|| key_data.key == MLX_KEY_LEFT_BRACKET
		|| key_data.key == MLX_KEY_RIGHT_BRACKET)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
	{
		return (1);
	}
	return (0);
}

int		is_camera_key_down(mlx_key_data_t key_data)
{
	if (is_movement_key_down(key_data)
		|| is_rotation_key_down(key_data)
		|| is_extra_key_down(key_data))
	{
		return (1);
	}
	return (0);
}

int	is_copy_delete_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_N
		|| key_data.key == MLX_KEY_BACKSPACE)
		&& (key_data.action == MLX_PRESS))
	{
		return (1);
	}
	return (0);
}

int	is_num_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_1
		|| key_data.key == MLX_KEY_2
		|| key_data.key == MLX_KEY_3
		|| key_data.key == MLX_KEY_4
		|| key_data.key == MLX_KEY_5
		|| key_data.key == MLX_KEY_6
		|| key_data.key == MLX_KEY_7
		|| key_data.key == MLX_KEY_8)
		&& (key_data.action == MLX_PRESS))
	{
		return (1);
	}
	return (0);
}

int	is_press_and_ctrl(mlx_key_data_t key_data)
{
	if (key_data.action == MLX_PRESS && key_data.modifier == MLX_CONTROL)
		return (1);
	return (0);
}
