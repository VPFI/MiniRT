/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:15 by vperez-f          #+#    #+#             */
/*   Updated: 2024/11/21 02:04:00 by vpf              ###   ########.fr       */
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
# include <pthread.h>
# include <math.h>
# include <limits.h>
# include "../libft/libft.h"
# include "../printf/ft_printf.h"
# include "../mlx/MLX42/include/MLX42/MLX42.h"

# define WINW 		1400
# define WINH 		800

# define THREADS 	8

# define MAX_DEPTH  8
# define SPP 		1

# define DEFOCUS	0.0
# define FOCUS_DIST	5 // 5.15
# define FOV		30

# define AMB		1

# define AMB_LIGHT	0.75
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

# define AIR_REF_INDEX	1.0003

# define ERR_NOFILE_MSG		"miniRT: no such file or dir: %s\n"
# define ERR_PERM_MSG		"miniRT: permission denied: %s\n"
# define ERR_STD_MSG		"miniRT: Unexpected error\n"

typedef struct s_vect	t_color;

typedef struct s_object t_object;

typedef union s_figure	t_figure;

typedef struct s_thread
{
	int				id;
	int				pix_rendered;
	int				iterations;
	pthread_t		self;
	float			time_hit;
	struct s_scene	*scene;
	uint32_t		*state;
	uint32_t		current_x;
	uint32_t		x_start;
	uint32_t		x_end;
	uint32_t		x_increment;
	uint32_t		current_y;
	uint32_t		y_start;
	uint32_t		y_end;
}					t_thread;

typedef struct s_thread_backup
{
	int				iterations;
	uint32_t		current_y;
}					t_thread_backup;

typedef enum e_mat_type
{
	LAMBERTIAN = 0,
	METAL = 1,
	GLOSSY = 2,
	DIELECTRIC = 3,
	EMISSIVE = 4,
}			t_mat_type;

typedef enum e_bounds
{
	MIN = 0,
	MAX = 1,
}			t_bounds;

typedef struct s_eq_params
{
	float	a;
	float	b;
	float	c;
	float	discr;
	float	root;
}			t_eq_params;

typedef enum e_fig_type
{
	SPHERE = 0,
	PLANE = 1,
	QUAD = 2,
	BOX = 3,
	DISK = 4,
	CYLINDER = 5,
	CONE = 6,
	LIGHT = 7,
}			t_fig_type;

typedef struct s_2dpoint
{
	float	x;
	float	y;
}			t_2dpoint;

typedef struct s_vect
{
	float	x;
	float	y;
	float	z;
}			t_vect;

