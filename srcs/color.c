/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 23:41:59 by ymekraou          #+#    #+#             */
/*   Updated: 2019/03/22 11:31:22 by ymekraou         ###   ########.fr       */
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

int		is_shaded(double light_pos[3], t_elem *elem, t_hit *hit_point)
{
	t_hit	shade_hit;
	t_elem	*tmp;
	double	vector[3];
	double	bias[3];
	int		i;

	init_hit_point(&shade_hit);
	i = -1;
	while (++i < 3)
	{
		vector[i] = (hit_point->coord[i] + 0.0001 * hit_point->normal[i])  - light_pos[i];
		shade_hit.coord[i] = (hit_point->coord[i] + 0.0001 * hit_point->normal[i]);
		bias[i] = (hit_point->coord[i] + 0.0001 * hit_point->normal[i]); 
	}
	norm_vector(vector);
	tmp = elem;
	while (tmp)
	{
		tmp->hit_funct(vector, light_pos, tmp->object, &shade_hit);
		if ( point_distance(shade_hit.coord, light_pos) < point_distance(bias, light_pos))
			return (1);
		tmp = tmp->next;
	}
	return (0);
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
	double	coeff_red;
	double	coeff_green;
	double	coeff_blue;
	double 	coeff_spec_r;
	double 	coeff_spec_g;
	double 	coeff_spec_b;
	double	shaded;

	i = -1;
	while(++i < 3)
		cam_vector[i] *= (-1.0);
	
	final_res[0] = 0;
	final_res[1] = 0;
	final_res[2] = 0;
	final_res[3] = 0;
	
	get_rgb_hit_point(hit_point);
	tmp = light;
	while (tmp)
	{
		diffuse_att = 0.0;
		specular_att = 0.0;
		i = -1;
		while(++i < 3)
			light_vector[i] = (tmp->pos[i] - hit_point->coord[i]);
		norm_vector(light_vector);
	
		i = -1;
		while (++i < 3)	
			reflected[i] = 2 * hit_point->normal[i] * dot_product(light_vector, hit_point->normal) - light_vector[i];
		norm_vector(reflected);
	
		shaded = is_shaded(tmp->pos, elem, hit_point);

		if ((stock = dot_product(light_vector, hit_point->normal)) < 0 || shaded)
			diffuse_att += 0;
		else
			diffuse_att += stock;

		if ((stock = dot_product(cam_vector, reflected)) < 0 || shaded || (diffuse_att == 0))
			specular_att += 0;
		else
			specular_att += stock;
		specular_att = pow(specular_att, 100);
		
		if (hit_point->red >= light->diffuse_red)
			coeff_red = ((double)(hit_point->red - (hit_point->red - light->diffuse_red)) / (double)(hit_point->red));
		else
			coeff_red = ((double)(hit_point->red) / (double)(light->diffuse_red));
		
		if (hit_point->green >= light->diffuse_green)
			coeff_green = ((double)(hit_point->green - (hit_point->green - light->diffuse_green)) / (double)(hit_point->green));
		else
			coeff_green = ((double)(hit_point->green) / (double)(light->diffuse_green));
		if (hit_point->blue >= light->diffuse_blue)
			coeff_blue = ((double)(hit_point->blue - (hit_point->blue - light->diffuse_blue)) / (double)(hit_point->blue));
		else
			coeff_blue = ((double)(hit_point->blue) / (double)(light->diffuse_blue));

		coeff_spec_r = 1.0 - coeff_red - 0.1;
		coeff_spec_g = 1.0 - coeff_green - 0.1;
		coeff_spec_b = 1.0 - coeff_blue - 0.1;

		tmp_res[0] = ((double)(hit_point->red)) * coeff_red * diffuse_att * 1 + (1 * coeff_spec_r * 255.0 *  specular_att);
		tmp_res[1] = ((double)(hit_point->green)) * coeff_green * diffuse_att * 1 + (1 * coeff_spec_g * 255.0 * specular_att);
		tmp_res[2] = ((double)(hit_point->blue)) * coeff_blue * diffuse_att * 1 + (1 * coeff_spec_b * 255.0 * specular_att);

		i = -1;
		while (++i < 3)
		{
			if (tmp_res[i] > final_res[i + 1])
				final_res[i + 1] += (tmp_res[i] - final_res[i + 1]);
		}




		tmp = tmp->next;
	}

/*	res[1] = ((double)(hit_point->red)) * coeff_red * diffuse_att * 1 + (1 * coeff_spec_r * 255.0 *  specular_att);
	res[2] = ((double)(hit_point->green)) * coeff_green * diffuse_att * 1 + (1 * coeff_spec_g * 255.0 * specular_att);
	res[3] = ((double)(hit_point->blue)) * coeff_blue * diffuse_att * 1 + (1 * coeff_spec_b * 255.0 * specular_att);
*/

	hit_point->color = 0;
	hit_point->color |= (int)(final_res[0]) << 24;
	hit_point->color |= (int)(final_res[1]) << 16;
	hit_point->color |= (int)(final_res[2]) << 8;
	hit_point->color |= (int)(final_res[3]);
}
