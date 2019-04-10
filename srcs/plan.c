/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 10:54:03 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/10 05:01:09 by ymekraou         ###   ########.fr       */
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
		printf("line => %s\n", line);
		if (line[0] == '\0')
			break;
		if (!(tab = ft_strsplit(line, ':')) || tab[2] != NULL)
			ft_error("error parse word\n");
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
			plan->attributes.color = ft_atoi_hexa(tab[1]);
		else if (ft_strcmp(tab[0],"\tambient coeff") == 0)
			plan->attributes.ambient_coeff = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tdiffuse coeff") == 0)
			plan->attributes.diffuse_coeff = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tspecular coeff") == 0)
			plan->attributes.specular_coeff = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tshininess") == 0)
			plan->attributes.shininess = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\ttranslation.x") == 0)
			plan->point[0] += ft_atoi_double(tab[1]);	
		else if (ft_strcmp(tab[0],"\ttranslation.y") == 0)
			plan->point[1] += ft_atoi_double(tab[1]);	
		else if (ft_strcmp(tab[0],"\ttranslation.z") == 0)
			plan->point[2] += ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\trotation.x") == 0)
			plan->rotation[0] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
		else if (ft_strcmp(tab[0],"\trotation.y") == 0)
			plan->rotation[1] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
		else if (ft_strcmp(tab[0],"\trotation.z") == 0)
			plan->rotation[2] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
		else
		{
			ft_free_parse(tab, line);
			ft_error("parse plan error\n");
		}
		ft_free_parse(tab, line);
	}
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
	return (plan);
}
