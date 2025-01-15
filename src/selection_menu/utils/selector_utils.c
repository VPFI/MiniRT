/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:42:26 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/15 18:46:44 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_texture_color(t_texture *tx, uint32_t x, uint32_t y)
{
	uint8_t *pixel;

	if (x >= tx->texture->width || y >= tx->texture->height)
		return (0);
	pixel = tx->texture->pixels	+ ((4 * tx->texture->width) * y) + (4 * x);
	return (get_rgba(*pixel, *(pixel + 1), *(pixel + 2), 0xFF));
}

char	*get_full_path_name(char *name)
{
	char	*path;

	path = ft_strdup(name);
	path = ft_strattach("./maps/", &path);
	return (path);
}

char	*get_map_path(int map_index)
{
	int				i;
	DIR 			*d;
	struct dirent	*dir;

	i = 0;
	d = opendir("./maps");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_name[0] && dir->d_name[0] != '.'
				&& ft_strnstr(dir->d_name, ".rt", ft_strlen(dir->d_name)))
			{
				if (i == map_index)
				{
					closedir(d);
					return (get_full_path_name(dir->d_name));
				}
				i++;
			}
		}
		closedir(d);
	}
	return (NULL);
}

int	count_maps(void)
{
	int				i;
	DIR 			*d;
	struct dirent	*dir;

	i = 0;
	d = opendir("./maps");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (dir->d_name[0] && dir->d_name[0] != '.'
				&& ft_strnstr(dir->d_name, ".rt", ft_strlen(dir->d_name)))
			{
				i++;
			}
		}
		closedir(d);
	}
	return (i);
}
