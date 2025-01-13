/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:38:41 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/11 23:14:39 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_UTILS_H
# define MUTEX_UTILS_H

# include "src/path_tracer/scene/scene.h"

bool	get_stop_status(t_scene *scene);
void	set_stop_status(t_scene *scene);
void	unset_stop_status(t_scene *scene);

#endif