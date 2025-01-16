/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:42:36 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 16:20:22 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "src/path_tracer/utils/vectors/vectors.h"
# include "src/path_tracer/scene/objects/objects.h"
# include "src/path_tracer/scene/objects/figures/figures.h"
# include "src/path_tracer/scene/objects/texture/texture_objects.h"

t_vect	get_cylinder_texture(t_hit_info *ht, t_texture *tx, t_figure *fig, int is_base);

#endif