/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 10:10:33 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/13 10:12:11 by ymekraou         ###   ########.fr       */
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
	tmp_light = env->light;
	while (tmp_light)
	{
		update_light(tmp_light, &(env->cam));
		tmp_light = tmp_light->next;
	}
}
