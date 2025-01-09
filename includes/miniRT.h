/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:15 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 22:20:17 by vperez-f         ###   ########.fr       */
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
# include "src/error_management/error_management.h"
# include "../libraries/libft/libft.h"
# include "../libraries/printf/ft_printf.h"
# include "../libraries/mlx/MLX42/include/MLX42/MLX42.h"

# define AIR_REF_INDEX	1.0003

# define STD_SKYSPHERE		"textures/sky_sphere/table_mountain_2_puresky_4k.png"

typedef struct s_vect	t_color;

typedef struct s_object t_object;

typedef union s_figure	t_figure;


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

typedef struct s_2dpoint
{
	float	x;
	float	y;
}			t_2dpoint;

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

typedef struct s_button
{
	t_coords	i_pt;
	t_coords	f_pt;
	char		*text;
	int 		color;
}       		t_button;



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

t_color		get_background_color(t_thread *thread, t_ray *ray);

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

//-----------------------------TO PUT IN LIBFT----------------------------------

int		ft_strcmp(const char *s1, const char *s2);

//------------------------------------------------------------------------------

void		delete_world_object(t_scene *scene);

void		init_copy(t_scene *scene, t_object *selected_obj);

int			init_sphere(t_scene *scene, t_figure fig, t_material mat, t_texture *tx);
int			init_plane(t_scene *scene, t_figure fig, t_material mat, t_texture *tx);
int			init_quad(t_scene *scene, t_figure fig, t_material mat, t_texture *tx);
int			init_disk(t_scene *scene, t_figure fig, t_material mat, t_texture *tx);
int			init_box(t_scene *scene, t_figure fig, t_material mat, t_texture *tx);
int			init_cylinder(t_scene *scene, t_figure fig, t_material mat, t_texture *tx);
int			init_cone(t_scene *scene, t_figure fig, t_material mat, t_texture *tx);
int			init_p_light(t_scene *scene, t_figure fig, t_material mat);

#endif