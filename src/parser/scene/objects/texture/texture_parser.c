/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:12:10 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/10 18:50:35 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/path_tracer/scene/objects/texture/texture.h"
#include "src/error_management/error_management.h"
#include "src/parser/utils/numerical_utils.h"
#include "src/parser/utils/lexical_utils.h"
#include <limits.h>

void	parse_texture(char **settings, t_texture **tx)
{
	int	amount;

	amount = count_components(settings);
	if (amount != 3)
		exit_err(ERR_EMPTY_MSG, "Missing texture components\n", 2);
	*tx = get_texture(settings[1], ft_atof(settings[2], 0, (float)INT_MAX));
	if (!(*tx))
	{
		exit_err(ERR_ATTR_MSG, "texture\n", 2);
	}
}
