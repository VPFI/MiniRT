/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_selector.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:15:00 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:15:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_SELECTOR_H
# define FILE_SELECTOR_H

# include "path_tracer/scene/scene.h"
# include "mlx/MLX42/include/MLX42/MLX42.h"

void	select_scene(t_scene *scene);
void	display_file_menu(t_scene *scene);
void	move_menu(t_scene *scene, keys_t key);

#endif