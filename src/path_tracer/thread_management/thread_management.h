/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:08:14 by vperez-f          #+#    #+#             */
/*   Updated: 2024/12/24 15:21:19 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_MANAGEMENT_H
# define THREAD_MANAGEMENT_H

# include <stdint.h>
# include <stdbool.h>
# include <pthread.h>

typedef struct s_thread
{
	int				id;
	int				pix_rendered;
	int				iterations;
	pthread_t		self;
	float			time_hit;
	struct s_scene	*scene;
	uint32_t		*state;
	uint32_t		current_x;
	uint32_t		x_start;
	uint32_t		x_end;
	uint32_t		x_increment;
	uint32_t		current_y;
	uint32_t		y_start;
	uint32_t		y_end;
	bool			sampled;
}					t_thread;

typedef struct s_thread_backup
{
	int				iterations;
	uint32_t		current_y;
}					t_thread_backup;

#endif