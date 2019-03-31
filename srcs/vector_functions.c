/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 23:45:56 by ymekraou          #+#    #+#             */
/*   Updated: 2019/03/13 10:01:45 by eduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

/*
void		cross_product(double vec1[3], double vec2[3], double angle, double res[3])
{
	double magn;

	magn = sqrt(dot_product(vec, vec));
	
}
*/
