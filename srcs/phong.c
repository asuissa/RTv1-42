/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:05:17 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/13 12:12:11 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	compute_reflected_ray(double reflected[3], double point_normal[3], double light_vector[3])
{
	int		i;
	double	stock;

	stock = dot_product(light_vector, point_normal);
	i = -1;
	while (++i < 3)	
		reflected[i] = (2 * point_normal[i] * stock) - light_vector[i];
	norm_vector(reflected);
}

void	normalize_color(t_hit *hit_point, double res[3])
{
	int		i;

	i = -1;
	while (++i < 3)
	{
		if (res[i] > 255.0)
			res[i] = 255.0;
	}
	hit_point->red = round(res[0]);
	hit_point->green = round(res[1]);
	hit_point->blue = round(res[2]);
}

void	light_contribution(double res[3], double cam_vector[3], t_env *env, t_hit *hit_point)
{
	int		i;
	double	light_vector[3];
	double	reflected[3];
	double	stock;
	t_light	*tmp;

	tmp = env->light;
	while (tmp)
	{
		i = -1;
		while(++i < 3)
			light_vector[i] = (tmp->pos_relative[i] - hit_point->coord[i]);
		norm_vector(light_vector);
		if (shading(tmp, light_vector, env->elem, hit_point) > 0)
			{
				add_diffuse(res, light_vector, tmp, hit_point);
				compute_reflected_ray(reflected, hit_point->normal, light_vector);
				if ((stock = dot_product(cam_vector, reflected)) > 0)
					add_specular(res, stock, tmp, hit_point);
			}
		tmp = tmp->next;
	}
}

void	compute_color(t_hit *hit_point, double cam_vector[3], t_env *env)
{
	double	res[3];
	int i;

	get_rgb_hit_point(hit_point);
	i = -1;
	while(++i < 3)
		cam_vector[i] *= (-1.0);
	add_ambient(res, hit_point);
	light_contribution(res, cam_vector, env, hit_point);
	normalize_color(hit_point, res);
}
