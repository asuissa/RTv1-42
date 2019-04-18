/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 20:27:25 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/18 16:39:58 by ymekraou         ###   ########.fr       */
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

int			check_light(t_light *light)
{
	if (light->power < 0.0)
		return (0);
	if (light->color > 0xFFFFFF || light->color < 0)
		return (0);
	if (light->aperture > 180.0 || light->aperture < 0)
		return (0);
	else
		light->aperture = cos((light->aperture * M_PI) / 180.0);
	return (1);
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

void		light_rotation_translation(t_light *light, t_camera *cam)
{
	int		i;

	rotate(light->direction, light->light_angle);
	i = -1;
	while (++i < 3)
	{
		light->pos_relative[i] = light->pos[i];
		light->direction_relative[i] = light->direction[i];
	}
	translate(light->pos_relative, cam->cam_pos);
	rotate(light->pos_relative, cam->cam_angle);
	rotate(light->direction_relative, cam->cam_angle);
	norm_vector(light->direction_relative);
	get_rgb_light(light);
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
			break ;
		}
		else if (!(light_parse(light, line)))
		{
			free(line);
			return (NULL);
		}
		else
			free(line);
	}
	if (!(check_light(light)))
		return (NULL);
	light_rotation_translation(light, cam);
	return (light);
}
