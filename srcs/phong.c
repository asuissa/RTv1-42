/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 23:41:59 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/10 03:58:50 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	get_rgb_hit_point(t_hit *hit_point)
{
	int		color;

	color = hit_point->color;

	hit_point->blue = (double)(color % (16 * 16));
	color = color / (16 * 16);
	hit_point->green = (double)(color % (16 * 16));
	color = color / (16 * 16);
	hit_point->red = (double)(color % (16 * 16));
	color = color / (16 * 16);
}

int		not_shaded(t_light *light, double light_ray[3], t_elem *elem, t_hit *hit_point)
{
	t_hit	shade_hit;
	t_elem	*tmp;
	double	vector[3];
	double	bias[3];
	double	reversed_light[3];
	int		i;

	init_hit_point(&shade_hit);
	i = -1;
	while (++i < 3)
	{
		bias[i] = (hit_point->coord[i] + 0.00001 * hit_point->normal[i]); 
		vector[i] = bias[i] - light->pos_relative[i];
		shade_hit.coord[i] = bias[i];
		reversed_light[i] = -light_ray[i];
	}
	norm_vector(vector);
	if (dot_product(reversed_light, light->direction_relative) < light->aperture)
		return (0);
	tmp = elem;
	while (tmp)
	{
		tmp->hit_funct(vector, light->pos_relative, tmp->object, &shade_hit);
		if (point_distance(bias, light->pos_relative) > point_distance(shade_hit.coord, light->pos_relative))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

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

double	compute_light_intensity(double point[3], double light[3], double power)
{
	double		light_intensity;

	light_intensity =  1 - (point_distance(point, light) / power);
	if (light_intensity < 0)
		return (0);
	return (light_intensity);
}

void	add_diffuse(double res[3], double light_vector[3], t_light *light, t_hit *hit_point)
{
	double		light_intensity;
	double		diffuse_att;
	double		light_red;
	double		light_green;
	double		light_blue;

	diffuse_att = dot_product(light_vector, hit_point->normal);
	if (diffuse_att > 0)
	{
		light_intensity =  compute_light_intensity(hit_point->coord, light->pos_relative, light->power);
		light_red = diffuse_att * light->red * light_intensity;
		light_green = diffuse_att * light->green * light_intensity;	
		light_blue = diffuse_att * light->blue * light_intensity;
		res[0] += light_red * (hit_point->red / 255.0) * hit_point->diffuse_coeff;
		res[1] += light_green * (hit_point->green / 255.0) * hit_point->diffuse_coeff;
		res[2] += light_blue * (hit_point->blue / 255.0) * hit_point->diffuse_coeff;
	}
}

void	add_specular(double res[3], double angle, t_light *light, t_hit *hit_point)
{
	double		light_intensity;
	double		specular_att;

	specular_att = pow(angle, hit_point->shininess);
	light_intensity = compute_light_intensity(hit_point->coord, light->pos_relative, light->power);
	res[0] += (hit_point->specular_coeff * (double)(light->red) * specular_att * light_intensity);
	res[1] += (hit_point->specular_coeff * (double)(light->green) * specular_att * light_intensity);
	res[2] += (hit_point->specular_coeff * (double)(light->blue) * specular_att * light_intensity);
}

void	add_ambient(double res[3], t_hit *hit_point)
{
	if (hit_point->red <= 255.0)
		res[0] = hit_point->ambient_coeff * hit_point->red;
	else
		res[0] = hit_point->ambient_coeff * 255.0;
	if (hit_point->green <= 255.0)
		res[1] = hit_point->ambient_coeff * hit_point->green;
	else
		res[1] = hit_point->ambient_coeff * 255.0;
	if (hit_point->blue <= 255.0)
		res[2] = hit_point->ambient_coeff * hit_point->blue;
	else
		res[2] = hit_point->ambient_coeff * 255.0;	
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
		if (not_shaded(tmp, light_vector, env->elem, hit_point) > 0)
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
