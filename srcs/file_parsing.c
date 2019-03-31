/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 07:21:00 by ymekraou          #+#    #+#             */
/*   Updated: 2019/03/17 00:05:47 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"


t_light		*get_last_light(t_light **head)
{
	t_light	*tmp;


	if (!(*head))
	{

		*head = (t_light*)malloc(sizeof(t_light));

		(*head)->next = NULL;
		return (*head);
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_light*)malloc(sizeof(t_light));
		tmp->next->next = NULL;
		return (tmp->next);
	}
}

t_elem		*get_last_elem(t_elem **head)
{
	t_elem	*tmp;

	if (!(*head))
	{
		*head = (t_elem*)malloc(sizeof(t_elem));
		(*head)->next = NULL;
		return (*head);
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (t_elem*)malloc(sizeof(t_elem));
		tmp->next->next = NULL;
		return (tmp->next);
	}
}

void		file_parsing(char *file, t_env *env)
{
	t_elem		*new_elem;
	t_light		*new_light;
	int			fd;
	char		*line;

	if ((fd = open(file, O_RDONLY)) <= 2)
		printf("c la merd!\n");
	env->elem = NULL;
	env->light = NULL;	
	while (get_next_line(fd, &line) > 0)
	{
		printf("->%s\n", line);
		if (ft_strcmp("camera:", line)  == 0)
		{	
			camera_parsing(fd, &(env->cam));
			printf("cam done\n");
		}
		else if (ft_strcmp("light:", line)  == 0)
		{
			new_light = get_last_light(&(env->light));

			light_parsing(fd, new_light);
			printf("light done\n");
		}
		else if (ft_strcmp("sphere:", line)  == 0)
		{
			new_elem = get_last_elem(&(env->elem));
			new_elem->object = sphere_parsing(fd);
			new_elem->hit_funct = &hit_sphere;
			printf("sphere done\n");
		}
		else if (ft_strcmp("plan:", line)  == 0)
		{
			new_elem = get_last_elem(&(env->elem));
			new_elem->object = plan_parsing(fd);
			new_elem->hit_funct = &hit_plan;
			printf("plan done\n");
		}
		else if (ft_strcmp("cone:", line)  == 0)
		{
			new_elem = get_last_elem(&(env->elem));
			new_elem->object = cone_parsing(fd);
			new_elem->hit_funct = &hit_cone;
			printf("cone done\n");
		}
		else if (ft_strcmp("cylender:", line)  == 0)
		{
			new_elem = get_last_elem(&(env->elem));
			new_elem->object = cylender_parsing(fd);
			new_elem->hit_funct = &hit_cylender;
			printf("cylender done\n");
		}

		ft_strdel(&line);
	}
	close(fd);
}
