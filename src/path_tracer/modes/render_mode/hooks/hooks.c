/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:49:20 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:49:22 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	render_mode_hooks(t_scene *scene, mlx_key_data_t key_data)
{
	if (key_data.key == MLX_KEY_X && is_press_and_ctrl(key_data))
	{
		set_stop_status(scene);
		wait_for_threads(scene);
		scene->do_backup = true;
		scene->stop = false;
		if (export_to_ppm(scene->image))
			ft_printf(STDERR_FILENO, "Unexpected error exporting image |--> Resuming render\n");
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