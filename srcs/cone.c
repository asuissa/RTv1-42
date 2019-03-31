/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:36:56 by ymekraou          #+#    #+#             */
/*   Updated: 2019/03/10 18:54:10 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_cone(t_cone *cone)
{
	cone->origin[0] = 0;
	cone->origin[1] = 0;
	cone->origin[2] = 2;
	cone->vector[0] = 0;
	cone->vector[1] = 1;
	cone->vector[2] = 0;
	norm_vector(cone->vector);
	cone->aperture = (25 * M_PI) / 180;
	cone->color = 0x00FF0000;
	cone->code = 3;
}

t_cone	*cone_parsing(int fd)
{
	t_cone		*cone;
	char		*line;
	char		**tab;

	cone = (t_cone*)malloc(sizeof(t_cone));
	init_cone(cone);
	while (get_next_line(fd, &line) > 0)
	{
		printf("line => %s\n", line);
		if (line[0] == '\0')
			break;
		tab = ft_strsplit(line, ':');
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
			cone->color = ft_atoi_hexa(tab[1]);
		free(tab[0]);
		free(tab[1]);
		free(tab);
		free(line);
	}
	norm_vector(cone->vector);
	return (cone);
}
