/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 20:27:25 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/15 17:49:40 by asuissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		init_light(t_light *light)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		light->pos[i] = 0;
		light->light_angle[i] = 0;
	}
	light->direction[0] = 0;
	light->direction[1] = 0;
	light->direction[2] = 1;
	light->color = 0xFFFFFF;
	light->power = 10000.0;
	light->next = NULL;
	light->aperture = cos(M_PI);
}

void		get_rgb_light(t_light *light)
{
	int		color;

	color = light->color;
	light->blue = (double)(color % (16 * 16));
	color = color / (16 * 16);
	light->green = (double)(color % (16 * 16));
	color = color / (16 * 16);
	light->red = (double)(color % (16 * 16));
	color = color / (16 * 16);
}

t_light		*light_parsing(int fd, t_light *light, t_camera *cam)
{
	char	*line;

	init_light(light);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			break ; //verifier free
		}
		else if (!light_parse_1(light, line) && !light_parse_2(light, line))
		{
			free(line);
			return (NULL);
		}
		else
			free(line);
	}
	light_rot_trans(light, cam);
	return (light);
}
