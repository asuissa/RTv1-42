/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:36:56 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/15 16:36:29 by asuissa          ###   ########.fr       */
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

	cone = (t_cone*)malloc(sizeof(t_cone));
	init_cone(cone);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			break ; //verifier free
		}
		else if (!cone_parse_1(cone, line) && !cone_parse_2(cone, line)
				&& !cone_parse_3(cone, line) && !cone_parse_coeff(cone, line))
		{
			free(line);
			return (NULL);
		}
		else
			free(line);
	}
	cone_rot_trans(cone, cam);
	return (cone);
}
