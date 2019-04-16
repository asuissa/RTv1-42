/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylender_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:49:46 by asuissa           #+#    #+#             */
/*   Updated: 2019/04/16 20:21:17 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		cylender_parse_basics(t_cylender *cylender, char *line)
{
	char	**tab;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\tposition.x") == 0)
		cylender->origin[0] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tposition.y") == 0)
		cylender->origin[1] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tposition.z") == 0)
		cylender->origin[2] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tvector.x") == 0)
		cylender->line_vector[0] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tvector.y") == 0)
		cylender->line_vector[1] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tvector.z") == 0)
		cylender->line_vector[2] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tradius") == 0)
		cylender->radius = ft_atoi_double(tab[1]);
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		cylender_parse_movements(t_cylender *cylender, char *line)
{
	char	**tab;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\ttranslation.x") == 0)
		cylender->origin[0] += ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\ttranslation.y") == 0)
		cylender->origin[1] += ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\ttranslation.z") == 0)
		cylender->origin[2] += ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\trotation.x") == 0)
		cylender->rotation[0] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else if (ft_strcmp(tab[0], "\trotation.y") == 0)
		cylender->rotation[1] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else if (ft_strcmp(tab[0], "\trotation.z") == 0)
		cylender->rotation[2] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		cylender_parse_attributes(t_cylender *cylender, char *line)
{
	char	**tab;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\tambient coeff") == 0)
		cylender->attributes.ambient_coeff = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tdiffuse coeff") == 0)
		cylender->attributes.diffuse_coeff = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tspecular coeff") == 0)
		cylender->attributes.specular_coeff = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tcolor") == 0)
		cylender->attributes.color = ft_atoi_hexa(tab[1]);
	else if (ft_strcmp(tab[0], "\tshininess") == 0)
		cylender->attributes.shininess = ft_atoi_double(tab[1]);
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		cylender_parse(t_cylender *cylender, char *line)
{
	if (cylender_parse_basics(cylender, line))
		return (1);
	if (cylender_parse_movements(cylender, line))
		return (1);
	if (cylender_parse_attributes(cylender, line))
		return (1);
	return (0);
}
