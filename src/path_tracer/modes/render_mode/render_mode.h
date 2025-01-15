/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mode.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:34:51 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 20:51:41 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_MODE_H
# define RENDER_MODE_H

# include "src/path_tracer/scene/scene.h"
# include "src/path_tracer/thread_management/thread_management.h"
# include "libraries/mlx/MLX42/include/MLX42/MLX42.h"

void	render_mode(t_thread *thread, uint32_t x, uint32_t y);
void	render_mode_hooks(t_scene *scene, mlx_key_data_t key_data);

#endif