/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 06:14:48 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/05 02:12:14 by asuissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	init_sphere(t_sphere *sphere)
{
	sphere->type = "sphere";
	sphere->center[0] = 0;
	sphere->center[1] = 0;
	sphere->center[2] = 5;
	sphere->radius = 1;
	sphere->color = 0x0000FF00;
	sphere->code = 1;	
}

t_sphere	*sphere_parsing(int fd, t_camera *cam)
{
	t_sphere	*sphere;
	char		*line;
	char		**tab;

	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	init_sphere(sphere);
	while (get_next_line(fd, &line) > 0)
	{
		printf("line => %s\n", line);
		if (line[0] == '\0')
			break;
		if (!(tab = ft_strsplit(line, ':')) || tab[2] != NULL)
			ft_error("Error parse word\n");
		if (ft_strcmp(tab[0],"\tposition.x") == 0)
		{
			sphere->center[0] = ft_atoi_double(tab[1]);
			sphere->center_relative[0] = sphere->center[0];
		}
		else if (ft_strcmp(tab[0],"\tposition.y") == 0)
		{
			sphere->center[1] = ft_atoi_double(tab[1]);
			sphere->center_relative[1] = sphere->center[1];
		}
		else if (ft_strcmp(tab[0],"\tposition.z") == 0)
		{
			sphere->center[2] = ft_atoi_double(tab[1]);
			sphere->center_relative[2] = sphere->center[2];
		}
		else if (ft_strcmp(tab[0],"\tradius") == 0)
			sphere->radius = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tcolor") == 0)
			sphere->color = ft_atoi_hexa(tab[1]);
		else
		{
			ft_free_parse(tab, line);
			ft_error("parse cam error\n");
		}
		ft_free_parse(tab, line);
	}
	translate(sphere->center_relative, cam->cam_pos);
	rotate(sphere->center_relative, cam->cam_angle);
	return (sphere);
}
