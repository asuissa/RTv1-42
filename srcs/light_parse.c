/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asuissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:40:54 by asuissa           #+#    #+#             */
/*   Updated: 2019/04/17 15:17:46 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		light_parse_basics(t_light *light, char *line)
{
	char	**tab;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\tposition.x") == 0)
		light->pos[0] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tposition.y") == 0)
		light->pos[1] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tposition.z") == 0)
		light->pos[2] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tangle.x") == 0)
		light->light_angle[0] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else if (ft_strcmp(tab[0], "\tangle.y") == 0)
		light->light_angle[1] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else if (ft_strcmp(tab[0], "\tangle.z") == 0)
		light->light_angle[2] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		light_parse_attributes(t_light *light, char *line)
{
	char	**tab;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\taperture") == 0)
		light->aperture = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tcolor") == 0)
		light->color = ft_atoi_hexa(tab[1]);
	else if (ft_strcmp(tab[0], "\tpower") == 0)
		light->power = ft_atoi_double(tab[1]);
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		light_parse(t_light *light, char *line)
{
	if (light_parse_basics(light, line))
		return (1);
	if (light_parse_attributes(light, line))
		return (1);
	return (0);
}

void	light_rotation_translation(t_light *light, t_camera *cam)
{
	int		i;

	rotate(light->direction, light->light_angle);
	i = -1;
	while (++i < 3)
	{
		light->pos_relative[i] = light->pos[i];
		light->direction_relative[i] = light->direction[i];
	}
	translate(light->pos_relative, cam->cam_pos);
	rotate(light->pos_relative, cam->cam_angle);
	rotate(light->direction_relative, cam->cam_angle);
	norm_vector(light->direction_relative);
	get_rgb_light(light);
}
