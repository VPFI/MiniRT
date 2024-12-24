/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:17:38 by vperez-f          #+#    #+#             */
/*   Updated: 2024/12/24 17:18:04 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*ts1;
	unsigned char	*ts2;

	i = 0;
	ts1 = (unsigned char *)s1;
	ts2 = (unsigned char *)s2;
	while ((ts1[i] != '\0') && (ts2[i] != '\0'))
	{
		if (ts1[i] != ts2[i])
		{
			return (ts1[i] - ts2[i]);
		}
		i++;
	}
	return (ts1[i] - ts2[i]);
}
