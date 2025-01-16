/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:42:34 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 15:39:11 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECTOR_UTILS_H
# define SELECTOR_UTILS_H

# include "src/path_tracer/scene/objects/texture/texture_objects.h"
# include <stdint.h>

typedef struct s_coords
{
	float	x;
	float	y;
	float	z;
	int		color;
}			t_coords;

int		count_maps(void);
char	*get_map_path(int map_index);
int		get_texture_color(t_texture *tx, uint32_t x, uint32_t y);

#endif