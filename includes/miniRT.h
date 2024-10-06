/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:15 by vperez-f          #+#    #+#             */
/*   Updated: 2024/10/06 21:49:30 by vpf              ###   ########.fr       */
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

# define DEF_COLOR 0xFF6720FF
# define CYAN_GULF 0xC9DFECC8

# define ESC_KEY 9 //0xff1b
# define PLUS_KEY 0x45
# define MINUS_KEY 0x4E
# define ONE_KEY 0x31
# define TWO_KEY 0x32
# define THREE_KEY 0x33
# define FOUR_KEY 0x34
# define FIVE_KEY 0x35
# define SIX_KEY 0x36
# define SEVEN_KEY 0x37
# define ENTER_KEY 0xff0d
# define LEFT_KEY 0xff51
# define UP_KEY 0xff52
# define RIGHT_KEY 0xff53
# define DOWN_KEY 0xff54
# define DOWN_KEY 0xff54
# define DOWN_KEY 0xff54
# define DOWN_KEY 0xff54
# define W_KEY 0x0077
# define A_KEY 0x0061
# define S_KEY 0x0073
# define D_KEY 0x0064
# define M_KEY 0x6d
# define Q_KEY 0x71
# define E_KEY 0x65
# define T_KEY 0x74
# define G_KEY 0x67
# define I_KEY 0x69
# define O_KEY 0x6f
# define P_KEY 0x70
# define R_KEY 0x72
# define COMMA_KEY 0x2c
# define PERIOD_KEY 0x2e
# define SLASH_KEY 0x2f
# define SPACE_KEY 0x20
# define SHIFT_KEY 0xffe1
# define EIGHT_KEY 0xffb8

# define KEYPRESS_M (1L<<0)
# define KEYRELEASE_M (1L<<1)
# define MOUSEPRESS_M (1L<<2)
# define MOUSERELEASE_M (1L<<3)
# define MOUSEMOVE_M (1L<<6)
# define STRUCTNOTIFY_M (1L<<17)

# define KEYDOWN 2
# define KEYUP 3
# define MOUSEDOWN 4
# define MOUSEUP 5
# define MOUSEMOVE 6
# define EXPOSE 12
# define DESTROY 17

typedef enum e_fig_type
{
	SPHERE = 0,
	PLANE = 1,
	DISK = 2,
}						t_fig_type;

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

typedef struct s_hit_record
{
	
}				t_hit_record;

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
	float			(*hit_func)(t_ray ray, t_figure figure);
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

float		hit_sphere(t_ray ray, t_figure fig);

t_vect		new_vect(float v1, float v2, float v3);
t_coords	new_coords(float v1, float v2, float v3);
t_vect		vect_simple_mult(t_vect vec, float num);
t_vect		vect_simple_div(t_vect vec, float num);
t_vect		vect_simple_subtract(t_vect vec, float num);
t_vect		vect_simple_add(t_vect vec, float num);
t_vect		vect_add(t_vect vec, t_vect vec2);
t_vect		vect_subtract(t_vect vec, t_vect vec2);
t_vect		vect_cross(t_vect vec, t_vect vec2);
float		vect_dot(t_vect vec, t_vect vec2);

#endif