typedef struct s_coords
{
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

typedef struct s_button
{
	t_coords	i_pt;
	t_coords	f_pt;
	char		*text;
	int 		color;
}       		t_button;

typedef struct s_reference_system
{
	t_ray	ray;
	t_vect	center;
}			t_reference_system;

typedef struct s_camera
{
	t_vect		origin;
	t_vect		orientation;
	float		viewport_width;
	float		viewport_height;
	float		fov;
	float		focus_dist;
	float		defocus_angle;
	float		defocus_radius;
	t_vect		w;
	t_vect		u;
	t_vect		v;
	t_vect		defocus_disk_u;
	t_vect		defocus_disk_v;
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
	t_object	*object;
	float		t;
}				t_hit_info;

typedef struct s_material
{
	t_color		color;
	t_color		albedo;
	t_mat_type	type;
	float		specular;
	float		metal_roughness;
	float		refraction_index;
	float		emission_intensity;
	bool		pattern;
}				t_material;

typedef struct s_point_light
{
	t_vect		location;
}				t_point_light;

typedef struct s_cylinder
{
	t_vect		center;
	t_vect		normal;
	float		radius;
	float		height;
}				t_cylinder;

typedef struct s_cone
{
	t_vect		center;
	t_vect		normal;
	float		radius;
	float		height;
}				t_cone;

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

typedef struct s_quad
{
	t_vect		u_vect;
	t_vect		v_vect;
	t_vect		origin;
}				t_quad;

typedef struct s_box
{
	t_vect		u_vect;
	t_vect		v_vect;
	t_vect		dimensions;
	t_vect		origin;
	t_object	*faces;
}				t_box;

typedef struct s_disk
{
	t_vect		center;
	t_vect		normal;
	float		radius;
}				t_disk;

typedef union s_figure
{
	t_sphere		sphere;
	t_plane			plane;
	t_quad			quad;
	t_box			box;
	t_disk			disk;
	t_cylinder		cylinder;
	t_cone			cone;
	t_point_light	p_light;
}				t_figure;

typedef struct s_object
{
	union s_figure 	figure;
	t_material		material;
	t_fig_type		type;
	struct s_object	*next;
	bool			selected;
	bool			(*hit_func)(t_ray ray, t_figure figure, t_hit_info *hit_info, float *bounds);
	t_vect			(*get_origin)(t_object *object);
	t_vect			(*get_visual)(t_hit_info *hit_info);
	void			(*edit_origin)(t_object *object, t_vect transformation);
	void			(*edit_orientation)(t_object *object, t_vect transformation);
	void			(*edit_dimensions)(t_object *object, t_vect transformation);
}					t_object;

typedef struct s_scene
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_vect			*cumulative_image;
	t_thread		threads[THREADS];
	t_thread_backup	threads_backup[THREADS];
	uint32_t		state;
	bool			stop;
	bool			edit_mode;
	bool			do_backup;
	bool			object_selected;
	pthread_mutex_t	stop_mutex;
	float			time;
	t_camera		camera;
	t_camera		back_up_camera;
	float			amb_light;
	t_sphere		sphere_test;
	t_object		*objects;
	t_object		*lights;
	uint32_t		height;
	uint32_t		width;
	float			aspect_ratio;
	t_button		buttons[20];
	int				choose_file;
	int				current_file;
}					t_scene;

typedef struct s_bresenham
{
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

int 		get_rgba(int r, int g, int b, int a);

int 		get_r(int rgba);
int 		get_g(int rgba);
int 		get_b(int rgba);
int 		get_a(int rgba);

void		print_list(t_object *list);

void		unset_stop_status(t_scene *scene);
void		set_stop_status(t_scene *scene);
bool		get_stop_status(t_scene *scene);

void		main_loop(void *sc);
void		recalculate_view(t_scene *scene);

int			init_object(t_scene *scene, t_figure fig, t_material mat, t_fig_type type);
void		init_faces(t_object *box, t_material mat, t_vect dimensions);
void		recalculate_faces(t_object *box, t_vect dimensions);

void		deselect_objects(t_object *objects, t_object *lights, bool *object_selected);

bool		hit_disk(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds);

void		wait_for_threads(t_scene *scene);
void		wait_for_threads_and_backup(t_scene *scene);

void		safe_pixel_put(t_scene *scene, uint32_t x, uint32_t y, t_vect color);
void		safe_pixel_put_bres(t_scene *scene, uint32_t x, uint32_t y, int color);

void		init_bresenham_line_font(t_scene *scene, t_coords *i_pt, t_coords *f_pt);
void		calculate_bresenham_font(t_scene *scene, t_bresenham *bres);
void		write_str(t_scene *scene, char *msg, int *xy, int size);

void		draw_file_menu(t_scene *scene);
void		draw_buttons(t_button *buttons, t_scene *scene);

void		set_new_image(t_scene *scene);

t_vect		calc_pixel_color_normal(t_scene *scene, t_ray ray);
t_vect		get_obj_color(t_hit_info *hit_info);

void		*set_rendering(void *args);
void		wait_for_threads(t_scene *scene);

bool		hit_sphere(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds);

t_color		hexa_to_vect(int color);

t_ray		new_ray(t_vect dir, t_vect origin);

t_coords	new_coords(float v1, float v2, float v3);

t_vect		new_color(float v1, float v2, float v3);

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
t_vect		vect_div(t_vect vec, t_vect vec2);
t_vect		vect_mult(t_vect vec, t_vect vec2);
float		vect_dot(t_vect vec, t_vect vec2);
float		vect_length(t_vect vec);

bool		zero_vect(t_vect vect);

t_vect		clamp_vect( t_vect vect, float min, float max);

void		free_objects(t_object **objects);
void		free_primitive(t_object **object);

#endif