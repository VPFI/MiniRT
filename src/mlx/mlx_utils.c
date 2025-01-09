/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:45:50 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 21:56:09 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "src/path_tracer/scene/scene.h"
#include "mlx_utils.h"

void	set_new_image(t_scene *scene)
{
	if (scene->image)
		mlx_delete_image(scene->mlx, scene->image);
	scene->image = mlx_new_image(scene->mlx, scene->width, scene->height);
}

void	safe_pixel_put_bres(t_scene *scene, uint32_t x, uint32_t y, int color)
{
	if ((x >= scene->width) || y >= scene->height)
		return ;
	mlx_put_pixel(scene->image, x, y, color);
}

void	safe_pixel_put(t_scene *scene, uint32_t x, uint32_t y, t_color color)
{
	if ((x >= scene->width) || y >= scene->height)
		return ;
	mlx_put_pixel(scene->image, x, y, get_rgba((int)(color.x * 255.9), (int)(color.y * 255.9), (int)(color.z * 255.9), 255));
}
