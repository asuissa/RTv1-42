/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 10:32:58 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/13 11:35:50 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	get_rgb_hit_point(t_hit *hit_point)
{
	int		color;

	color = hit_point->color;

	hit_point->blue = (double)(color % (16 * 16));
	color = color / (16 * 16);
	hit_point->green = (double)(color % (16 * 16));
	color = color / (16 * 16);
	hit_point->red = (double)(color % (16 * 16));
	color = color / (16 * 16);
}

void		update_hitpoint(t_hit *hit_point,
				double tmp[3], t_attributes attributes)
{
	hit_point->coord[0] = tmp[0];
	hit_point->coord[1] = tmp[1];
	hit_point->coord[2] = tmp[2];
	hit_point->hit = 1;
	hit_point->color = attributes.color;
	hit_point->ambient_coeff = attributes.ambient_coeff;
	hit_point->diffuse_coeff = attributes.diffuse_coeff;
	hit_point->specular_coeff = attributes.specular_coeff;
	hit_point->shininess = attributes.shininess;
}

void		init_hit_point(t_hit *hit_point)
{
	hit_point->coord[0] = 0;
	hit_point->coord[1] = 0;
	hit_point->coord[2] = 0;
	hit_point->normal[0] = 0;
	hit_point->normal[1] = 0;
	hit_point->normal[2] = 0;
	hit_point->red = 0;
	hit_point->green = 0;
	hit_point->blue = 0;
	hit_point->color = 0x00000000;
	hit_point->hit = 0;
	hit_point->obj = NULL;
}

int			compute_hit_point(t_hit *hit_point, double tmp[3],
								double cam_center[3], t_attributes attributes)
{
	if (hit_point->hit > 0)
	{
		if (point_distance(tmp, cam_center)
				< point_distance(hit_point->coord, cam_center))
		{
			update_hitpoint(hit_point, tmp, attributes);
			return (1);
		}
		return (0);
	}
	else
	{
		update_hitpoint(hit_point, tmp, attributes);
		return (1);
	}
}
