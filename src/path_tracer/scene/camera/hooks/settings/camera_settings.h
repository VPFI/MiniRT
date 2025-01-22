/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_settings.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:19:40 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 19:28:13 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_SETTINGS_H
# define CAMERA_SETTINGS_H

# include "mlx/MLX42/include/MLX42/MLX42.h"

void	modify_fov(struct s_camera *camera, mlx_key_data_t key_data);
void	modify_defocus(struct s_camera *camera, mlx_key_data_t key_data);
void	modify_focus_dist(struct s_camera *camera, mlx_key_data_t key_data);

#endif