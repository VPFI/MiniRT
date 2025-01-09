/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:12:10 by vperez-f          #+#    #+#             */
/*   Updated: 2024/12/24 17:12:16 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
