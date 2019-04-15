/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:16:43 by asuissa           #+#    #+#             */
/*   Updated: 2019/04/15 19:48:44 by asuissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		plan_parse_1(t_plan *plan, char *line)
{
	char	**tab;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\tposition.x") == 0)
		plan->point[0] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tposition.y") == 0)
		plan->point[1] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tposition.z") == 0)
		plan->point[2] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tnormal.x") == 0)
		plan->normal[0] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tnormal.y") == 0)
		plan->normal[1] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tnormal.z") == 0)
		plan->normal[2] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tcolor") == 0)
		plan->attributes.color = ft_atoi_hexa(tab[1]);
	else
	{
		printf("test1\n");
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		plan_parse_2(t_plan *plan, char *line)
{
	char	**tab;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\tshininess") == 0)
		plan->attributes.shininess = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\ttranslation.x") == 0)
		plan->point[0] += ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\ttranslation.y") == 0)
		plan->point[1] += ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\ttranslation.z") == 0)
		plan->point[2] += ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\trotation.x") == 0)
		plan->rotation[0] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else if (ft_strcmp(tab[0], "\trotation.y") == 0)
		plan->rotation[1] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else if (ft_strcmp(tab[0], "\trotation.z") == 0)
		plan->rotation[2] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else
	{
		printf("test2\n");
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		plan_parse_coeff(t_plan *plan, char *line)
{
	char	**tab;
	double	i;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\tambient coeff") == 0
			&& (i = ft_atoi_double(tab[1])) < 1 && i > 0)
		plan->attributes.ambient_coeff = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tdiffuse coeff") == 0
			&& (i = ft_atoi_double(tab[1])) < 1 && i > 0)
		plan->attributes.diffuse_coeff = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tspecular coeff") == 0
			&& (i = ft_atoi_double(tab[1])) < 1 && i > 0)
		plan->attributes.specular_coeff = ft_atoi_double(tab[1]);
	else
	{
		printf("test3\n");
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	if (plan->attributes.ambient_coeff + plan->attributes.diffuse_coeff
			+ plan->attributes.specular_coeff > 1)
		return (0);
	return (1);
}

void	plan_rot_trans(t_plan *plan, t_camera *cam)
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
