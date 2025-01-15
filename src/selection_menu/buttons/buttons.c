/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:30:21 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 18:39:15 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/selection_menu/buttons/buttons.h"
#include <stdlib.h>

void	free_buttons(t_button *buttons, int n)
{
	int	i;

	i = 0;
	if (!buttons)
		return ;
	while (i < n)
	{
		if (buttons[i].text)
			free(buttons[i].text);
		i++;
	}
	free(buttons);
}
