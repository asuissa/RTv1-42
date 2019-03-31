/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 18:48:02 by ymekraou          #+#    #+#             */
/*   Updated: 2019/03/22 12:16:53 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void 	normal_sphere(double sphere_center[3], t_hit *hit_point)
{
	int i;

	i = -1;
	while (++i < 3)
		hit_point->normal[i] = (hit_point->coord[i] - sphere_center[i]);
	norm_vector(hit_point->normal);
}

void 	normal_plan(double normal_plan[3], t_hit *hit_point)
{
	int i;

	i = -1;
	while (++i < 3)
		hit_point->normal[i] = -normal_plan[i];
}

void	normal_cylender(t_cylender *cylender, t_hit *hit_point)
{
	double tmp[3];
	double t;
	int i;

	i = -1;
	while (++i < 3)
		tmp[i] = hit_point->coord[i] - cylender->origin[i];
	t = dot_product(tmp, cylender->line_vector);
	i = -1;
	while (++i < 3)
		tmp[i] = cylender->origin[i] + t * cylender->line_vector[i];
	i = -1;
	while (++i < 3)
		hit_point->normal[i] = (hit_point->coord[i] - tmp[i]);
	norm_vector(hit_point->normal);
}

void	normal_cone(t_cone *cone, t_hit *hit_point)
{
	double tmp[3];
	double t;
	int i;

	i = -1;
	while (++i < 3)
		tmp[i] = hit_point->coord[i] - cone->origin[i];
	t = dot_product(tmp, tmp) / dot_product(cone->vector, tmp);
	i = -1;
	while (++i < 3)
		tmp[i] = cone->origin[i] + t * cone->vector[i];
	i = -1;
	while (++i < 3)
		hit_point->normal[i] = (hit_point->coord[i] - tmp[i]);
	norm_vector(hit_point->normal);
}
