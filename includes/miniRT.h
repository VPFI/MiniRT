/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:15 by vperez-f          #+#    #+#             */
/*   Updated: 2024/10/07 02:34:27 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <math.h>
# include <limits.h>
# include "../libft/libft.h"
# include "../printf/ft_printf.h"
# include "../mlx/MLX42/include/MLX42/MLX42.h"

# define WINW 1400
# define WINH 800

# define THREADS 4

# define DEF_COLOR 0xFF6720FF
# define CYAN_GULF 0xC9DFECC8

typedef enum e_bounds
{
	MIN = 0,
	MAX = 1,
}			t_bounds;

typedef enum e_eq_indx
{
	a = 0,
	h = 1,
	c = 2,
	discr = 3,
}			t_eq_indx;

typedef enum e_fig_type
{
	SPHERE = 0,
	PLANE = 1,
	DISK = 2,
}			t_fig_type;

typedef struct s_vect
{
	float	x;
	float	y;
	float	z;
}			t_vect;

typedef struct s_coords{
	float   x;
	float   y;
	float   z;
	int 	color;
}       	t_coords;

typedef struct s_ray
{
	t_vect		origin;
	t_vect		dir;
}				t_ray;

typedef struct s_button{
	t_coords	i_pt;
	t_coords	f_pt;
	char		*text;
	int 		color;
}       		t_button;

typedef struct s_camera
{
	t_vect		origin;
	float		viewport_width;
	float		viewport_height;
	float		view_distance;
	t_vect		vp_edge_vert;
	t_vect		vp_edge_horizntl;
	t_vect		pixel_delta_v;
	t_vect		pixel_delta_h;
	t_vect		viewport_origin;
	t_vect		viewport_pixel0;
}				t_camera;

typedef struct s_hit_info
{
	t_vect		point;
	t_vect		normal;
	float		t;
}				t_hit_info;

typedef struct s_sphere
{
	t_vect		center;
	float		radius;
}				t_sphere;

typedef struct s_plane
{
	t_vect		center;
	t_vect		normal;
}				t_plane;

typedef union s_figure
{
	t_sphere	sphere;
	t_plane		plane;
}				t_figure;

typedef struct s_object
{
	union s_figure 	figure;
	t_fig_type		type;
	struct s_object	*next;
	bool			(*hit_func)(t_ray ray, t_figure figure, t_hit_info *hit_info, float *bounds);
}					t_object;

typedef struct s_scene
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_camera		camera;
	t_sphere		sphere_test;
	t_object		*objects;
	uint32_t		height;
	uint32_t		width;
	float			aspect_ratio;
	t_button		buttons[20];
	int				choose_file;
	int				current_file;
}					t_scene;

typedef struct s_bresenham{
	t_coords	i_pt;
	t_coords	f_pt;
	int			d;
	int			d2;
	int			dx;
	int			dy;
	int			i_one;
	int			i_two;
	int			n;
	int			max;
	int			color;
	float		fade_comp[4];
}           	t_bresenham;

int get_rgba(int r, int g, int b, int a);

int get_r(int rgba);
int get_g(int rgba);
int get_b(int rgba);
int get_a(int rgba);

void	safe_pixel_put(t_scene *scene, uint32_t x, uint32_t y, uint32_t color);
void	init_bresenham_line_font(t_scene *scene, t_coords *i_pt, t_coords *f_pt);
void	calculate_bresenham_font(t_scene *scene, t_bresenham *bres);
void	write_str(t_scene *scene, char *msg, int *xy, int size);

void	draw_file_menu(t_scene *scene);
void	draw_buttons(t_button *buttons, t_scene *scene);

void	set_new_image(t_scene *scene);

bool		hit_sphere(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds);

t_coords	new_coords(float v1, float v2, float v3);
t_vect		new_vect(float v1, float v2, float v3);
t_vect		unit_vect(t_vect vect);
t_vect		ray_at(t_ray ray, float pos);
t_vect		vect_simple_mult(t_vect vec, float num);
t_vect		vect_simple_div(t_vect vec, float num);
t_vect		vect_simple_subtract(t_vect vec, float num);
t_vect		vect_simple_add(t_vect vec, float num);
t_vect		vect_add(t_vect vec, t_vect vec2);
t_vect		vect_subtract(t_vect vec, t_vect vec2);
t_vect		vect_cross(t_vect vec, t_vect vec2);
float		vect_dot(t_vect vec, t_vect vec2);

#endif