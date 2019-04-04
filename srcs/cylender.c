/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 06:45:28 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/03 08:07:52 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	init_cylender(t_cylender *cylender)
{
	cylender->origin[0] = 0;
	cylender->origin[1] = 0;
	cylender->origin[2] = 0;
	cylender->line_vector[0] = 0;
	cylender->line_vector[1] = 0;
	cylender->line_vector[2] = 0;
	norm_vector(cylender->line_vector);
	cylender->radius = 1;
	cylender->color = 0x00FFFFFF;
	cylender->code = 4;
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
			cylender->radius = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tcolor") == 0)
			cylender->color = ft_atoi_hexa(tab[1]);
		free(tab[0]);
		free(tab[1]);
		free(tab);
		free(line);
	}
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
