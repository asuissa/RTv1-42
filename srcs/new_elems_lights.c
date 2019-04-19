/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_elems_lights.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:01:59 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/18 18:19:34 by ymekraou         ###   ########.fr       */
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
		ft_error("an error occured while parsing a light.\n");
	}
	if (!(new_light = light_parsing(fd, new_light, &(env->cam))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a light.\n");
	}
}

void		new_sphere(t_env *env, char *line, int fd)
{
	t_elem	*new_elem;

	if (!(new_elem = get_last_elem(&(env->elem))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a sphere.\n");
	}
	if (!(new_elem->object = sphere_parsing(fd, &(env->cam))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a sphere.\n");
	}
	new_elem->hit_funct = &hit_sphere;
	new_elem->update_funct = &update_sphere;
}

void		new_plan(t_env *env, char *line, int fd)
{
	t_elem	*new_elem;

	if (!(new_elem = get_last_elem(&(env->elem))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a plan.\n");
	}
	if (!(new_elem->object = plan_parsing(fd, &(env->cam))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a plan.\n");
	}
	new_elem->hit_funct = &hit_plan;
	new_elem->update_funct = &update_plan;
}

void		new_cone(t_env *env, char *line, int fd)
{
	t_elem	*new_elem;

	if (!(new_elem = get_last_elem(&(env->elem))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a cone.\n");
	}
	if (!(new_elem->object = cone_parsing(fd, &(env->cam))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a cone.\n");
	}
	new_elem->hit_funct = &hit_cone;
	new_elem->update_funct = &update_cone;
}

void		new_cylender(t_env *env, char *line, int fd)
{
	t_elem	*new_elem;

	if (!(new_elem = get_last_elem(&(env->elem))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a cylender.\n");
	}
	if (!(new_elem->object = cylender_parsing(fd, &(env->cam))))
	{
		clean_lists(env->light, env->elem);
		free(line);
		close(fd);
		ft_error("an error occured while parsing a cylender.\n");
	}
	new_elem->hit_funct = &hit_cylender;
	new_elem->update_funct = &update_cylender;
}
