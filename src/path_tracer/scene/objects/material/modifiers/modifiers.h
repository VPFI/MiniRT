/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:09:34 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:15:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

# include "mlx/MLX42/include/MLX42/MLX42.h"
# include "path_tracer/scene/objects/material/material.h"

void	cicle_material_type(t_material *material);
void	increment_color(t_material *material, mlx_key_data_t key_data);
void	decrement_color(t_material *material, mlx_key_data_t key_data);
void	increment_material_component(t_material *material, mlx_key_data_t key_data);
void	decrement_material_component(t_material *material, mlx_key_data_t key_data);

#endif