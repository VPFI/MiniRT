/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:27:17 by vpf               #+#    #+#             */
/*   Updated: 2024/12/24 16:37:34 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

static int	check_extension(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len >= 3)
	{
		if (name[len - 1] == 't')
			if (name[len - 2] == 'r')
				if (name[len - 3] == '.')
					return (0);
	}
	return (1);
}

static int	check_file_format(char *path)
{
	char	*filename;

	filename = get_filename(path);
	if (!filename)
		return (exit_err(ERR_STD_MSG, NULL, 1), 1);
	if (filename[0] == '.')
		return (free(filename), throw_err(ERR_HIDFILE_MSG, NULL, 2));
	if (check_extension(filename))
		return (free(filename), throw_err(ERR_INCEXT_MSG, NULL, 2));
	free(filename);
	return (0);
}

static int	check_file_validity(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		if (access(path, F_OK))
			return (12);
		else if (access(path, R_OK))
			return (throw_err(ERR_PERM_MSG, NULL, 12), 12);
		else
			return (throw_err(ERR_STD_MSG, NULL, 12), 12);
	}
	close(fd);
	return (0);
}

int	parse_map_path(t_scene *scene, int argc, char **argv)
{
	if (argc == 1)
		return (10);
	else if (argc > 2)
		return (throw_err(ERR_ARGNUM_MSG, NULL, 11));
	if (!(!ft_strcmp(".std", argv[1]) || !ft_strcmp(".standard", argv[1])))
	{
		if (check_file_format(argv[1]))
			return (throw_err(ERR_INCMAP_MSG, argv[1], 12));
		if (check_file_validity(argv[1]))
			return (throw_err(ERR_NOFILE_MSG, argv[1], 12));
	}
	else
	{
		scene->choose_file = 1;
		scene->path = ft_strdup(argv[1]);
	}
	return (0);
}
