/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:39:57 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 19:14:59 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_MENU_H
# define DRAW_MENU_H

# include "path_tracer/scene/scene.h"
# include "selection_menu/buttons/buttons.h"

void	draw_no_maps_found(t_scene *scene);
void	draw_buttons(t_button *buttons, t_scene *scene);

#endif