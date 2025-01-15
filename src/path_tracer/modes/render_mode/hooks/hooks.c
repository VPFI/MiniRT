/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:49:20 by vpf               #+#    #+#             */
/*   Updated: 2025/01/15 01:19:02 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/libft/libft.h"
#include "src/path_tracer/path_tracer.h"
#include "src/path_tracer/scene/scene.h"
#include "src/path_tracer/scene/export/export.h"
#include "src/path_tracer/thread_management/mutex_utils.h"
#include "src/window_management/key_identifiers/extra_keys.h"
#include "src/path_tracer/thread_management/thread_management.h"
#include "src/error_management/error_management.h"

void	render_mode_hooks(t_scene *scene, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_X && is_press_and_ctrl(key_data))
	{
		set_stop_status(scene);
		wait_for_threads(scene);
		scene->do_backup = true;
		scene->stop = false;
		if (export_to_ppm(scene->image))
			ft_printf(stderr, "Unexpected error exporting image |--> Resuming render\n");
		main_loop(scene);
	}
	else if (key_data.key == MLX_KEY_E && is_press_and_ctrl(key_data))
	{
		set_stop_status(scene);
		wait_for_threads(scene);
		scene->stop = false;
		scene->edit_mode = true;
		ft_memset(scene->cumulative_image, 0, sizeof(t_vect) * scene->height * scene->width);
		main_loop(scene);
	}
}
