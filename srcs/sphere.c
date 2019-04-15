/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 06:14:48 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/15 19:20:47 by asuissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		init_sphere(t_sphere *sphere)
{
	int i;

	sphere->type = "sphere";
	i = -1;
	while (++i < 3)
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

	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	init_sphere(sphere);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			break ; //verifier free
		}
		else if (!sphere_parse_1(sphere, line) && !sphere_parse_2(sphere, line)
				&& !sphere_parse_coeff(sphere, line))
		{
			free(line);
			return (NULL);
		}
		else
			free(line);
	}
	sphere_rot_trans(sphere, cam);
	return (sphere);
}
