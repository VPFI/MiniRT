/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_parser.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:04:15 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 15:10:04 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_PARSER_H
# define MATERIAL_PARSER_H

# include "path_tracer/scene/objects/material/material.h"

void	parse_material(char **settings, t_material *mat);
void	parse_pattern(char **settings, t_material *mat);

#endif