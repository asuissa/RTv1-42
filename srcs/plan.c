/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 10:54:03 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/17 18:03:12 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_plan	*init_plan(void)
{
	t_plan *plan;
	int i;

	if (!(plan = (t_plan*)malloc(sizeof(t_plan))))
		return (NULL);
	i = -1
	while (++i < 3)
	{
		plan->point[i] = 0;
		plan->normal[i] = 0;
		plan->rotation[i] = 0;
	}
	norm_vector(plan->normal);
	plan->attributes.shininess = 100;
	return (plan);
}

int		check_plan(t_plan *plan)
{
	if (check_attributes(&(plan->attributes)) == 0)
		return (0);
	return (1);
}

void	plan_rotation_translation(t_plan *plan, t_camera *cam)
{
	int		i;

	rotate(plan->normal, plan->rotation);
	norm_vector(plan->normal);
	i = -1;
	while (++i < 3)
	{
		plan->point_relative[i] = plan->point[i];
		plan->normal_relative[i] = plan->normal[i];
	}
	translate(plan->point_relative, cam->cam_pos);
	rotate(plan->point_relative, cam->cam_angle);
	rotate(plan->normal_relative, cam->cam_angle);
}

t_plan		*plan_parsing(int fd, t_camera *cam)
{
	t_plan		*plan;
	char		*line;

	if (!(plan = init_plan()))
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			break ;
		}
		else if (!(plan_parse(plan, line))) 		
		{
			free(line);
			return (NULL);
		}
		else
			free(line);
	}
	if (!(check_plan(plan)))
		return (NULL);
	plan_rotation_translation(plan, cam);
	return (plan);
}
