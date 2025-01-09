/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_keys.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:25:27 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 17:27:26 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_movement_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_UP || key_data.key == MLX_KEY_DOWN
		|| key_data.key == MLX_KEY_LEFT || key_data.key == MLX_KEY_RIGHT
		||key_data.key == MLX_KEY_LEFT_SHIFT || key_data.key == MLX_KEY_SPACE)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
	{
		return (1);
	}
	return (0);
}

int	is_rotation_key_down(mlx_key_data_t key_data)
{
	if ((key_data.key == MLX_KEY_W || key_data.key == MLX_KEY_S
		|| key_data.key == MLX_KEY_A || key_data.key == MLX_KEY_D
		|| key_data.key == MLX_KEY_Q || key_data.key == MLX_KEY_E)
		&& (key_data.action == MLX_PRESS || key_data.action == MLX_REPEAT))
	{
		return (1);
	}
	return (0);
}

int	is_material_key_down(mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_J
		|| key_data.key == MLX_KEY_K
		|| key_data.key == MLX_KEY_L
		|| key_data.key == MLX_KEY_SEMICOLON
		|| key_data.key == MLX_KEY_APOSTROPHE)
	{
		return (1);
	}
	return (0);
}

int	is_rgb_key_down(mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_Z
		|| key_data.key == MLX_KEY_X
		|| key_data.key == MLX_KEY_C)
	{
		return (1);
	}
	return (0);
}

int	is_aspect_key_down(mlx_key_data_t key_data)
{
	if (is_rgb_key_down(key_data)
		|| is_material_key_down(key_data)
		|| key_data.key == MLX_KEY_TAB)
	{
		return (1);
	}
	return (0);
}
