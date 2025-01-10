/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:04:24 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/10 18:51:31 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_PARSER_H
# define TEXTURE_PARSER_H

# include "src/path_tracer/scene/objects/texture/texture.h"

void	parse_texture(char **settings, t_texture **tx);

#endif