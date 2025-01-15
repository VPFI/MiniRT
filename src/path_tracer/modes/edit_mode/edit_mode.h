/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_mode.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:34:24 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 20:59:05 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDIT_MODE_H
# define EDIT_MODE_H

# include <stdint.h>
# include "src/path_tracer/scene/scene.h"
# include "src/path_tracer/thread_management/thread_management.h"

void	edit_mode(t_thread *thread, uint32_t x, uint32_t y);
void	edit_mode_hooks(t_scene *scene, mlx_key_data_t key_data);

#endif