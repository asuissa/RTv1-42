/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 10:06:40 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/13 10:09:48 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	update_sphere(void *sphere, t_camera *cam)
{
	t_sphere *tmp;

	tmp = sphere;
	tmp->center_relative[0] = tmp->center[0];
	tmp->center_relative[1] = tmp->center[1];
	tmp->center_relative[2] = tmp->center[2];
	translate(tmp->center_relative, cam->cam_pos);
	rotate(tmp->center_relative, cam->cam_angle);
}

void	update_plan(void *plan, t_camera *cam)
{
	t_plan	*tmp;
	int		i;

	tmp = plan;
	i = -1;
	while (++i < 3)
	{
		tmp->normal_relative[i] = tmp->normal[i];
		tmp->point_relative[i] = tmp->point[i];
	}
	translate(tmp->point_relative, cam->cam_pos);
	rotate(tmp->point_relative, cam->cam_angle);
	rotate(tmp->normal_relative, cam->cam_angle);
}

void	update_cylender(void *cylender, t_camera *cam)
{
	t_cylender	*tmp;
	int			i;

	tmp = cylender;
	i = -1;
	while (++i < 3)
	{
		tmp->origin_relative[i] = tmp->origin[i];
		tmp->line_vector_relative[i] = tmp->line_vector[i];
	}
	translate(tmp->origin_relative, cam->cam_pos);
	rotate(tmp->origin_relative, cam->cam_angle);
	rotate(tmp->line_vector_relative, cam->cam_angle);
	norm_vector(tmp->line_vector_relative);
}

void	update_cone(void *cone, t_camera *cam)
{
	t_cone	*tmp;
	int		i;

	tmp = cone;
	i = -1;
	while (++i < 3)
	{
		tmp->origin_relative[i] = tmp->origin[i];
		tmp->vector_relative[i] = tmp->vector[i];
	}
	translate(tmp->origin_relative, cam->cam_pos);
	rotate(tmp->origin_relative, cam->cam_angle);
	rotate(tmp->vector_relative, cam->cam_angle);
	norm_vector(tmp->vector_relative);
}
