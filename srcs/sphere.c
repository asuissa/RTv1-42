/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 06:14:48 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/17 18:09:54 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_sphere	*init_sphere(void)
{
	t_sphere	*sphere;
	int			i;

	if (!(sphere = (t_sphere*)malloc(sizeof(t_sphere))))
		return (NULL);
	i = -1;
	while (++i < 3)
	{
		sphere->center[i] = 0;
		sphere->rotation[i] = 0;
	}
	sphere->radius = 1;
	return (sphere);
}

int			check_sphere(t_sphere *sphere)
{
	if (check_attributes(&(sphere->attributes)) == 0)
		return (0);
	if (sphere->radius <= 0)
		return (0);
	return (1);
}

void		sphere_rotation_translation(t_sphere *sphere, t_camera *cam)
{
	int		i;

	i = -1;
	while (++i < 3)
		sphere->center_relative[i] = sphere->center[i];
	translate(sphere->center_relative, cam->cam_pos);
	rotate(sphere->center_relative, cam->cam_angle);
}

t_sphere	*sphere_parsing(int fd, t_camera *cam)
{
	t_sphere	*sphere;
	char		*line;

	if (!(sphere = init_sphere()))
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			break ;
		}
		else if (!(sphere_parse(sphere, line)))
		{
			free(line);
			return (NULL);
		}
		else
			free(line);
	}
	if (!(check_sphere(sphere)))
		return (NULL);
	sphere_rotation_translation(sphere, cam);
	return (sphere);
}
