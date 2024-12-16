/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:27:17 by vpf               #+#    #+#             */
/*   Updated: 2024/12/16 01:41:21 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	exit_err(char *msg, char *specifier, int err_code)
{
	if (!specifier)
		fprintf(stderr, "MiniRT | Critical error: %s\n", msg);
	else
	{
		fprintf(stderr, "MiniRT | Critical error: ");
		fprintf(stderr, msg, specifier);
	}
	exit(err_code);
}

int	throw_err(char *msg, char *specifier, int err_code)
{
	if (!specifier)
		fprintf(stderr, "MiniRT | Error: %s\n", msg);
	else
	{
		fprintf(stderr, "MiniRT | Error: ");
		fprintf(stderr, msg, specifier);
	}
	return (err_code);
}

char	*get_filename(char *path)
{
	int	aux;
	int	len;

	if (!path)
	{
		return (NULL);
	}
	len = ft_strlen(path);
	aux = len;
	while (aux > 0 && path[aux - 1] != '/')
	{
		aux--;
	}
	return (ft_substr(path, aux, len));
}

int	check_extension(char *name)
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

int	check_file_format(char *path)
{
	char	*filename;

	filename = get_filename(path);
	if (!filename)
		return (exit_err(ERR_STD_MSG, NULL, 1), 1);
	if (filename[0] == '.')
		return (throw_err(ERR_HIDFILE_MSG, NULL, 2));
	if (check_extension(filename))
		return (throw_err(ERR_INCEXT_MSG, NULL, 2));
	return (0);
}

int	check_file_validity(char *path)
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
	if (check_file_format(argv[1]))
		return (throw_err(ERR_INCMAP_MSG, argv[1], 12));
	if (check_file_validity(argv[1]))
		return (throw_err(ERR_NOFILE_MSG, argv[1], 12));
	scene->path = ft_strdup(argv[1]);
	return (0);
}
