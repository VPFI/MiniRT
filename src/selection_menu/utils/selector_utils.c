/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:42:26 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/22 15:23:17 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "path_tracer/utils/color/color_utils.h"
#include "path_tracer/scene/objects/texture/texture_objects.h"
#include <dirent.h>
#include <stdint.h>
#include <unistd.h>

int	get_texture_color(t_texture *tx, uint32_t x, uint32_t y)
{
	uint8_t	*pixel;

	if (x >= tx->texture->width || y >= tx->texture->height)
		return (0);
	pixel = tx->texture->pixels + ((4 * tx->texture->width) * y) + (4 * x);
	return (get_rgba(*pixel, *(pixel + 1), *(pixel + 2), 0xFF));
}

static char	*get_full_path_name(char *name)
{
	char	*path;

	path = ft_strdup(name);
	path = ft_strattach("./assets/maps/", &path);
	return (path);
}

char	*get_map_path(int map_index)
{
	int				i;
	DIR				*d;
	struct dirent	*dir;

	i = 0;
	d = opendir("./assets/maps");
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			if (dir->d_name[0] && dir->d_name[0] != '.'
				&& ft_strnstr(dir->d_name, ".rt", ft_strlen(dir->d_name)))
			{
				if (i == map_index)
				{
					return (closedir(d), get_full_path_name(dir->d_name));
				}
				i++;
			}
			dir = readdir(d);
		}
		closedir(d);
	}
	return (NULL);
}

int	count_maps(void)
{
	int				i;
	DIR				*d;
	struct dirent	*dir;

	i = 0;
	d = opendir("./assets/maps/");
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			if (dir->d_name[0] && dir->d_name[0] != '.'
				&& ft_strnstr(dir->d_name, ".rt", ft_strlen(dir->d_name)))
			{
				i++;
			}
			dir = readdir(d);
		}
		closedir(d);
	}
	return (i);
}
