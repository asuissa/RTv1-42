/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:56:01 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/09 02:55:34 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double		plan_ratio(double tmp[3], double ray_vector[3],
						double cam_center[3], t_plan *plan)
{
	int		i;
	double	ratio;

	i = -1;
	while (++i < 3)
		tmp[i] = plan->point_relative[i] - cam_center[i];
	ratio = dot_product(tmp, plan->normal_relative)
			/ dot_product(ray_vector, plan->normal_relative);
	return (ratio);
}

void		hit_plan(double ray_vector[3], double cam_center[3],
						void *data, t_hit *hit_point)
{
	double	tmp[3];
	double	ratio;
	t_plan	*plan;
	int		i;

	plan = (t_plan*)data;
	if (fabs(dot_product(ray_vector, plan->normal_relative)) > 0.0001)
	{
		ratio = plan_ratio(tmp, ray_vector, cam_center, plan);
		if (ratio >= 0.0001)
		{
			i = -1;
			while (++i < 3)
				tmp[i] = cam_center[i] + ratio * ray_vector[i];
			if (compute_hit_point(hit_point, tmp, cam_center, plan->attributes))
			{
				normal_plan(plan->normal_relative, hit_point);
				hit_point->obj = data;
			}
		}
	}
}
