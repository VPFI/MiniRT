/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:56:23 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:14:59 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "path_tracer/scene/scene.h"

void	close_mlx(void *sc);
void	set_new_image(t_scene *scene);
void	safe_pixel_put(t_scene *scene, uint32_t x, uint32_t y, t_color color);
void	safe_pixel_put_bres(t_scene *scene, uint32_t x, uint32_t y, int color);

#endif
