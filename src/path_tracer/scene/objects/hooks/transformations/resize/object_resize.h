/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_resize.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:43:24 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 17:52:36 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_RESIZE_H
# define OBJECT_RESIZE_H

# include "src/path_tracer/scene/objects/objects.h"
# include "libraries/mlx/MLX42/include/MLX42/MLX42.h"

int	check_object_resize(t_object *target_object, mlx_key_data_t key_data);

#endif