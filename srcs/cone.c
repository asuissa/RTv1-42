/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:36:56 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/14 18:01:34 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	init_cone(t_cone *cone)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		cone->origin[i] = 0;
		cone->vector[i] = 0;
		cone->rotation[i] = 0;
	}
	norm_vector(cone->vector);
	cone->aperture = (25 * M_PI) / 180;
	cone->attributes.shininess = 100;
}

t_cone	*cone_parsing(int fd, t_camera *cam)
{
	t_cone		*cone;
	char		*line;
	char		**tab;
	int			i;

	cone = (t_cone*)malloc(sizeof(t_cone));
	init_cone(cone);
	while (get_next_line(fd, &line) > 0)
	{
		printf("line => %s\n", line);
		if (line[0] == '\0')
			break;
		if (!(tab = ft_strsplit(line, ':')) || tab[2] != NULL)
			ft_error("error parse word\n");
		if (ft_strcmp(tab[0],"\tposition.x") == 0)
			cone->origin[0] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tposition.y") == 0)
			cone->origin[1] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tposition.z") == 0)
			cone->origin[2] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tvector.x") == 0)
			cone->vector[0] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tvector.y") == 0)
			cone->vector[1] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tvector.z") == 0)
			cone->vector[2] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\taperture") == 0)
			cone->aperture = (ft_atoi_double(tab[1]) * M_PI) / 180;
		else if (ft_strcmp(tab[0],"\tcolor") == 0)
			cone->attributes.color = ft_atoi_hexa(tab[1]);
		else if (ft_strcmp(tab[0],"\tambient coeff") == 0)
			cone->attributes.ambient_coeff = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tdiffuse coeff") == 0)
			cone->attributes.diffuse_coeff = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tspecular coeff") == 0)
			cone->attributes.specular_coeff = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tshininess") == 0)
			cone->attributes.shininess = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\ttranslation.x") == 0)
			cone->origin[0] += ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\ttranslation.y") == 0)
			cone->origin[1] += ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\ttranslation.z") == 0)
			cone->origin[2] += ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\trotation.x") == 0)
			cone->rotation[0] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
		else if (ft_strcmp(tab[0],"\trotation.y") == 0)
			cone->rotation[1] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
		else if (ft_strcmp(tab[0],"\trotation.z") == 0)
			cone->rotation[2] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
		else
		{
		//	ft_free_parse(tab, line);
			ft_error("parse cone error");
		}
	//	ft_free_parse(tab, line);
	}
	rotate(cone->vector, cone->rotation);
	i = -1;
	while (++i < 3)
	{
		cone->origin_relative[i] = cone->origin[i];
		cone->vector_relative[i] = cone->vector[i];
	}
	translate(cone->origin_relative, cam->cam_pos);
	rotate(cone->origin_relative, cam->cam_angle);
	rotate(cone->vector_relative, cam->cam_angle);
	norm_vector(cone->vector_relative);
	return (cone);
}
