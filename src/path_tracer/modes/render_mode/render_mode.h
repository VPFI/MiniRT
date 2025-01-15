/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mode.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:34:51 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 01:00:09 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_MODE_H
# define RENDER_MODE_H

# include "src/path_tracer/thread_management/thread_management.h"

void	render_mode(t_thread *thread, uint32_t x, uint32_t y);

#endif