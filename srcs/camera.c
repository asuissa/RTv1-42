/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 06:02:20 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/03 22:07:12 by asuissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_cam(t_camera *cam)
{
	cam->cam_pos[0] = 0;
	cam->cam_pos[1] = 0;
	cam->cam_pos[2] = 0;
	cam->vp_center[0] = 0;
	cam->vp_center[1] = 0;
	cam->vp_center[2] = 1;
	cam->vf_angle = (90 * M_PI) / 180;
	cam->vp_dim = atan(cam->vf_angle / 2);
}

void	camera_parsing(int fd,  t_camera *cam)
{
	char	*line;
	char	**tab;

	init_cam(cam);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
			break;
		tab = ft_strsplit(line, ':');
		if (ft_strcmp(tab[0],"\tposition.x") == 0)
			cam->cam_pos[0] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tposition.y") == 0)
			cam->cam_pos[1] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0],"\tposition.z") == 0)
			cam->cam_pos[2] = ft_atoi_double(tab[1]);
		else
		{
			printf("parse cam error\n");
			exit(1);
		}
		free(tab[0]);
		free(tab[1]);
		free(tab);
		free(line);
	}
}
