/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_component.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 11:41:18 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/13 11:49:19 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"


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
