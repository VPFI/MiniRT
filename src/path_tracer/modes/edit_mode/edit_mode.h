/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_mode.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:34:24 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/14 19:15:00 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDIT_MODE_H
# define EDIT_MODE_H

# include "src/path_tracer/thread_management/thread_management.h"

void	edit_mode(t_thread *thread, uint32_t x, uint32_t y);

#endif