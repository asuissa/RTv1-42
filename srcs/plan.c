/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 10:54:03 by ymekraou          #+#    #+#             */
/*   Updated: 2019/03/10 18:53:36 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_plan(t_plan *plan)
{
	plan->type = "plan";
	plan->point[0] = 0;
	plan->point[1] = -0.5;
	plan->point[2] = 0;

	plan->normal[0] = 0;
	plan->normal[1] = -1;
	plan->normal[2] = 0;
	norm_vector(plan->normal);
	plan->color = 0x000000FF;
	plan->code = 2;
}

t_plan		*plan_parsing(int fd)
{
	t_plan		*plan;
	char		*line;
	char		**tab;

	plan = (t_plan*)malloc(sizeof(t_plan));
	init_plan(plan);
	while (get_next_line(fd, &line) > 0)
	{
		printf("line => %s\n", line);
		if (line[0] == '\0')
			break;
		tab = ft_strsplit(line, ':');
		if (ft_strcmp(tab[0],"\tposition.x") == 0)
			plan->point[0] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tposition.y") == 0)
			plan->point[1] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tposition.z") == 0)
			plan->point[2] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tnormal.x") == 0)
			plan->normal[0] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tnormal.y") == 0)
			plan->normal[1] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tnormal.z") == 0)
			plan->normal[2] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tcolor") == 0)
			plan->color = ft_atoi_hexa(tab[1]);
		free(tab[0]);
		free(tab[1]);
		free(tab);
		free(line);
	}
	norm_vector(plan->normal);
	return (plan);
}
