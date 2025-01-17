/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_color_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:39:44 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/17 19:27:05 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_COLOR_UTILS_H
# define INT_COLOR_UTILS_H

int	get_r(int rgba);
int	get_g(int rgba);
int	get_b(int rgba);
int	get_a(int rgba);
int	get_rgba(int r, int g, int b, int a);

#endif