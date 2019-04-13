/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylender.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:58:18 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/13 10:17:28 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double		a_cylender(double ray_vector[3], double line_vector[3])
{
	double	tmp[3];
	int		i;

	i = -1;
	while (++i < 3)
		tmp[i] = (ray_vector[i]
				- dot_product(ray_vector, line_vector) * line_vector[i]);
	return (dot_product(tmp, tmp));
}

double		b_cylender(double ray_vector[3],
						t_cylender cylender, double cam_center[3])
{
	double	delta[3];
	double	tmp[3];
	double	tmp2[3];
	int		i;

	i = -1;
	while (++i < 3)
		delta[i] = cam_center[i] - cylender.origin_relative[i];
	i = -1;
	while (++i < 3)
		tmp[i] = ray_vector[i]
				- dot_product(ray_vector, cylender.line_vector_relative)
				* cylender.line_vector_relative[i];
	i = -1;
	while (++i < 3)
		tmp2[i] = delta[i] - dot_product(delta, cylender.line_vector_relative)
				* cylender.line_vector_relative[i];
	return (2 * dot_product(tmp, tmp2));
}

double		c_cylender(t_cylender cylender, double cam_center[3])
{
	double	delta[3];
	double	tmp[3];
	int		i;

	i = -1;
	while (++i < 3)
		delta[i] = cam_center[i] - cylender.origin_relative[i];
	i = -1;
	while (++i < 3)
		tmp[i] = delta[i]
			- dot_product(delta, cylender.line_vector_relative)
			* cylender.line_vector_relative[i];
	return (dot_product(tmp, tmp) - pow(cylender.radius, 2));
}

void		hit_cylender(double ray_vector[3],
						double cam_center[3], void *data, t_hit *hit_point)
{
	double		discr[3];
	double		ratio;
	double		tmp[3];
	t_cylender	*cylender;

	cylender = (t_cylender*)data;
	discr[0] = a_cylender(ray_vector, cylender->line_vector_relative);
	discr[1] = b_cylender(ray_vector, *cylender, cam_center);
	discr[2] = c_cylender(*cylender, cam_center);
	if (pow(discr[1], 2) - (4 * discr[0] * discr[1]) >= 0)
	{
		ratio = compute_ratio(discr[0], discr[1], discr[2]);
		if (ratio >= 0)
		{
			tmp[0] = cam_center[0] + ratio * ray_vector[0];
			tmp[1] = cam_center[1] + ratio * ray_vector[1];
			tmp[2] = cam_center[2] + ratio * ray_vector[2];
			if (compute_hit_point(hit_point, tmp,
						cam_center, cylender->attributes))
			{
				normal_cylender(cylender, hit_point);
				hit_point->obj = data;
			}
		}
	}
}
