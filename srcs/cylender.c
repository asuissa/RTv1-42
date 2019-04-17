/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 06:45:28 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/17 17:56:58 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_cylender		*init_cylender(void)
{
	int			i;
	t_cylender	*cylender;

	if (!(cylender = (t_cylender*)malloc(sizeof(t_cylender))))
		return (NULL);
	i = -1;
	while (++i < 3)
	{
		cylender->origin[i] = 0;
		cylender->line_vector[i] = 0;
		cylender->rotation[i] = 0;
	}
	norm_vector(cylender->line_vector);
	cylender->radius = 1;
	cylender->attributes.shininess = 100;
	return (cylender);
}

int				check_cylender(t_cylender *cylender)
{
	if (cylender->radius > 0)
		return (0);
	if (check_attributes(&(cylender->attributes)) == 0)
		return (0);
	return (1);
}

void			cylender_rotation_translation(t_cylender *cylender,
					t_camera *cam)
{
	int		i;

	rotate(cylender->line_vector, cylender->rotation);
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
}

t_cylender		*cylender_parsing(int fd, t_camera *cam)
{
	t_cylender	*cylender;
	char		*line;

	if (!(cylender = init_cylender()))
		return (NULL);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			break ;
		}
		else if (!(cylender_parse(cylender, line)))
		{
			free(line);
			return (NULL);
		}
		else
			free(line);
	}
	if (!(check_cylender(cylender)))
		return (NULL);
	cylender_rotation_translation(cylender, cam);
	return (cylender);
}
