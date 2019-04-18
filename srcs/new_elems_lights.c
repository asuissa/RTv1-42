/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_elems_lights.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:01:59 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/18 12:28:44 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		new_light(t_env *env, char *line, int fd)
{
	t_light		*new_light;

	if (!(new_light = get_last_light(&(env->light))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a light");
	}
	if (!(new_light = light_parsing(fd, new_light, &(env->cam))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a light");
	}
	printf("light done\n");
}

void		new_sphere(t_env *env, char *line, int fd)
{
	t_elem	*new_elem;

	if (!(new_elem = get_last_elem(&(env->elem))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a sphere");
	}
	if (!(new_elem->object = sphere_parsing(fd, &(env->cam))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a sphere");
	}
	new_elem->hit_funct = &hit_sphere;
	new_elem->update_funct = &update_sphere;
	printf("sphere done\n");
}

void		new_plan(t_env *env, char *line, int fd)
{
	t_elem	*new_elem;

	if (!(new_elem = get_last_elem(&(env->elem))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a plan");
	}
	if (!(new_elem->object = plan_parsing(fd, &(env->cam))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a plan");
	}
	new_elem->hit_funct = &hit_plan;
	new_elem->update_funct = &update_plan;
	printf("plan done\n");
}

void		new_cone(t_env *env, char *line, int fd)
{
	t_elem	*new_elem;

	if (!(new_elem = get_last_elem(&(env->elem))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a cone");
	}
	if (!(new_elem->object = cone_parsing(fd, &(env->cam))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a cone");
	}
	new_elem->hit_funct = &hit_cone;
	new_elem->update_funct = &update_cone;
	printf("cone done\n");
}

void		new_cylender(t_env *env, char *line, int fd)
{
	t_elem	*new_elem;

	if (!(new_elem = get_last_elem(&(env->elem))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a cylender");
	}
	if (!(new_elem->object = cylender_parsing(fd, &(env->cam))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a cylender");
	}
	new_elem->hit_funct = &hit_cylender;
	new_elem->update_funct = &update_cylender;
	printf("cylender done\n");
}
