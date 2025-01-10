/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_parser.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:19:52 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/10 17:46:27 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIENT_PARSER_H
# define AMBIENT_PARSER_H

# include "src/path_tracer/scene/scene.h"

void	load_ambient(t_scene *scene, char **components, int amount);

#endif