/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 23:41:59 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/04 17:13:14 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	get_rgb_hit_point(t_hit *hit_point)
{
	int		color;

	color = hit_point->color;

	hit_point->blue = (color % (16 * 16));
	color = color / (16 * 16);
	hit_point->green = (color % (16 * 16));
	color = color / (16 * 16);
	hit_point->red = (color % (16 * 16));
	color = color / (16 * 16);
	hit_point->alpha = (color % (16 * 16));
	color = color / (16 * 16);
}

int		is_shaded(t_light *light, double light_ray[3], t_elem *elem, t_hit *hit_point)
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
	if (dot_product(reversed_light, light->direction_relative) < cos((10.0 * M_PI) / 180))
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

void	compute_color(t_light *light, t_hit *hit_point, double cam_vector[3], t_elem *elem)
{
	t_light	*tmp;
	double	stock;
	int 	i;
	double	diffuse_att;
	double	specular_att;
	double	light_vector[3];
	double	reflected[3];
	double	final_res[4];
	double	tmp_res[3];
	double	light_intensity;
	double	light_diff_red;
	double	light_diff_green;
	double	light_diff_blue;
	double 	coeff_spec_r;
	double 	coeff_spec_g;
	double 	coeff_spec_b;
	double 	coeff_diff_r;
	double 	coeff_diff_g;
	double 	coeff_diff_b;
	double	shaded;

	i = -1;
	while(++i < 3)
		cam_vector[i] *= (-1.0);
		
	get_rgb_hit_point(hit_point);
	final_res[0] = 0;
	final_res[1] = 0.1 * 255.0;
	final_res[2] = 0.1 * 255.0;
	final_res[3] = 0.1 * 255.0;

	tmp = light;
	while (tmp)
	{
		
		diffuse_att = 0.0;
		specular_att = 0.0;
		i = -1;
		while(++i < 3)
			light_vector[i] = (tmp->pos_relative[i] - hit_point->coord[i]);
		norm_vector(light_vector);
	
		i = -1;
		while (++i < 3)	
			reflected[i] = 2 * hit_point->normal[i] * dot_product(light_vector, hit_point->normal) - light_vector[i];
		norm_vector(reflected);
	
		shaded = is_shaded(tmp, light_vector, elem, hit_point);

		if ((stock = dot_product(light_vector, hit_point->normal)) < 0 || !(shaded))
			diffuse_att += 0;
		else
			diffuse_att = stock ;

		if ((stock = dot_product(cam_vector, reflected)) < 0 || !(shaded) || (diffuse_att == 0))
			specular_att += 0;
		else
			specular_att += stock;
		specular_att = pow(specular_att, 100);
		
		light_intensity =  1 - (point_distance(hit_point->coord, tmp->pos_relative) / 10000.0);
		light_diff_red = diffuse_att * (double)(tmp->diffuse_red) * light_intensity;
		light_diff_green = diffuse_att * (double)(tmp->diffuse_green) * light_intensity;	
		light_diff_blue = diffuse_att * (double)(tmp->diffuse_blue) * light_intensity;
	
		coeff_diff_r = 0.6;
		coeff_diff_g = 0.6;
		coeff_diff_b = 0.6;

	
		if (hit_point->red > light_diff_red)
			tmp_res[0] = light_diff_red * coeff_diff_r;
		else
			tmp_res[0] = (double)(hit_point->red) * coeff_diff_r;
		if (hit_point->green > light_diff_green)
			tmp_res[1] = light_diff_green * coeff_diff_g;
		else
			tmp_res[1] = (double)(hit_point->green) * coeff_diff_g;
		if (hit_point->blue > light_diff_blue)
			tmp_res[2] = light_diff_blue * coeff_diff_b;
		else
			tmp_res[2] = (double)(hit_point->blue) * coeff_diff_b;


		coeff_spec_r = 0.3;
		coeff_spec_g = 0.3;
		coeff_spec_b = 0.3;

		tmp_res[0] += (coeff_spec_r * 255.0 * specular_att);
		tmp_res[1] += (coeff_spec_g * 255.0 * specular_att);
		tmp_res[2] += (coeff_spec_b * 255.0 * specular_att);

		i = -1;
		while (++i < 3)
		{
			final_res[i + 1] += tmp_res[i];
			if (final_res[i + 1] > 255.0)
				final_res[i + 1] = 255.0;
		}
		tmp = tmp->next;
	}

	
	hit_point->color = 0;
	hit_point->color |= (int)(final_res[0]) << 24;
	hit_point->color |= (int)(final_res[1]) << 16;
	hit_point->color |= (int)(final_res[2]) << 8;
	hit_point->color |= (int)(final_res[3]);
}
