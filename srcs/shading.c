/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:06:23 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/13 12:09:39 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		shading(t_light *light, double light_ray[3], t_elem *elem, t_hit *hit_point)
{
	t_hit	shade_hit;
	t_elem	*tmp;
	double	vector[3];
	double	bias[3];
	double	reversed_light[3];
	int		i;

	init_hit_point(&shade_hit);
	i = -1;
	while (++i < 3)
	{
		bias[i] = (hit_point->coord[i] + 0.00001 * hit_point->normal[i]); 
		vector[i] = bias[i] - light->pos_relative[i];
		shade_hit.coord[i] = bias[i];
		reversed_light[i] = -light_ray[i];
	}
	norm_vector(vector);
	if (dot_product(reversed_light, light->direction_relative) < light->aperture)
		return (0);
	tmp = elem;
	while (tmp)
	{
		tmp->hit_funct(vector, light->pos_relative, tmp->object, &shade_hit);
		if (point_distance(bias, light->pos_relative) > point_distance(shade_hit.coord, light->pos_relative))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
