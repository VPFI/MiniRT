/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:30:27 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 18:51:18 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTONS_H
# define BUTTONS_H

typedef struct s_button
{
	t_coords	i_pt;
	t_coords	f_pt;
	char		*text;
	int 		color;
}				t_button;

void	free_buttons(t_button *buttons, int n);

#endif