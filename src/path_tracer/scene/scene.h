/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:02:05 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 00:54:43 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <stdint.h>
# include <stdbool.h>
# include "libraries/mlx/MLX42/include/MLX42/MLX42.h"
# include "src/path_tracer/scene/camera/camera.h"
# include "src/path_tracer/utils/vectors/vectors.h"
# include "src/path_tracer/thread_management/thread_management.h"

# define WINW 		1820
# define WINH 		980

# define THREADS 	8

# define MAX_DEPTH  8
# define SPP 		1

# define TEST 		1

# define DEFOCUS	0.0
# define FOCUS_DIST	5
# define FOV		40

# define AMB		1

# define AMB_LIGHT	0.7
# define AMB_COLOR	0xF1F1F1FF
# define BG_COLOR	0x101010FF

# define DEF_COLOR	0xFF6720FF
# define BRONZE		0xCD7F32FF
# define CYAN_GULF	0xC9DFECFF
# define TURQUOISE	0x40E0D0FF
# define RED		0xFF4364FF
# define GREEN		0x43FF64FF 
# define BLUE		0x1C1CFFFF 
# define YELLOW		0xEEEE9BFF
# define SILVER		0xC0C0C0FF
# define BLACK		0x505050FF
# define TRUE_BLACK	0x000000FF
# define WHITE		0xF1F1F1FF

typedef struct s_scene
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_vect			*cumulative_image;
	t_thread		threads[THREADS];
	t_thread_backup	threads_backup[THREADS];
	char			*path;
	int				samples;
	int				max_depth;
	uint32_t		state;
	bool			stop;
	bool			edit_mode;
	bool			do_backup;
	bool			object_selected;
	pthread_mutex_t	stop_mutex;
	float			time;
	t_camera		camera;
	t_camera		back_up_camera;
	int				amb_color;
	float			amb_light;
	t_object		*sky_sphere;
	t_object		*objects;
	t_object		*lights;
	uint32_t		height;
	uint32_t		width;
	float			aspect_ratio;
	t_button		*buttons;
	t_texture		*menu_tx;
	int				map_count;
	int				choose_file;
	int				current_file;
}					t_scene;

void	init_scene(t_scene *scene);
void	init_sky_sphere(t_scene *scene, char *path);
void	change_scene_settings(t_scene *scene, mlx_key_data_t key_data);

#endif