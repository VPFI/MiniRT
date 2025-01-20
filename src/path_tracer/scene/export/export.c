/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 02:30:09 by vpf               #+#    #+#             */
/*   Updated: 2025/01/20 15:40:20 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "printf/ft_printf.h"
#include "error_management/error_management.h"
#include "mlx/MLX42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

static void	write_ppm(mlx_image_t *img, int fd, char *filename)
{
	uint32_t	x;
	uint32_t	y;
	uint8_t		*pixel;

	y = 0;
	pixel = NULL;
	ft_printf(1, "\n\nExporting %i x %i img\n", img->width, img->height);
	ft_printf(fd, "P3\n%i %i\n255\n", img->width, img->height);
	while (y < img->height)
	{
		x = 0;
		pixel = &img->pixels[((y * img->width)) * sizeof(uint32_t)];
		while (x < img->width)
		{
			ft_printf(fd, "%i %i %i", *(pixel), *(pixel + 1), *(pixel + 2));
			x++;
			pixel = pixel + sizeof(uint32_t);
			if (x < img->width)
				ft_printf(fd, "  ");
		}
		ft_printf(fd, "\n");
		y++;
		ft_printf(2, "--| %i%% |--\r", (int)((y / (float)img->height) * 100));
	}
	ft_printf(1, "Img exported succesfully to \"%s\"\n\n", filename);
}

int	export_to_ppm(mlx_image_t *image)
{
	int		fd;
	char	*filename;

	fd = 0;
	filename = ft_itoa((int)(mlx_get_time() * 1000));
	filename = ft_strattach("./assets/img/exported/", &filename);
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
