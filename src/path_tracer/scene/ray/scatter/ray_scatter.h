/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_scatter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:29:18 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/20 17:12:44 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_SCATTER_H
# define RAY_SCATTER_H

struct	s_ray;
struct	s_thread;
struct	s_hit_info;

bool	scatter_ray(struct s_thread *thread, struct s_hit_info hit_info,
			struct s_ray *bounce_ray, struct s_ray ray, t_color *emittance);

#endif