/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 20:27:25 by ymekraou          #+#    #+#             */
/*   Updated: 2019/03/20 04:51:36 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		init_light(t_light *light)
{
	light->specular = 0.9;
	light->diffuse_color = 0xFFFFFF;
	light->ambient = 0.3;
	light->pos[0] = -1.5;
	light->pos[1] = 0;
	light->pos[2] = 0;
	light->size = 0.5;
	light->next = NULL;
}

void	get_rgb_light(t_light *light)
{
	int		color;

	color = light->diffuse_color;

	light->diffuse_blue = (color % (16 * 16));
	color = color / (16 * 16);
	light->diffuse_green = (color % (16 * 16));
	color = color / (16 * 16);
	light->diffuse_red = (color % (16 * 16));
	color = color / (16 * 16);
}

t_light		*light_parsing(int fd, t_light *light)
{
	char	*line;
	char	**tab;

	init_light(light);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
			break;
		tab = ft_strsplit(line, ':');
		if (ft_strcmp(tab[0],"\tposition.x") == 0)
			light->pos[0] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tposition.y") == 0)
			light->pos[1] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tposition.z") == 0)
			light->pos[2] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tambient") == 0)
			light->ambient = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tspecular") == 0)
			light->specular = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tdiffuse_color") == 0)
			light->diffuse_color = ft_atoi_hexa(tab[1]);
		else if (ft_strcmp(tab[0],"\tsize") == 0)
			light->size = ft_atoi_double(tab[1]);
		free(tab[0]);
		free(tab[1]);
		free(tab);
		free(line);
	}
	get_rgb_light(light);
	return (light);
}
