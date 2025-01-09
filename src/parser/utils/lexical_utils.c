/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:36:00 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 17:02:48 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_components(char **components)
{
	int	i;

	if (!components)
		return (0);
	i = 0;
	while (components[i])
	{
		i++;
	}
	return (i);
}

char	**format_line(char *line)
{
	char	**res;
	char	*temp_line;

	temp_line = ft_strtrim(line, "\n");
	res = ft_split(temp_line, ' ');
	free(temp_line);
	if (res && res[0] && !ft_strncmp(res[0], "#", 1))
	{
		ft_free_arr(res);
		return (NULL);
	}
	return (res);
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
