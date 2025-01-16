/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:34:08 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 20:43:23 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_UTILS_H
# define MUTEX_UTILS_H

struct s_scene;

bool	get_stop_status(struct s_scene *scene);
void	set_stop_status(struct s_scene *scene);
void	unset_stop_status(struct s_scene *scene);

#endif