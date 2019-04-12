/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 06:14:48 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/12 07:46:12 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	init_sphere(t_sphere *sphere)
{
	int i;

	sphere->type = "sphere";
	i = -1;
	while ( ++i < 3)
	{
		sphere->center[i] = 0;
		sphere->rotation[i] = 0;
	}
	sphere->radius = 1;	
}

t_sphere	*sphere_parsing(int fd, t_camera *cam)
{
	t_sphere	*sphere;
	char		*line;
	char		**tab;
	int			i;

	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	init_sphere(sphere);
	while (get_next_line(fd, &line) > 0)
	{
		printf("line => %s\n", line);
		if (line[0] == '\0')
			break;
		if (!(tab = ft_strsplit(line, ':')) || tab[2] != NULL)
			ft_error("error parse word\n");
		if (ft_strcmp(tab[0],"\tposition.x") == 0)
			sphere->center[0] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tposition.y") == 0)
			sphere->center[1] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tposition.z") == 0)
			sphere->center[2] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tradius") == 0)
			sphere->radius = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tcolor") == 0)
			sphere->attributes.color = ft_atoi_hexa(tab[1]);
		else if (ft_strcmp(tab[0],"\tambient coeff") == 0)
			sphere->attributes.ambient_coeff = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tdiffuse coeff") == 0)
			sphere->attributes.diffuse_coeff = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tspecular coeff") == 0)
			sphere->attributes.specular_coeff = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tshininess") == 0)
			sphere->attributes.shininess = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\ttranslation.x") == 0)
			sphere->center[0] += ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\ttranslation.y") == 0)
			sphere->center[1] += ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\ttranslation.z") == 0)
			sphere->center[2] += ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\trotation.x") == 0)
			sphere->rotation[0] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
		else if (ft_strcmp(tab[0],"\trotation.y") == 0)
			sphere->rotation[1] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
		else if (ft_strcmp(tab[0],"\trotation.z") == 0)
			sphere->rotation[2] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
		else
		{
			ft_free_parse(tab, line);
			ft_error("parse cam error\n");
		}
		ft_free_parse(tab, line);
	}
	i = -1;
	while (++i < 3)
		sphere->center_relative[i] = sphere->center[i];
	translate(sphere->center_relative, cam->cam_pos);
	rotate(sphere->center_relative, cam->cam_angle);
	return (sphere);
}
