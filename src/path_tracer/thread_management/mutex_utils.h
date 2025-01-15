/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:34:08 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 20:37:07 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_UTILS_H
# define MUTEX_UTILS_H

# include "src/path_tracer/scene/scene.h"

bool	get_stop_status(t_scene *scene);
void	set_stop_status(t_scene *scene);
void	unset_stop_status(t_scene *scene);

#endif