/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:48:15 by vperez-f          #+#    #+#             */
/*   Updated: 2024/09/30 20:12:22 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include "../libft/libft.h"
# include "../printf/ft_printf.h"
# include "../mlx/MLX42/include/MLX42/MLX42.h"

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

typedef struct s_vect
{
	float	x;
	float	y;
	float	z;
}			t_vect;

typedef struct s_scene
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	uint32_t		height;
	uint32_t		width;
}			t_scene;

typedef struct s_camera
{
	
}			t_camera;

typedef struct s_sphere
{
	t_vect		center;
	double		radius;
	void		*hit_func;
}				t_sphere;

typedef union s_figure
{
	t_sphere	*sphere;
}				t_figure;

typedef struct s_object
{
	union s_figure 	object;
	struct s_object	*next;
}					t_object;


int get_rgba(int r, int g, int b, int a);

int get_r(int rgba);
int get_g(int rgba);
int get_b(int rgba);
int get_a(int rgba);

#endif