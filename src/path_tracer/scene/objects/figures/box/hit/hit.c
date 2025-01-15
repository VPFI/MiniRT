/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpf <vpf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 23:43:01 by vpf               #+#    #+#             */
/*   Updated: 2024/12/30 18:26:48 by vpf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



bool	hit_box(t_ray ray, t_figure fig, t_hit_info *hit_info, float *bounds)
{
	t_hit_info	internal_hit_info;

	if (ray_hit(fig.box.faces, ray, &internal_hit_info, NULL))
	{
		if (internal_hit_info.t <= bounds[MIN] || bounds[MAX] <= internal_hit_info.t)
			return (false);
		hit_info->t = internal_hit_info.t;
		return (true);
	}
	return (false);
}
