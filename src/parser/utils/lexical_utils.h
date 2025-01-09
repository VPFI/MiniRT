/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:57:09 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 22:37:22 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICAL_UTILS_H
# define LEXICAL_UTILS_H

char	**format_line(char *line);
char	*get_filename(char *path);

int		count_components(char **components);

#endif