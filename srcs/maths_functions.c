/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 10:21:27 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/04 17:08:13 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double		dot_product(double vec1[3], double vec2[3])
{
	return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]);
}

void		norm_vector(double vec[3])
{
	double magn;

	magn = sqrt(dot_product(vec, vec));
	vec[0] /= magn;
	vec[1] /= magn;
	vec[2] /= magn;
}

double		point_distance(double coord_one[3], double coord_two[3])
{
	double	tmp[3];
	int		i;

	i = -1;
	while (++i < 3)
		tmp[i] = pow((coord_one[i] - coord_two[i]), 2);
	return (sqrt(tmp[0] + tmp[1] + tmp[2]));
}

double		compute_ratio(double a, double b, double c)
{
	double	ratio1;
	double	ratio2;

	if (pow(b, 2) - (4 * a * c) == 0)
		return (-(b / (2 * a)));
	else
	{
		ratio1 = (-(b) + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
		ratio2 = (-(b) - sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
		if (ratio2 < ratio1 && ratio2 >= 0)
			ratio1 = ratio2;
		return (ratio1);
	}
}
