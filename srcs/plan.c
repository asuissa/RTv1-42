/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 10:54:03 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/15 17:48:12 by asuissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		init_plan(t_plan *plan)
{
	plan->type = "plan";
	plan->point[0] = 0;
	plan->point[1] = -1;
	plan->point[2] = 0;
	plan->normal[0] = 0;
	plan->normal[1] = 1;
	plan->normal[2] = 0;
	plan->rotation[0] = 0;
	plan->rotation[1] = 0;
	plan->rotation[2] = 0;
	norm_vector(plan->normal);
	plan->attributes.shininess = 100;
}

t_plan		*plan_parsing(int fd, t_camera *cam)
{
	t_plan		*plan;
	char		*line;
	char		**tab;
	int			i;

	plan = (t_plan*)malloc(sizeof(t_plan));
	init_plan(plan);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			break ; //verifier free
		}
		else if (!plan_parse_1(plan, line) && !plan_parse_2(plan, line)
				&& !plan_parse_coeff(plan, line))
		{
			free(line);
			return (NULL);
		}
		else
			free(line);
	}
	plan_rot_trans(plan, cam);
	return (plan);
}
