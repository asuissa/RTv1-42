/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:55:08 by asuissa           #+#    #+#             */
/*   Updated: 2019/04/15 18:07:06 by asuissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		sphere_parse_1(t_sphere *sphere, char *line)
{
	char	**tab;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\tposition.x") == 0)
		sphere->center[0] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tposition.y") == 0)
		sphere->center[1] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tposition.z") == 0)
		sphere->center[2] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tradius") == 0)
		sphere->radius = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tcolor") == 0)
		sphere->attributes.color = ft_atoi_hexa(tab[1]);
	else if (ft_strcmp(tab[0], "\tshininess") == 0)
		sphere->attributes.shininess = ft_atoi_double(tab[1]);
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		sphere_parse_2(t_sphere *sphere, char *line)
{
	char	**tab;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\ttranslation.x") == 0)
		sphere->center[0] += ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\ttranslation.y") == 0)
		sphere->center[1] += ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\ttranslation.z") == 0)
		sphere->center[2] += ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\trotation.x") == 0)
		sphere->rotation[0] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else if (ft_strcmp(tab[0], "\trotation.y") == 0)
		sphere->rotation[1] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else if (ft_strcmp(tab[0], "\trotation.z") == 0)
		sphere->rotation[2] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		sphere_parse_coeff(t_sphere *sphere, char *line)
{
	char	**tab;
	int		i;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\tambient coeff") == 0
			&& (i = ft_atoi_double(tab[1])) < 1 && i > 0)
		sphere->attributes.ambient_coeff = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tdiffuse coeff") == 0
			&& (i = ft_atoi_double(tab[1])) < 1 && i > 0)
		sphere->attributes.diffuse_coeff = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tspecular coeff") == 0
			&& (i = ft_atoi_double(tab[1])) < 1 && i > 0)
		sphere->attributes.specular_coeff = ft_atoi_double(tab[1]);
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	if (sphere->attributes.ambient_coeff + sphere->attributes.diffuse_coeff
			+ sphere->attributes.specular_coeff > 1)
		return (0);
	return (1);
}

void	sphere_rot_trans(t_sphere *sphere, t_camera *cam)
{
	int		i;

	i = -1;
	while (++i < 3)
		sphere->center_relative[i] = sphere->center[i];
	translate(sphere->center_relative, cam->cam_pos);
	rotate(sphere->center_relative, cam->cam_angle);
}
