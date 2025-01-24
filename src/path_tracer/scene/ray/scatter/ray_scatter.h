/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_scatter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:29:18 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/24 00:52:14 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_SCATTER_H
# define RAY_SCATTER_H

struct	s_thread;
struct	s_hit_info;
struct	s_scatter_rays;

bool	scatter_ray(struct s_thread *thread, struct s_hit_info hit_info,
			struct s_scatter_rays *rays, t_color *emittance);

#endif