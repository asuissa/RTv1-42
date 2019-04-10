/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 20:27:25 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/10 22:08:57 by asuissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		init_light(t_light *light)
{
	int	i;
	
	i = -1;
	while (++i < 3)
	{
		light->pos[i] = 0;
		light->light_angle[i] = 0;;
	}	
	light->direction[0] = 0;
	light->direction[1] = 0;
	light->direction[2] = 1;
	light->color = 0xFFFFFF;
	light->power = 10000.0;
	light->next = NULL;
	light->aperture = cos(M_PI);
}

void	get_rgb_light(t_light *light)
{
	int		color;

	color = light->color;

	light->blue = (double)(color % (16 * 16));
	color = color / (16 * 16);
	light->green = (double)(color % (16 * 16));
	color = color / (16 * 16);
	light->red = (double)(color % (16 * 16));
	color = color / (16 * 16);
}

t_light		*light_parsing(int fd, t_light *light, t_camera *cam)
{
	char	*line;
	char	**tab;
	int		i;

	init_light(light);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
			break;
		if (!(tab = ft_strsplit(line, ':')) || tab[2] != NULL)
			ft_error("error parse word\n");
		if (ft_strcmp(tab[0], "\tposition.x") == 0)
			light->pos[0] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0], "\tposition.y") == 0)
			light->pos[1] = ft_atoi_double(tab[1]);	
		else if (ft_strcmp(tab[0], "\tposition.z") == 0)
			light->pos[2] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0], "\tangle.x") == 0)
			light->light_angle[0] = (ft_atoi_double(tab[1]) * M_PI ) / 180.0;
		else if (ft_strcmp(tab[0], "\tangle.y") == 0)
			light->light_angle[1] = (ft_atoi_double(tab[1]) * M_PI ) / 180.0;
		else if (ft_strcmp(tab[0], "\tangle.z") == 0)
			light->light_angle[2] = (ft_atoi_double(tab[1]) * M_PI ) / 180.0;
		else if (ft_strcmp(tab[0], "\taperture") == 0)
			light->aperture = cos((ft_atoi_double(tab[1]) * M_PI ) / 180.0);
		else if (ft_strcmp(tab[0], "\tcolor") == 0)
			light->color = ft_atoi_hexa(tab[1]);
		else if (ft_strcmp(tab[0], "\tpower") == 0)
			light->power = ft_atoi_double(tab[1]);
		else if ((ft_strcmp(tab[0], "\tdiffuse_color"))
				&& (ft_strcmp(tab[0], "\tspecular"))
				&& (ft_strcmp(tab[0], "\tambient"))
				&& (ft_strcmp(tab[0], "\treflective")))
		{
			ft_free_parse(tab, line);
			ft_error("parse light error\n");
		}
		ft_free_parse(tab, line);
	}
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
	return (light);
}
