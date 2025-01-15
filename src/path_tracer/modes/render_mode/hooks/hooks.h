/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:21:22 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 01:13:39 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "src/path_tracer/scene/scene.h"

void    render_mode_hooks(t_scene *scene, mlx_key_data_t key_data);

#endif