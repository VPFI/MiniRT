/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 13:46:36 by vperez-f          #+#    #+#             */
/*   Updated: 2024/12/24 15:21:23 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_management.h"

void	unset_stop_status(t_scene *scene)
{
	pthread_mutex_lock(&scene->stop_mutex);
	scene->stop = false;
	pthread_mutex_unlock(&scene->stop_mutex);
}

void	set_stop_status(t_scene *scene)
{
	pthread_mutex_lock(&scene->stop_mutex);
	scene->stop = true;
	pthread_mutex_unlock(&scene->stop_mutex);
}

bool	get_stop_status(t_scene *scene)
{
	bool res;

	pthread_mutex_lock(&scene->stop_mutex);
	res = scene->stop;
	pthread_mutex_unlock(&scene->stop_mutex);
	return (res);
}