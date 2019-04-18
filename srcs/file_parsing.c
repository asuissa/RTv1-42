/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 07:21:00 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/18 14:18:12 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		check_attributes(t_attributes *attributes)
{
	if (attributes->color > 0xFFFFFF || attributes->color < 0)
		return (0);
	if (attributes->shininess > 1250.0 || attributes->shininess < 0)
		return (0);
	if (attributes->ambient_coeff > 1 || attributes->ambient_coeff < 0)
		return (0);
	if (attributes->diffuse_coeff > 1 || attributes->diffuse_coeff < 0)
		return (0);
	if (attributes->specular_coeff > 1 || attributes->specular_coeff < 0)
		return (0);
	if (attributes->diffuse_coeff
			+ attributes->ambient_coeff + attributes->specular_coeff > 1)
		return (0);
	return (1);
}

int		open_file(char *file)
{
	int		fd;
	char	c[1];

	if ((fd = open(file, O_RDONLY)) <= 2)
		ft_error("File couldn't be opened.\n");
	if ((read(fd, c, 1)) > 0 && c[0] != 'c')
	{
		close(fd);
		ft_error("Camera is not defined correctly.\n");
	}
	return (fd);
}

void	file_parsing(char *file, t_env *env)
{
	int			fd;
	char		*line;

	fd = open_file(file);
	camera_parsing(fd, &(env->cam));
	env->elem = NULL;
	env->light = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp("light:", line) == 0)
			new_light(env, line, fd);
		else if (ft_strcmp("sphere:", line) == 0)
			new_sphere(env, line, fd);
		else if (ft_strcmp("plan:", line) == 0)
			new_plan(env, line, fd);
		else if (ft_strcmp("cone:", line) == 0)
			new_cone(env, line, fd);
		else if (ft_strcmp("cylender:", line) == 0)
			new_cylender(env, line, fd);
		else
			invalid_line_error(env, line, fd);
		ft_strdel(&line);
	}
	close(fd);
}
