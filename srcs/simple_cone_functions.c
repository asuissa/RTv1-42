/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cone_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 21:26:20 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/20 02:45:27 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			test_opposite_cone(double point[3], t_cone *cone)
{
	double	tmp[3];
	int		i;

	i = -1;
	while (++i < 3)
		tmp[i] = point[i] - cone->origin_relative[i];
	norm_vector(tmp);
	if (dot_product(tmp, cone->vector_relative) < 0)
		return (1);
	return (0);
}

void		simple_cone_ratio(double ratio[2], double a, double b, double c)
{
	if (pow(b, 2) - (4 * a * c) == 0)
	{
		ratio[0] = -(b / (2 * a));
		ratio[1] = -(b / (2 * a));
	}
	else
	{
		ratio[0] = (-(b) + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
		ratio[1] = (-(b) - sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
	}
	if (ratio[1] < 0)
		ratio[1] = ratio[0];
	if (ratio[0] < 0)
		ratio[0] = ratio[1];
}

void		cone_hit_point(double ratio, double cam_center[3],
				double ray_vector[3], double tmp[3])
{
	int	i;

	i = -1;
	while (++i < 3)
		tmp[i] = cam_center[i] + (ratio * ray_vector[i]);
}

int			swap_hit_point(double tmp1[3], double tmp2[3])
{
	int	i;

	i = -1;
	while (++i < 3)
		tmp1[i] = tmp2[i];
	return (1);
}

int			test_simple_cone(double ratio[2], double tmp1[3],
				double tmp2[3], t_cone *cone)
{
	if (ratio[0] == ratio[1])
		if (test_opposite_cone(tmp1, cone))
			return (1);
	if ((ratio[0] < ratio[1]))
	{
		if (test_opposite_cone(tmp1, cone))
			return (1);
		if (test_opposite_cone(tmp2, cone))
			return (swap_hit_point(tmp1, tmp2));
	}
	if ((ratio[1] < ratio[0]))
	{
		if (test_opposite_cone(tmp2, cone))
			return (swap_hit_point(tmp1, tmp2));
		if (test_opposite_cone(tmp1, cone) && ratio[0] >= 0)
			return (1);
	}
	return (0);
}
