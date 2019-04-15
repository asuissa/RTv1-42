/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 06:45:28 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/15 16:35:30 by asuissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		init_cylender(t_cylender *cylender)
{
	int	i;

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
}

t_cylender	*cylender_parsing(int fd, t_camera *cam)
{
	t_cylender	*cylender;
	char		*line;

	cylender = (t_cylender*)malloc(sizeof(t_cylender));
	init_cylender(cylender);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			break ; //verifier free
		}
		else if (!cylender_parse_1(cone, line) && !cylender_parse_2(cone, line)
				&& !cylender_parse_coeff(cone, line))
		{
			free(line);
			return (NULL);
		}
		else
			free(line);
	}
	if (!cylender_rot_trans(cylender, cam))
		return (NULL);
	return (cylender);
}
