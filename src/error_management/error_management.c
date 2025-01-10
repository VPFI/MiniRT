/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:32:55 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/10 16:54:57 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_management.h"

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
