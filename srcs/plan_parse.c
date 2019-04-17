/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:16:43 by asuissa           #+#    #+#             */
/*   Updated: 2019/04/17 16:05:12 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		plan_parse_basics(t_plan *plan, char *line)
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
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		plan_parse_movements(t_plan *plan, char *line)
{
	char	**tab;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\ttranslation.x") == 0)
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
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		plan_parse_attributes(t_plan *plan, char *line)
{
	char	**tab;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\tambient coeff") == 0)
		plan->attributes.ambient_coeff = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tdiffuse coeff") == 0)
		plan->attributes.diffuse_coeff = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tspecular coeff") == 0)
		plan->attributes.specular_coeff = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tshininess") == 0)
		plan->attributes.shininess = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tcolor") == 0)
		plan->attributes.color = ft_atoi_hexa(tab[1]);
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		plan_parse(t_plan *plan, char *line)
{
	if (plan_parse_basics(plan, line))
		return (1);
	if (plan_parse_movements(plan, line))
		return (1);
	if (plan_parse_attributes(plan, line))
		return (1);
	return (0);
}
