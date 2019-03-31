/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 06:45:28 by ymekraou          #+#    #+#             */
/*   Updated: 2019/03/10 18:54:42 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_cylender(t_cylender *cylender)
{
	cylender->origin[0] = 0;
	cylender->origin[1] = 0.5;
	cylender->origin[2] = 1;
	cylender->line_vector[0] = 0;
	cylender->line_vector[1] = 0;
	cylender->line_vector[2] = 1;
	norm_vector(cylender->line_vector);
	cylender->radius = 0.1;
	cylender->color = 0x00FFFFFF;
	cylender->code = 4;
}

t_cylender	*cylender_parsing(int fd)
{
	t_cylender	*cylender;
	char		*line;
	char		**tab;

	cylender = (t_cylender*)malloc(sizeof(t_cylender));
	init_cylender(cylender);
	while (get_next_line(fd, &line) > 0)
	{
		printf("line => %s\n", line);
		if (line[0] == '\0')
			break;
		tab = ft_strsplit(line, ':');
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
			cylender->radius = (ft_atoi_double(tab[1]) * M_PI) / 180;
		else if (ft_strcmp(tab[0],"\tcolor") == 0)
			cylender->color = ft_atoi_hexa(tab[1]);
		free(tab[0]);
		free(tab[1]);
		free(tab);
		free(line);
	}
	norm_vector(cylender->line_vector);
	return (cylender);
}
