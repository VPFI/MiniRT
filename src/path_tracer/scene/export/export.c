/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:30:09 by vpf               #+#    #+#             */
/*   Updated: 2025/01/15 16:42:01 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/libft/libft.h"
#include "libraries/printf/ft_printf.h"
#include "src/error_management/error_management.h"
#include "libraries/mlx/MLX42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

static void	write_ppm(mlx_image_t *image, int fd, char *filename)
{
	uint32_t	x;
	uint32_t	y;
	uint8_t		*pixel;

	y = 0;
	pixel = NULL;
	ft_printf(STDOUT_FILENO, "\n\nExporting %i x %i image\n", image->width, image->height);
	ft_printf(fd, "P3\n");
	ft_printf(fd, "%i %i\n", image->width, image->height);
	ft_printf(fd, "255\n");
	while (y < image->height)
	{
		x = 0;
		pixel = &image->pixels[((y * image->width)) * sizeof(uint32_t)];
		while (x < image->width)
		{
			ft_printf(fd, "%i %i %i", *(pixel), *(pixel + 1), *(pixel + 2));
			x++;
			pixel = pixel + sizeof(uint32_t);
			if (x < image->width)
				ft_printf(fd, "  ");
		}
		ft_printf(fd, "\n");
		y++;
		ft_printf(STDERR_FILENO, "--| %i%% |--\r", (int)((y / (float)image->height) * 100));
	}
	ft_printf(STDOUT_FILENO, "Image exported succesfully to \"%s\"\n\n", filename);
}

int	export_to_ppm(mlx_image_t *image)
{
	int		fd;
	char	*filename;

	fd = 0;
	filename = ft_itoa((int)(mlx_get_time() * 1000));
	filename = ft_strattach("img/exported/", &filename);
	filename = ft_strappend(&filename, ".ppm");
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		if (access(filename, F_OK))
			throw_err(ERR_NOFILE_MSG, filename, 1);
		else if (access(filename, R_OK))
			throw_err(ERR_PERM_MSG, NULL, 1);
		else
			throw_err(ERR_STD_MSG, NULL, 1);
		free(filename);
		return (1);
	}
	write_ppm(image, fd, filename);
	close(fd);
	free(filename);
	return (0);
}
