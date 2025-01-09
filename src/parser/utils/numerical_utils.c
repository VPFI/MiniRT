/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numerical_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:02:26 by vperez-f          #+#    #+#             */
/*   Updated: 2025/01/09 17:02:56 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


float	sum_parts(int integer_part, float decimal_part, char *array)
{
	if (integer_part >= 0 && array[0] != '-')
	{
		return ((float)(integer_part + decimal_part));
	}
	else
	{
		return ((float)(integer_part - decimal_part));
	}	
}
void	check_bounds(float num, float min, float max)
{
	if (num > max)
	{
		fprintf(stderr, "Maximum threshold: %f || Input --> %f\n", max, num);
		exit_err(ERR_EMPTY_MSG, "Maximum value threshold exceeded\n", 2);
	}
	if (num < min)
	{
		fprintf(stderr, "Minimum threshold: %f || Input --> %f\n", min, num);
		exit_err(ERR_EMPTY_MSG, "Minimum value threshold not reached\n", 2);
	}
}

float	ft_atof(char *array, float min, float max)
{
	int		i;
	float	res;
	char	*aux;
	float	decimal_part;

	i = 0;
	decimal_part = 0;
	if (ft_strlen(array) > 10)
	{
		fprintf(stderr, "Input --> %s\n", array);
		exit_err(ERR_EMPTY_MSG, "Maximum value threshold exceeded\n", 2);
	}
	while (array[i] && array[i] != '.')
		i++;		
	if (i != (int)ft_strlen(array) && array[i + 1])
	{
		aux = ft_substr(array, (i + 1), ft_strlen(array));
		if (!aux)
			exit_err(ERR_MEM_MSG, "(malloc)", 1);
		decimal_part = (ft_atoi(aux) / powf(10, ft_strlen(aux)));
		free(aux);
	}
	res = sum_parts(ft_atoi(array), decimal_part, array);
	check_bounds(res, min, max);
	return (res);
}

t_vect	input_to_vect(char *input, float min, float max)
{
	t_vect	res;
	int		count;
	char	**vec_comp;

	vec_comp = ft_split(input, ',');
	count = count_components(vec_comp);
	if (count != 3)
		exit_err(ERR_VECT_MSG, input, 2);
	res.x = ft_atof(vec_comp[0], min, max);
	res.y = ft_atof(vec_comp[1], min, max);
	res.z = ft_atof(vec_comp[2], min, max);
	ft_free_arr(vec_comp);
	return (res);
}
