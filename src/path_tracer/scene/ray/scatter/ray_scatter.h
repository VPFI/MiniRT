/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_scatter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:29:18 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/16 20:44:46 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_SCATTER_H
# define RAY_SCATTER_H

struct s_thread;
struct s_hit_info;

bool	scatter_ray(struct s_thread *thread, struct s_hit_info hit_info, t_ray *bounce_ray, t_ray ray, t_color *emittance);

#endif