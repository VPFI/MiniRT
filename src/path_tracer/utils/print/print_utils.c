/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:44:14 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 15:24:35 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	print_vec_s(t_vect vect, char*msg)
{
	printf("%s X: %f\n", msg, vect.x);
	printf("%s Y: %f\n", msg, vect.y);
	printf("%s Z: %f\n\n", msg, vect.z);
}

void	print_vec(t_vect vect)
{
	printf("VECT X: %f\n", vect.x);
	printf("VECT Y: %f\n", vect.y);
	printf("VECT Z: %f\n", vect.z);
}

void	print_list(t_object *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("OBJ: %i --- type: %i\n", i, list->type);
		i++;
		list = list->next;
	}
}
