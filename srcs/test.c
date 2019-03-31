/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:31:44 by ymekraou          #+#    #+#             */
/*   Updated: 2019/03/22 12:17:09 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		init_hit_point(t_hit *hit_point)
{
	hit_point->coord[0] = 0;
	hit_point->coord[1] = 0;
	hit_point->coord[2] = 0;
	hit_point->normal[0] = 0;
	hit_point->normal[1] = 0;
	hit_point->normal[2] = 0;
	hit_point->alpha = 0;
	hit_point->red = 0;
	hit_point->green = 0;
	hit_point->blue = 0;
	hit_point->color = 0x00000000;
	hit_point->hit = 0;
	hit_point->obj = NULL;
}

double		point_distance(double coord_one[3], double coord_two[3])
{
	double	tmp[3];
	int		i;
	i = -1;
	while (++i < 3)
		tmp[i] = pow(coord_one[i] - coord_two[i], 2);
	return (sqrt(tmp[0] + tmp[1] + tmp[2]));
}

int			compute_hit_point(t_hit *hit_point, double tmp[3], double cam_center[3], int color, int code)
{		
	if (hit_point->hit > 0)
	{
		if (point_distance(tmp, cam_center) < point_distance(hit_point->coord, cam_center))
		{
			hit_point->coord[0] = tmp[0];
			hit_point->coord[1] = tmp[1];
			hit_point->coord[2] = tmp[2];
			hit_point->color = color;
			hit_point->hit = code;
			return (1);
		}
		return (0);
	}
	else
	{
		hit_point->hit = code;
		hit_point->coord[0] = tmp[0];
		hit_point->coord[1] = tmp[1];
		hit_point->coord[2] = tmp[2];
		hit_point->color = color;
		return (1);
	}
}











double		compute_b_sphere(double ray_vector[3], double cam_center[3], double sphere_center[3])
{
	double tmp[3];

	tmp[0] = cam_center[0] - sphere_center[0];
	tmp[1] = cam_center[1] - sphere_center[1];
	tmp[2] = cam_center[2] - sphere_center[2];
	return (2 * dot_product(tmp, ray_vector));
}


double		compute_c_sphere(double sphere_radius, double cam_center[3], double sphere_center[3])
{
	double tmp[3];

	tmp[0] = cam_center[0] - sphere_center[0];
	tmp[1] = cam_center[1] - sphere_center[1];
	tmp[2] = cam_center[2] - sphere_center[2];
	return (dot_product(tmp, tmp) - pow(sphere_radius, 2));
}

void		hit_sphere(double ray_vector[3], double cam_center[3], void *data, t_hit *hit_point)
{
	double	a;
	double	b;
	double	c;
	double	ratio1;
	double	ratio2;
	double	tmp[3];
	t_sphere *sphere;

	sphere = (t_sphere*)data;
	a = dot_product(ray_vector, ray_vector);
	b = compute_b_sphere(ray_vector, cam_center, sphere->center);
	c = compute_c_sphere(sphere->radius, cam_center, sphere->center);
	if ( pow(b, 2) - (4 * a * c) >= 0)
	{
		if (pow(b, 2) - (4 * a * c) == 0)
			ratio1 = b / -2;
		else
		{
			ratio1 = (-(b) + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
			ratio2 = (-(b) - sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
			if (ratio2 < ratio1 && ratio2 >= 0)
				ratio1 = ratio2;
		}
		if (ratio1 >= 0)
		{
			tmp[0] = cam_center[0] + (ratio1 * ray_vector[0]);
			tmp[1] = cam_center[1] + (ratio1 * ray_vector[1]);
			tmp[2] = cam_center[2] + (ratio1 * ray_vector[2]);
			if (compute_hit_point(hit_point, tmp, cam_center, sphere->color, sphere->code))
			{
				normal_sphere(sphere->center, hit_point);
				hit_point->obj = data;
			}
		}
	}
}















double 		compute_a_cone(double ray_vector[3], t_cone cone)
{
	double res;

	res = dot_product(ray_vector, cone.vector);
	return ((res * res) - (cos(cone.aperture) * cos(cone.aperture)));
}

double 		compute_b_cone(double ray_vector[3], t_cone cone, double cam_center[3])
{
	double tmp[3];
	double tmp2;
	
	tmp[0] = cam_center[0] - cone.origin[0];
	tmp[1] = cam_center[1] - cone.origin[1];
	tmp[2] = cam_center[2] - cone.origin[2];
	tmp2 = dot_product(ray_vector, cone.vector) * dot_product(tmp, cone.vector)
			- dot_product(ray_vector, tmp) * pow(cos(cone.aperture), 2);
	return (2 * tmp2);
}

double 		compute_c_cone(t_cone cone, double cam_center[3])
{
	double tmp[3];
	double tmp2;
	
	tmp[0] = cam_center[0] - cone.origin[0];
	tmp[1] = cam_center[1] - cone.origin[1];
	tmp[2] = cam_center[2] - cone.origin[2];
	tmp2 = pow(dot_product(tmp, cone.vector), 2)
		- dot_product(tmp, tmp) * pow(cos(cone.aperture), 2);
	return (tmp2);
}

int			test_opposite_cone(double point[3], t_cone cone)
{
	double	tmp[3];

	tmp[0] = point[0] - cone.origin[0];
	tmp[1] = point[1] - cone.origin[1];
	tmp[2] = point[2] - cone.origin[2];
	norm_vector(tmp);
	if (dot_product(tmp, cone.vector) < 0)
		return (1);
	return (0);
}

void		hit_cone(double ray_vector[3], double cam_center[3], void *data, t_hit *hit_point)
{
	double	a;
	double	b;
	double	c;
	double	ratio1;
	double	ratio2;
	double	tmp[3];
	t_cone	*cone;

	cone = (t_cone*)data;
	a = compute_a_cone(ray_vector, *cone);
	b = compute_b_cone(ray_vector, *cone, cam_center);
	c = compute_c_cone(*cone, cam_center);

	if (pow(b, 2) - (4 * a * c) >= 0)
	{
		if (pow(b, 2) - (4 * a * c) == 0)
			ratio1 = b / -2;
		else
		{
			ratio1 = (-(b) + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
			ratio2 = (-(b) - sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
			if (ratio2 < ratio1 && ratio2 >= 0)
				ratio1 = ratio2;
		}
			tmp[0] = cam_center[0] + ratio1 * ray_vector[0];
			tmp[1] = cam_center[1] + ratio1 * ray_vector[1];
			tmp[2] = cam_center[2] + ratio1 * ray_vector[2];
			if (test_opposite_cone(tmp, *cone))
			{
				if (compute_hit_point(hit_point, tmp, cam_center, cone->color, cone->code))
				{
					normal_cone(cone, hit_point);
					hit_point->obj = data;
				}
			}
	}
}











void		hit_plan(double ray_vector[3], double cam_center[3], void *data, t_hit *hit_point)
{
	double	tmp[3];
	double	ratio;
	t_plan	*plan;

	plan = (t_plan*)data;	
	if (dot_product(ray_vector, plan->normal) > 0.000)
	{
		tmp[0] = plan->point[0] - cam_center[0];
		tmp[1] = plan->point[1] - cam_center[1];
		tmp[2] = plan->point[2] - cam_center[2];

		ratio = dot_product(tmp, plan->normal) / dot_product(ray_vector, plan->normal);
		tmp[0] = cam_center[0] + ratio * ray_vector[0];
		tmp[1] = cam_center[1] + ratio * ray_vector[1];
		tmp[2] = cam_center[2] + ratio * ray_vector[2];
		if (compute_hit_point(hit_point, tmp, cam_center, plan->color, plan->code))
		{
			normal_plan(plan->normal, hit_point);
			hit_point->obj = data;
		}
	}	
}













double 		compute_a_cylender(double ray_vector[3], double line_vector[3])
{
	double tmp[3];
	
	tmp[0] = ray_vector[0] - dot_product(ray_vector, line_vector) * line_vector[0];
	tmp[1] = ray_vector[1] - dot_product(ray_vector, line_vector) * line_vector[1];
	tmp[2] = ray_vector[2] - dot_product(ray_vector, line_vector) * line_vector[2];
	return (dot_product(tmp, tmp)); 
}

double 		compute_b_cylender(double ray_vector[3], t_cylender cylender, double cam_center[3])
{
	double delta[3];
	double tmp[3];
	double tmp2[3];
	
	delta[0] = cam_center[0] - cylender.origin[0];
	delta[1] = cam_center[1] - cylender.origin[1];
	delta[2] = cam_center[2] - cylender.origin[2];

	tmp[0] = ray_vector[0] - dot_product(ray_vector, cylender.line_vector) * cylender.line_vector[0];
	tmp[1] = ray_vector[1] - dot_product(ray_vector, cylender.line_vector) * cylender.line_vector[1];
	tmp[2] = ray_vector[2] - dot_product(ray_vector, cylender.line_vector) * cylender.line_vector[2];

	tmp2[0] = delta[0] - dot_product(delta, cylender.line_vector) * cylender.line_vector[0];
	tmp2[1] = delta[1] - dot_product(delta, cylender.line_vector) * cylender.line_vector[1];
	tmp2[2] = delta[2] - dot_product(delta, cylender.line_vector) * cylender.line_vector[2];

	return (2 * dot_product(tmp, tmp2)); 
}

double 		compute_c_cylender(t_cylender cylender, double cam_center[3])
{
	double delta[3];
	double tmp[3];
	
	delta[0] = cam_center[0] - cylender.origin[0];
	delta[1] = cam_center[1] - cylender.origin[1];
	delta[2] = cam_center[2] - cylender.origin[2];

	tmp[0] = delta[0] - dot_product(delta, cylender.line_vector) * cylender.line_vector[0];
	tmp[1] = delta[1] - dot_product(delta, cylender.line_vector) * cylender.line_vector[1];
	tmp[2] = delta[2] - dot_product(delta, cylender.line_vector) * cylender.line_vector[2];

	return (dot_product(tmp, tmp) - pow(cylender.radius, 2)); 
}

void		hit_cylender(double ray_vector[3], double cam_center[3], void *data, t_hit *hit_point)
{
	double	a;
	double	b;
	double	c;
	double	ratio1;
	double	ratio2;
	double	tmp[3];
	t_cylender *cylender;

	cylender = (t_cylender*)data;
	a = compute_a_cylender(ray_vector, cylender->line_vector);
	b = compute_b_cylender(ray_vector, *cylender, cam_center);
	c = compute_c_cylender(*cylender, cam_center);
	if (pow(b, 2) - (4 * a * c) >= 0)
	{
		if (pow(b, 2) - (4 * a * c) == 0)
			ratio1 = b / -2;
		else
		{
			ratio1 = (-(b) + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
			ratio2 = (-(b) - sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
			if (ratio2 < ratio1 && ratio2 >= 0)
				ratio1 = ratio2;
		}
		if (ratio1 >= 0)
		{
			tmp[0] = cam_center[0] + ratio1 * ray_vector[0];
			tmp[1] = cam_center[1] + ratio1 * ray_vector[1];
			tmp[2] = cam_center[2] + ratio1 * ray_vector[2];
			if (compute_hit_point(hit_point, tmp, cam_center, cylender->color, cylender->code))
			{
				normal_cylender(cylender, hit_point);
				hit_point->obj = data;
			}
		}
	}
}


void		test(int *pixels, t_env *env)
{
	t_elem		*tmp;
	double		pixel_center[3];
	double		pas;
	int			k;
	double		ray_vector[3];
	t_hit		hit_point;

	pas = env->cam.vp_dim / ((double)(SCREEN_WIDTH) / 2);
	pixel_center[2] = env->cam.vp_center[2];
	pixel_center[1] = env->cam.vp_center[1] + env->cam.vp_dim + (pas / 2);

	k = 0;
	while (k < (int)(SCREEN_WIDTH * SCREEN_WIDTH))
	{
		pixel_center[0] = env->cam.vp_center[0] - env->cam.vp_dim + (pas / 2);
		while (pixel_center[0] <= (env->cam.vp_center[0] + env->cam.vp_dim - (pas / 2)))
		{
			ray_vector[0] = pixel_center[0];
			ray_vector[1] = pixel_center[1];
			ray_vector[2] = pixel_center[2];
			norm_vector(ray_vector);
			init_hit_point(&hit_point);

			tmp = env->elem;
			while (tmp)
			{
				tmp->hit_funct(ray_vector, env->cam.cam_pos, tmp->object, &hit_point);
				tmp = tmp->next;
			}
			compute_color(env->light, &hit_point, ray_vector, env->elem);
			pixels[k] = hit_point.color;	
			++k;
			pixel_center[0] += pas;
		}
		pixel_center[1] -= pas;
	}
}
