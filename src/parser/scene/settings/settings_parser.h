/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:19:44 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/10 17:48:35 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_PARSER_H
# define SETTINGS_PARSER_H

# include "src/path_tracer/scene/scene.h"

void	load_settings(t_scene *scene, char **components, int amount);

#endif