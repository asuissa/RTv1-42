/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 09:27:25 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/04 15:32:32 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double		b_sphere(double ray_vector[3],
								double cam_center[3], double sphere_center[3])
{
	double tmp[3];

	tmp[0] = cam_center[0] - sphere_center[0];
	tmp[1] = cam_center[1] - sphere_center[1];
	tmp[2] = cam_center[2] - sphere_center[2];
	return (2 * dot_product(tmp, ray_vector));
}

double		c_sphere(double sphere_radius,
								double cam_center[3], double sphere_center[3])
{
	double tmp[3];

	tmp[0] = cam_center[0] - sphere_center[0];
	tmp[1] = cam_center[1] - sphere_center[1];
	tmp[2] = cam_center[2] - sphere_center[2];
	return (dot_product(tmp, tmp) - pow(sphere_radius, 2));
}

void		hit_sphere(double ray_vector[3],
						double cam_center[3], void *data, t_hit *hit_point)
{
	double		discr[3];
	double		ratio;
	double		tmp[3];
	t_sphere	*sphere;

	sphere = (t_sphere*)data;
	discr[0] = dot_product(ray_vector, ray_vector);
	discr[1] = b_sphere(ray_vector, cam_center, sphere->center_relative);
	discr[2] = c_sphere(sphere->radius, cam_center, sphere->center_relative);
	if (pow(discr[1], 2) - (4 * discr[0] * discr[2]) >= 0)
	{
		ratio = compute_ratio(discr[0], discr[1], discr[2]);
		if (ratio >= 0)
		{
			tmp[0] = cam_center[0] + (ratio * ray_vector[0]);
			tmp[1] = cam_center[1] + (ratio * ray_vector[1]);
			tmp[2] = cam_center[2] + (ratio * ray_vector[2]);
			if (compute_hit_point(hit_point, tmp, cam_center, sphere->color))
			{
				normal_sphere(sphere->center_relative, hit_point);
				hit_point->obj = data;
			}
		}
	}
}
