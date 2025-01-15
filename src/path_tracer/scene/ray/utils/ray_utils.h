/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:29:15 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 16:43:37 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_UTILS_H
# define RAY_UTILS_H

# include "src/path_tracer/scene/ray/ray.h"

t_vect	ray_at(t_ray ray, float pos);
void	check_normal(t_vect *normal, t_vect *ray_dir);

#endif