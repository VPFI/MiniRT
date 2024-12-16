/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:15 by vperez-f          #+#    #+#             */
/*   Updated: 2024/12/16 02:53:49 by vpf              ###   ########.fr       */
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

# define AIR_REF_INDEX	1.0003

# define ERR_ARGNUM_MSG		"\n\nToo many arguments received, can't specify scene.\n Valid format for opening a specific scene directly:\n\n \"./miniRT ./maps/scene_name.rt\n\nOpening file selector...\n"
# define ERR_HIDFILE_MSG		"Potentially hidden files not supported\n"
# define ERR_INCEXT_MSG		"Invalid file extension || Only .rt files are allowed\n"
# define ERR_INCMAP_MSG		"Incorrect argument scene [%s], opening file selector..."
# define ERR_NOFILE_MSG		"No such file or dir: %s\n\n"
# define ERR_PERM_MSG		"Permission denied\n"
# define ERR_STD_MSG		"Unexpected error\n"
# define ERR_EMPTY_MSG		"%s\n"
# define ERR_MEM_MSG		"Memory allocation failed %s\n\n"

# define STD_SKYSPHERE		"textures/sky_sphere/table_mountain_2_puresky_4k.png"

# define SPHERE				"sp"
# define PLANE				"pl"
# define QUAD				"qu"
# define DISK				"di"
# define BOX				"bx"
# define CYLINDER			"cy"
# define CONE				"co"
# define P_LIGHT			"l"

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
	bool			sampled;
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

typedef enum e_polar
{
	LONGITUDE = 0,
	LATITUDE = 1,
}			t_polar;

typedef struct s_eq_params
{
	float	a;
	float	b;
	float	c;
	float	discr;
	float	root;
}			t_eq_params;

typedef struct s_pattern_vars
{
	int		x_index_square;
	int		y_index_square;
	int		pattern_index;
}			t_pattern_vars;

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

typedef struct s_base_params
{
	float 	point_arc;
	float	base_height;
	float	point_radius;
	t_vect	point_to_base;
}			t_base_params;

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
	float		pattern_dim;
	bool		pattern;
}				t_material;

typedef struct s_point_light
{
	t_vect		location;
	float		radius_shadow;
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
	t_vect		normal;
	t_vect		center;
}				t_quad;

typedef struct s_box
{
	t_vect		u_vect;
	t_vect		v_vect;
	t_vect		dimensions;
	t_vect		center;
	t_object	*faces;
}				t_box;

typedef struct s_disk
{
	t_vect		center;
	t_vect		normal;
	float		radius;
}				t_disk;

typedef struct s_texel
{
	int	x;
	int	y;
}		t_texel;

typedef struct s_texture
{
	char			*path;
	mlx_texture_t	*texture;
	float			texture_dim;
}					t_texture;

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
}					t_figure;

typedef struct s_object
{
	union s_figure 	figure;
	t_material		material;
	t_texture		*texture;
	t_fig_type		type;
	struct s_object	*next;
	bool			selected;
	bool			(*hit_func)(t_ray ray, t_figure figure, t_hit_info *hit_info, float *bounds);
	t_vect			(*get_origin)(t_object *object);
	t_vect			(*get_visual)(t_hit_info *hit_info);
	t_vect			(*get_normal)(t_hit_info *hit_info, t_figure *fig);
	void			(*edit_origin)(t_object *object, t_vect transformation);
	void			(*edit_orientation)(t_object *object, t_camera *camera, t_vect transformation);
	void			(*edit_dimensions)(t_object *object, t_vect transformation);
}					t_object;

typedef struct s_scene
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_vect			*cumulative_image;
	t_thread		threads[THREADS];
	t_thread_backup	threads_backup[THREADS];
	char			*path;
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

void		init_scene(t_scene *scene);

void		print_list(t_object *list);

t_vect		get_random_uvect(uint32_t *state);

void		unset_stop_status(t_scene *scene);
void		set_stop_status(t_scene *scene);
bool		get_stop_status(t_scene *scene);

void		main_loop(void *sc);
void		recalculate_view(t_scene *scene);

t_vect		relative_translate(t_camera *camera, mlx_key_data_t key_data);
t_vect		absolute_translate(mlx_key_data_t key_data);

int			init_object(t_scene *scene, t_figure fig, t_material mat, t_fig_type type);
void		init_faces(t_object *box, t_material mat, t_vect dimensions);
void		recalculate_faces(t_object *box, t_vect dimensions);

void		deselect_objects(t_object *objects, t_object *lights, bool *object_selected);

bool		hit_disk(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds);

void		wait_for_threads(t_scene *scene);
void		wait_for_threads_and_backup(t_scene *scene);

void		safe_pixel_put(t_scene *scene, uint32_t x, uint32_t y, t_vect color);
void		safe_pixel_put_bres(t_scene *scene, uint32_t x, uint32_t y, int color);

void		init_bresenham_line_font(t_scene *scene, t_coords *i_pt, t_coords *f_pt, int color);
void		calculate_bresenham_font(t_scene *scene, t_bresenham *bres);
void		write_str(t_scene *scene, char *msg, int *xys, int color);

void		draw_file_menu(t_scene *scene);
void		free_buttons(t_button *buttons, int n);
void		draw_buttons(t_button *buttons, t_scene *scene);

void		free_texture(t_texture **texture);

void		set_new_image(t_scene *scene);

t_vect		translate_texture_to_normal(uint8_t *pixel);
void		set_bump_map_normal_plane(t_vect *point, t_texture *tx, t_vect *normal);
void		set_bump_map_normal_base(t_vect *point, t_vect *normal, t_texture *tx, float radius, float base_distance);

t_color		get_sky_color(t_thread *thread, t_ray *ray);

t_vect		calc_pixel_color_normal(t_thread *thread, t_scene *scene, t_ray ray);
t_vect		get_obj_color(t_hit_info *hit_info);
void		set_polar_coords(t_vect *point, t_figure *fig, float *polar_coords);
t_ray		dielectric_scatter(uint32_t *state, t_hit_info hit_info, t_ray inc_ray, t_color *emittance, t_thread *thread);

void		*set_rendering(void *args);
void		wait_for_threads(t_scene *scene);


float		get_vector_arc_height(t_vect *point);
t_vect		get_disk_pattern(t_hit_info *hit_info);
void		set_base_params(t_base_params *params, t_vect *point, float radius);
t_vect		get_base_pattern(t_vect *point, t_figure *figure, float pattern_dim, t_color *obj_color);
t_vect		get_plane_pattern_color(t_vect *rotated_point, float pattern_dim, t_vect *material_color);
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


int			parse_map_path(t_scene *scene, int argc, char **argv);
char		*get_map_path(int map_index);

int			throw_err(char *msg, char *specifier, int err_code);
void		exit_err(char *msg, char *specifier, int err_code);

#endif