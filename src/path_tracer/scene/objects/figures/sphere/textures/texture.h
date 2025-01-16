/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 18:42:36 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 17:43:28 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "src/path_tracer/utils/vectors/vectors.h"
# include "src/path_tracer/scene/objects/objects.h"
# include "src/path_tracer/scene/objects/texture/texture_objects.h"

t_vect	get_sphere_texture(t_hit_info *hit_info, t_texture *texture);

#endif