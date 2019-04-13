/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 18:48:02 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/13 10:20:50 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	normal_sphere(double sphere_center[3], t_hit *hit_point)
{
	int i;

	i = -1;
	while (++i < 3)
		hit_point->normal[i] = (hit_point->coord[i] - sphere_center[i]);
	norm_vector(hit_point->normal);
}

void	normal_plan(double normal_plan[3], t_hit *hit_point)
{
	int i;

	i = -1;
	while (++i < 3)
		hit_point->normal[i] = normal_plan[i];
	norm_vector(hit_point->normal);
}

void	normal_cylender(t_cylender *cylender, t_hit *hit_point)
{
	double	tmp[3];
	double	t;
	int		i;

	t = -(dot_product(cylender->origin_relative, cylender->line_vector_relative)
		- dot_product(hit_point->coord, cylender->line_vector_relative));
	i = -1;
	while (++i < 3)
		tmp[i] = cylender->origin_relative[i]
			+ t * cylender->line_vector_relative[i];
	i = -1;
	while (++i < 3)
		hit_point->normal[i] = (hit_point->coord[i] - tmp[i]);
	norm_vector(hit_point->normal);
}

void	normal_cone(t_cone *cone, t_hit *hit_point)
{
	double	tmp[3];
	double	t;
	int		i;

	i = -1;
	while (++i < 3)
		tmp[i] = hit_point->coord[i] - cone->origin_relative[i];
	t = dot_product(tmp, tmp) / dot_product(cone->vector_relative, tmp);
	i = -1;
	while (++i < 3)
		tmp[i] = cone->origin_relative[i] + t * cone->vector_relative[i];
	i = -1;
	while (++i < 3)
		hit_point->normal[i] = (hit_point->coord[i] - tmp[i]);
	norm_vector(hit_point->normal);
}
