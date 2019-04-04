/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 10:29:10 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/04 15:32:55 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double		compute_a_cone(double ray_vector[3], t_cone cone)
{
	double res;

	res = dot_product(ray_vector, cone.vector_relative);
	return ((res * res) - (cos(cone.aperture) * cos(cone.aperture)));
}

double		compute_b_cone(double ray_vector[3],
							t_cone cone, double cam_center[3])
{
	double	tmp[3];
	double	tmp2;
	int		i;

	i = -1;
	while (++i < 3)
		tmp[i] = cam_center[i] - cone.origin_relative[i];
	tmp2 = (dot_product(ray_vector, cone.vector_relative)
			* dot_product(tmp, cone.vector_relative))
			- (dot_product(ray_vector, tmp) * pow(cos(cone.aperture), 2));
	return (2 * tmp2);
}

double		compute_c_cone(t_cone cone, double cam_center[3])
{
	double	tmp[3];
	double	tmp2;
	int		i;

	i = -1;
	while (++i < 3)
		tmp[i] = cam_center[i] - cone.origin_relative[i];
	tmp2 = pow(dot_product(tmp, cone.vector_relative), 2)
		- dot_product(tmp, tmp) * pow(cos(cone.aperture), 2);
	return (tmp2);
}

int			test_opposite_cone(double point[3], t_cone cone)
{
	double	tmp[3];
	int		i;

	i = -1;
	while (++i < 3)
		tmp[i] = point[i] - cone.origin_relative[i];
	norm_vector(tmp);
	if (dot_product(tmp, cone.vector_relative) < 0)
		return (1);
	return (0);
}

void		hit_cone(double ray_vector[3],
						double cam_center[3], void *data, t_hit *hit_point)
{
	double	discr[3];
	double	ratio;
	double	tmp[3];
	t_cone	*cone;

	cone = (t_cone*)data;
	discr[0] = compute_a_cone(ray_vector, *cone);
	discr[1] = compute_b_cone(ray_vector, *cone, cam_center);
	discr[2] = compute_c_cone(*cone, cam_center);
	if (pow(discr[1], 2) - (4 * discr[0] * discr[2]) >= 0)
	{
		ratio = compute_ratio(discr[0], discr[1], discr[2]);
		tmp[0] = cam_center[0] + ratio * ray_vector[0];
		tmp[1] = cam_center[1] + ratio * ray_vector[1];
		tmp[2] = cam_center[2] + ratio * ray_vector[2];
		if (test_opposite_cone(tmp, *cone))
		{
			if (compute_hit_point(hit_point, tmp, cam_center, cone->color))
			{
				normal_cone(cone, hit_point);
				hit_point->obj = data;
			}
		}
	}
}
