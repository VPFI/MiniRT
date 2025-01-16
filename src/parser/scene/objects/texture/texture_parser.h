/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:04:24 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 15:39:11 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_PARSER_H
# define TEXTURE_PARSER_H

# include "src/path_tracer/scene/objects/texture/texture_objects.h"

void	parse_texture(char **settings, t_texture **tx);

#endif