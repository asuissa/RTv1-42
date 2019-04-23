/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 06:02:20 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/23 18:39:13 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	init_cam(t_camera *cam)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		cam->cam_pos[i] = 0;
		cam->cam_pos_relative[i] = 0;
		cam->cam_angle[i] = 0;
	}
	cam->vp_center[0] = 0;
	cam->vp_center[1] = 0;
	cam->vp_center[2] = 1;
	cam->vf_angle = ((90.0 / 2.0) * M_PI) / 180.0;
	cam->vp_width = 0.5;
	cam->pixel_size = (cam->vp_width * 2.0) / (double)(SCREEN_WIDTH);
	cam->vp_height = cam->pixel_size * (double)(SCREEN_HEIGHT);
}

void	valid_file(int fd)
{
	char	*line;

	if (get_next_line(fd, &line) <= 0)
		invalid_file_error(fd);
	if ((ft_strcmp(line, "amera:")))
	{
		free(line);
		ft_error("Camera must be defined at the beginning of the file.\n");
	}
	free(line);
}

int		camera_position_parsing(char *line, t_camera *cam)
{
	char	**tab;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\tposition.x") == 0)
		cam->cam_pos[0] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tposition.y") == 0)
		cam->cam_pos[1] = ft_atoi_double(tab[1]);
	else if (ft_strcmp(tab[0], "\tposition.z") == 0)
		cam->cam_pos[2] = ft_atoi_double(tab[1]);
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

int		camera_angle_parsing(char *line, t_camera *cam)
{
	char	**tab;

	if (!(tab = parse_word(line)))
		return (0);
	if (ft_strcmp(tab[0], "\tangle.x") == 0)
		cam->cam_angle[0] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else if (ft_strcmp(tab[0], "\tangle.y") == 0)
		cam->cam_angle[1] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else if (ft_strcmp(tab[0], "\tangle.z") == 0)
		cam->cam_angle[2] = (ft_atoi_double(tab[1]) * M_PI) / 180.0;
	else
	{
		free_split_tab(tab);
		return (0);
	}
	free_split_tab(tab);
	return (1);
}

void	camera_parsing(int fd, t_camera *cam)
{
	char	*line;

	valid_file(fd);
	init_cam(cam);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '\0')
		{
			free(line);
			break ;
		}
		else if (!(camera_position_parsing(line, cam))
				&& !(camera_angle_parsing(line, cam)))
		{
			free(line);
			invalid_file_error(fd);
		}
		else
			free(line);
	}
}
