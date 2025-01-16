/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:53:41 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:15:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_MANAGEMENT_H
# define WINDOW_MANAGEMENT_H

# include "mlx/MLX42/include/MLX42/MLX42.h"
# include <stdint.h>

void	key_down(mlx_key_data_t key_data, void *sc);
void	resize_handle(int32_t width, int32_t height, void *sc);
void	mouse_handle(mouse_key_t button, action_t action, modifier_key_t mods, void *sc);

#endif