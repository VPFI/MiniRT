/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:13:13 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 21:40:40 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "printf/ft_printf.h"
#include "path_tracer/scene/objects/material/material.h"

void	cicle_material_type(t_material *material)
{
	material->type = (material->type + 1) % 5;
	ft_printf(STDOUT_FILENO, "Material is now: %i\n\n", material->type);
	return ;
}
