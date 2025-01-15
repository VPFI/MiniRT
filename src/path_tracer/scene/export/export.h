/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:20:59 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 01:17:36 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "libraries/mlx/MLX42/include/MLX42/MLX42.h"

int	export_to_ppm(mlx_image_t *image);

#endif