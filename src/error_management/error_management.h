/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:23:05 by vperez-f          #+#    #+#             */
/*   Updated: 2024/12/24 15:34:58 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MANAGEMENT_H
# define ERROR_MANAGEMENT_H

# include <stdio.h>

# define ERR_ARGNUM_MSG		"\n\nToo many arguments received, can't specify scene.\nValid format for opening a specific scene directly:\n\n \"./miniRT ./maps/scene_name.rt\"\n\nOpening file selector...\n"
# define ERR_HIDFILE_MSG	"Potentially hidden files not supported\n"
# define ERR_INCEXT_MSG		"Invalid file extension || Only .rt files are allowed\n"
# define ERR_INCMAP_MSG		"Incorrect argument scene [%s], opening file selector..."
# define ERR_NOFILE_MSG		"No such file or dir: %s\n\n"
# define ERR_PERM_MSG		"Permission denied\n"
# define ERR_STD_MSG		"Unexpected error\n"
# define ERR_EMPTY_MSG		"%s\n"
# define ERR_MEM_MSG		"Memory allocation failed %s\n\n"
# define ERR_ATTR_MSG		"Parsing: %s\n"
# define ERR_VECT_MSG		"Parsing: %s to vector form\n"
# define ERR_NOID_MSG		"Invalid identifier %s\n"
# define ERR_MAT_MSG		"Wrong material type: %s\n"

#endif