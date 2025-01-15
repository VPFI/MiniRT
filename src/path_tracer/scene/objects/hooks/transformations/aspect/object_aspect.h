/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_aspect.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:42:50 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 17:52:41 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_ASPECT_H
# define OBJECT_ASPECT_H

# include "src/path_tracer/scene/objects/objects.h"
# include "libraries/mlx/MLX42/include/MLX42/MLX42.h"

int	check_object_aspect(t_object *target_object, mlx_key_data_t key_data);

#endif