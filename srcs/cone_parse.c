/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 20:33:24 by asuissa           #+#    #+#             */
/*   Updated: 2019/04/16 15:56:27 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		cone_parse_basics(t_cone *cone, char *line)
{
	char	**tab;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\tposition.x") == 0)
		cone->origin[0] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tposition.y") == 0)
		cone->origin[1] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tposition.z") == 0)
		cone->origin[2] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tvector.x") == 0)
		cone->vector[0] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tvector.y") == 0)
		cone->vector[1] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tvector.z") == 0)
		cone->vector[2] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\taperture") == 0)
		cone->aperture = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		cone_parse_movements(t_cone *cone, char *line)
{
	char	**tab;
	double	i;

	if (!(tab = parse_word(line)))
		return (0);
	else if (ft_strcmp(tab[0], "\ttranslation.x") == 0)
		cone->origin[0] += ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\ttranslation.y") == 0)
		cone->origin[1] += ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\ttranslation.z") == 0)
		cone->origin[2] += ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\trotation.x") == 0)
		cone->rotation[0] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else if (ft_strcmp(tab[0], "\trotation.y") == 0)
		cone->rotation[1] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else if (ft_strcmp(tab[0], "\trotation.z") == 0)
		cone->rotation[2] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		cone_parse_attributes(t_cone *cone, char *line)
{
	char	**tab;
	double	i;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\tambient coeff") == 0
			&& (i = ft_atoi_double(tab[1])) < 1 && i > 0)
		cone->attributes.ambient_coeff = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tdiffuse coeff") == 0
			&& (i = ft_atoi_double(tab[1])) < 1 && i > 0)
		cone->attributes.diffuse_coeff = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tspecular coeff") == 0
			&& (i = ft_atoi_double(tab[1])) < 1 && i > 0)
		cone->attributes.specular_coeff = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tshininess") == 0)
		cone->attributes.shininess = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tcolor") == 0)
		cone->attributes.color = ft_atoi_hexa(tab[1]);
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}
