/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 06:02:20 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/05 00:09:21 by asuissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_free_parse(char **tab, char *line)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	free(line);
}

void		ft_error(char *msg)
{
	ft_putstr(msg);
	exit(1);
}

void		init_cam(t_camera *cam)
{
	cam->cam_pos_relative[0] = 0;
	cam->cam_pos_relative[1] = 0;
	cam->cam_pos_relative[2] = 0;
	cam->vp_center[0] = 0;
	cam->vp_center[1] = 0;
	cam->vp_center[2] = 1;
	cam->vf_angle = (90.0 * M_PI) / 180.0;
	cam->vp_dim = (double)(fabs(atan(cam->vf_angle / 2.0)));
	cam->pas = cam->vp_dim / ((double)(SCREEN_WIDTH) / 2.0);
}

void		camera_parsing(int fd, t_camera *cam)
{
	char	*line;
	char	**tab;

	init_cam(cam);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
			break ;
		if (!(tab = ft_strsplit(line, ':')))
				ft_error("Parsing error\n");
		if (ft_strcmp(tab[0], "\tposition.x") == 0)
			cam->cam_pos[0] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0], "\tposition.y") == 0)
			cam->cam_pos[1] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0], "\tposition.z") == 0)
			cam->cam_pos[2] = ft_atoi_double(tab[1]);
		else if (ft_strcmp(tab[0], "\tangle.x") == 0)
			cam->cam_angle[0] = (ft_atoi_double(tab[1]) * M_PI) / 180;
		else if (ft_strcmp(tab[0], "\tangle.y") == 0)
			cam->cam_angle[1] = (ft_atoi_double(tab[1]) * M_PI) / 180;
		else if (ft_strcmp(tab[0], "\tangle.z") == 0)
			cam->cam_angle[2] = (ft_atoi_double(tab[1]) * M_PI) / 180;
		else
		{
			ft_free_parse(tab, line);
			ft_error("parse cam error\n");
		}
		ft_free_parse(tab, line);
	}
}
