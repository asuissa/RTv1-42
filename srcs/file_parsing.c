/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 07:21:00 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/16 18:44:44 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			check_attributes(t_attributes *attributes)
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

t_light		*get_last_light(t_light **head)
{
	t_light	*tmp;

	if (!(*head))
	{
		if (!(*head = (t_light*)malloc(sizeof(t_light))))
			return (NULL);
		(*head)->next = NULL;
		return (*head);
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_light*)malloc(sizeof(t_light))))
			return (NULL);
		tmp->next->next = NULL;
		return (tmp->next);
	}
}

t_elem		*get_last_elem(t_elem **head)
{
	t_elem	*tmp;

	if (!(*head))
	{
		if (!(*head = (t_elem*)malloc(sizeof(t_elem))))
			return (NULL);
		(*head)->next = NULL;
		return (*head);
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_elem*)malloc(sizeof(t_elem))))
			return (NULL);
		tmp->next->next = NULL;
		return (tmp->next);
	}
}

//une fonction par partie qui retourne 0 si null
void		file_parsing(char *file, t_env *env)
{
	t_elem		*new_elem;
	t_light		*new_light;
	int			fd;
	char		*line;

	fd = invalid_read(file);
	camera_parsing(fd, &(env->cam));
	env->elem = NULL;
	env->light = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		printf("->%s\n", line);
		if (ft_strcmp("light:", line) == 0)
		{
			if (!(new_light = get_last_light(&(env->light)))
					|| !light_parsing(fd, new_light, &(env->cam)))
				invalid_line_error(fd, line);
			printf("light done\n");
		}
		else if (ft_strcmp("sphere:", line) == 0)
		{
			if (!(new_elem = get_last_elem(&(env->elem)))
					|| !(new_elem->object = sphere_parsing(fd, &(env->cam))))
				invalid_line_error(fd, line);
			new_elem->hit_funct = &hit_sphere;
			new_elem->update_funct = &update_sphere;
			printf("sphere done\n");
		}
		else if (ft_strcmp("plan:", line) == 0)
		{
			if (!(new_elem = get_last_elem(&(env->elem)))
					|| !(new_elem->object = plan_parsing(fd, &(env->cam))))
				invalid_line_error(fd, line);
			new_elem->hit_funct = &hit_plan;
			new_elem->update_funct = &update_plan;
			printf("plan done\n");
		}
		else if (ft_strcmp("cone:", line) == 0)
		{
			if (!(new_elem = get_last_elem(&(env->elem)))
					|| !(new_elem->object = cone_parsing(fd, &(env->cam))))
				invalid_line_error(fd, line);
			new_elem->hit_funct = &hit_cone;
			new_elem->update_funct = &update_cone;
			printf("cone done\n");
		}
		else if (ft_strcmp("cylender:", line) == 0)
		{
			if (!(new_elem = get_last_elem(&(env->elem)))
					|| !(new_elem->object = cylender_parsing(fd, &(env->cam))))
				invalid_line_error(fd, line);
			new_elem->hit_funct = &hit_cylender;
			new_elem->update_funct = &update_cylender;
			printf("cylender done\n");
		}
		else
			invalid_line_error(fd, line);
		ft_strdel(&line);
	}
	close(fd);
}
