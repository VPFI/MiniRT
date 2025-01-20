/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:09:34 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 18:55:30 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODIFIERS_H
# define MODIFIERS_H

# include "mlx/MLX42/include/MLX42/MLX42.h"

struct	s_material;

void	cicle_material_type(struct s_material *material);
void	increment_color(struct s_material *material, mlx_key_data_t key_data);
void	decrement_color(struct s_material *material, mlx_key_data_t key_data);
void	increment_material_component(struct s_material *mat, mlx_key_data_t k);
void	decrement_material_component(struct s_material *mat, mlx_key_data_t k);

#endif