/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:13:13 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 17:13:23 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	cicle_material_type(t_object *target_object)
{
	target_object->material.type = (target_object->material.type + 1) % 5;
	ft_printf(STDOUT_FILENO, "Material is now: %i\n\n", target_object->material.type);
	return ;
}
