/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:36:56 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/16 15:54:57 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	init_cone(t_cone *cone)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		cone->origin[i] = 0.0;
		cone->vector[i] = 0.0;
		cone->rotation[i] = 0.0;
	}
	norm_vector(cone->vector);
	cone->aperture = (25 * M_PI) / 180.0;
	cone->attributes.shininess = 100.0;
}

void	cone_rotation_translation(t_cone *cone, t_camera *cam)
{
	int	i;

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
}

t_cone	*cone_parsing(int fd, t_camera *cam)
{
	t_cone		*cone;
	char		*line;

	if (!(cone = (t_cone*)malloc(sizeof(t_cone))))
		return (NULL);
	init_cone(cone);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			break ; //verifier free
		}
		else if (!cone_parse_basics(cone, line) && !cone_parse_movements(cone, line)
			   	&& !cone_parse_attributes(cone, line))
		{
			free(line);
			return (NULL);
		}
		else
			free(line);
	}
	cone_rotation_translation(cone, cam);
	return (cone);
}
