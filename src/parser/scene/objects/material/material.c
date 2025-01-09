/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:11:15 by vperez-f          #+#    #+#             */
/*   Updated: 2024/12/24 17:22:58 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



static int	get_material_index(char *id)
{
	if (!id)
		exit_err(ERR_ATTR_MSG, "Wrong material type\n", 2);
	ft_strtolower(id);
	if (!ft_strcmp(id, "lambertian") || !ft_strcmp(id, "diffuse"))
		return (LAMBERTIAN);
	else if (!ft_strcmp(id, "metal") || !ft_strcmp(id, "metallic"))
		return (METAL);
	else if (!ft_strcmp(id, "glossy") || !ft_strcmp(id, "plastic"))
		return (GLOSSY);
	else if (!ft_strcmp(id, "glass") || !ft_strcmp(id, "dielectric"))
		return (DIELECTRIC);
	else if (!ft_strcmp(id, "emissive"))
		return (EMISSIVE);
	else
		exit_err(ERR_MAT_MSG, id, 2);
	return (0);
}

void	parse_material(char **settings, t_material *mat)
{
	int	amount;

	amount = count_components(settings);
	if (amount != 6)
		exit_err(ERR_EMPTY_MSG, "Missing material components\n", 2);
	mat->type = get_material_index(settings[1]);		
	mat->specular = ft_atof(settings[2], 0, 1);
	mat->metal_roughness = ft_atof(settings[3], 0, 1);
	mat->refraction_index = ft_atof(settings[4], 0, 100);
	mat->emission_intensity = ft_atof(settings[5], 0, (float)INT_MAX);
}

static bool	get_pattern_bool(char *id)
{
	if (id)
	{
		if (!ft_strcmp(id, "0") || !ft_strcmp(id, "false"))
		{
			return (false);
		}
		else if (!ft_strcmp(id, "1") || !ft_strcmp(id, "true"))
		{
			return (true);
		}
	}
	exit_err(ERR_EMPTY_MSG, "Unknown pattern value\n", 2);
	return (false);
}

void	parse_pattern(char **settings, t_material *mat)
{
	int	amount;

	amount = count_components(settings);
	if (amount != 3)
		exit_err(ERR_EMPTY_MSG, "Missing pattern components\n", 2);
	mat->pattern = get_pattern_bool(settings[1]);
	mat->pattern_dim = ft_atof(settings[2], 0, (float)INT_MAX);
}
