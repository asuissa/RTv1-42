/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 01:36:56 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/16 19:14:53 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_cone	*init_cone(void)
{
	int		i;
	t_cone	*cone;

	if (!(cone = (t_cone*)malloc(sizeof(t_cone))))
		return (NULL);
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
	return (cone);
}

int		check_cone(t_cone *cone)
{
	if (!((cone->aperture < (90.0 * M_PI / 180.0))
		&& (cone->aperture > 0)))
		return (0);
	if (check_attributes(&(cone->attributes)) == 0)
		return (0);
	return (1);
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

	if (!(cone = init_cone()))
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			break ;
		}
		else if (!(cone_parse(cone, line)))
		{
			free(line);
			return (NULL);
		}
		else
			free(line);
	}
	if (!(check_cone(cone)))
		free(cone);
	else
		cone_rotation_translation(cone, cam);
	return (cone);
}
