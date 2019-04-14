/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 06:45:28 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/14 18:02:18 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	init_cylender(t_cylender *cylender)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		cylender->origin[i] = 0;
		cylender->line_vector[i] = 0;
		cylender->rotation[i] = 0;
	}
	norm_vector(cylender->line_vector);
	cylender->radius = 1;
	cylender->attributes.shininess = 100;
}

t_cylender	*cylender_parsing(int fd, t_camera *cam)
{
	t_cylender	*cylender;
	char		*line;
	char		**tab;
	int			i;

	cylender = (t_cylender*)malloc(sizeof(t_cylender));
	init_cylender(cylender);
	while (get_next_line(fd, &line) > 0)
	{
		printf("line => %s\n", line);
		if (line[0] == '\0')
			break;
		if(!(tab = ft_strsplit(line, ':')) || tab[2] != NULL)
			ft_error("error parse word\n");
		if (ft_strcmp(tab[0],"\tposition.x") == 0)
			cylender->origin[0] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tposition.y") == 0)
			cylender->origin[1] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tposition.z") == 0)
			cylender->origin[2] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tvector.x") == 0)
			cylender->line_vector[0] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tvector.y") == 0)
			cylender->line_vector[1] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tvector.z") == 0)
			cylender->line_vector[2] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tradius") == 0)
			cylender->radius = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tcolor") == 0)
			cylender->attributes.color = ft_atoi_hexa(tab[1]);
		else if (ft_strcmp(tab[0],"\tambient coeff") == 0)
			cylender->attributes.ambient_coeff = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tdiffuse coeff") == 0)
			cylender->attributes.diffuse_coeff = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tspecular coeff") == 0)
			cylender->attributes.specular_coeff = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tshininess") == 0)
			cylender->attributes.shininess = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\ttranslation.x") == 0)
			cylender->origin[0] += ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\ttranslation.y") == 0)
			cylender->origin[1] += ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\ttranslation.z") == 0)
			cylender->origin[2] += ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\trotation.x") == 0)
			cylender->rotation[0] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
		else if (ft_strcmp(tab[0],"\trotation.y") == 0)
			cylender->rotation[1] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
		else if (ft_strcmp(tab[0],"\trotation.z") == 0)
			cylender->rotation[2] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
		else
		{
		//	ft_free_parse(tab, line);
			ft_error("parse cylender error\n");
		}
		//ft_free_parse(tab, line);
	}
	rotate(cylender->line_vector, cylender->rotation);
	i = -1;
	while (++i < 3)
	{
		cylender->origin_relative[i] = cylender->origin[i];
		cylender->line_vector_relative[i] = cylender->line_vector[i];
	}
	translate(cylender->origin_relative, cam->cam_pos);
	rotate(cylender->origin_relative, cam->cam_angle);
	rotate(cylender->line_vector_relative, cam->cam_angle);
	norm_vector(cylender->line_vector_relative);
	return (cylender);
}
