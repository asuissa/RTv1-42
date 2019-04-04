/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_coord.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 17:00:07 by ymekraou          #+#    #+#             */
/*   Updated: 2019/03/31 23:41:10 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	update_light(t_light *light, t_camera *cam)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		light->direction_relative[i] = light->direction[i];	
		light->pos_relative[i] = light->pos[i];
	}
	translate(light->pos_relative, cam->cam_pos);
	rotate(light->pos_relative, cam->cam_angle);
	rotate(light->direction_relative, cam->cam_angle);
	norm_vector(light->direction_relative);
}


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
	t_plan *tmp;
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
	t_cylender *tmp;
	int		i;

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
	t_cone *tmp;
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

void	update_scene(t_env *env)
{
	t_elem	*tmp_elem;
	t_light	*tmp_light;

	tmp_elem = env->elem;
	while (tmp_elem)
	{
		tmp_elem->update_funct(tmp_elem->object, &(env->cam));
		tmp_elem = tmp_elem->next;
	}
	printf("elem updated\n");
	tmp_light = env->light;
	while (tmp_light)
	{
		update_light(tmp_light, &(env->cam));
		tmp_light= tmp_light->next;
	}
	printf("light updated\n");
}
