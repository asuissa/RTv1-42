/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:31:44 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/10 03:57:47 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		init_hit_point(t_hit *hit_point)
{
	hit_point->coord[0] = 0;
	hit_point->coord[1] = 0;
	hit_point->coord[2] = 0;
	hit_point->normal[0] = 0;
	hit_point->normal[1] = 0;
	hit_point->normal[2] = 0;
	hit_point->red = 0;
	hit_point->green = 0;
	hit_point->blue = 0;
	hit_point->color = 0x00000000;
	hit_point->hit = 0;
	hit_point->obj = NULL;
}

int			compute_hit_point(t_hit *hit_point, double tmp[3],
								double cam_center[3], t_attributes attributes)
{
	if (hit_point->hit > 0)
	{
		if (point_distance(tmp, cam_center)
				< point_distance(hit_point->coord, cam_center))
		{
			hit_point->coord[0] = tmp[0];
			hit_point->coord[1] = tmp[1];
			hit_point->coord[2] = tmp[2];
			hit_point->hit = 1;
			hit_point->color = attributes.color;
			hit_point->ambient_coeff = attributes.ambient_coeff;
			hit_point->diffuse_coeff = attributes.diffuse_coeff;
			hit_point->specular_coeff = attributes.specular_coeff;
			hit_point->shininess = attributes.shininess;
			return (1);
		}
		return (0);
	}
	else
	{
		hit_point->coord[0] = tmp[0];
		hit_point->coord[1] = tmp[1];
		hit_point->coord[2] = tmp[2];
		hit_point->hit = 1;
		hit_point->color = attributes.color;
		hit_point->ambient_coeff = attributes.ambient_coeff;
		hit_point->diffuse_coeff = attributes.diffuse_coeff;
		hit_point->specular_coeff = attributes.specular_coeff;
		hit_point->shininess = attributes.shininess;
		return (1);
	}
}

void		init_ray(double ray_vector[3],
						double pixel_center[3], t_hit *hit_point)
{
	ray_vector[0] = pixel_center[0];
	ray_vector[1] = pixel_center[1];
	ray_vector[2] = pixel_center[2];
	norm_vector(ray_vector);
	init_hit_point(hit_point);
}

int			trace_ray(double pixel_center[3], t_env *env)
{
	t_hit	hit_point;
	double	ray_vector[3];
	t_elem	*tmp;

	init_ray(ray_vector, pixel_center, &(hit_point));
	tmp = env->elem;
	while (tmp)
	{
		tmp->hit_funct(ray_vector, env->cam.cam_pos_relative,
						tmp->object, &hit_point);
		tmp = tmp->next;
	}
	if (hit_point.hit)
		compute_color(&hit_point, ray_vector, env);
	else
		return (0);
	return (SDL_MapRGB(env->screen->format, (int)(hit_point.red),
						(int)(hit_point.green), (int)(hit_point.blue)));
}

void		*ray_casting(void *arg)
{
	t_env		*env;
	double		pixel_center[3];
	int			k;

	env = ((t_thread*)arg)->env;
	pixel_center[2] = env->cam.vp_center[2];
	pixel_center[1] = env->cam.vp_center[1] + env->cam.vp_dim
		+ ((env->cam.pas) / 2.0) - ((t_thread*)arg)->offset;
	k = ((t_thread*)arg)->pixel_start;
	while (k < ((t_thread*)arg)->pixel_end)
	{
		pixel_center[0] = env->cam.vp_center[0]
			- env->cam.vp_dim + ((env->cam.pas) / 2.0);
		while (pixel_center[0] <= (env->cam.vp_center[0]
					+ env->cam.vp_dim - ((env->cam.pas) / 2.0)))
		{
			env->raw_pixels[k++] = trace_ray(pixel_center, env);
			pixel_center[0] += (env->cam.pas);
		}
		pixel_center[1] -= (env->cam.pas);
	}
	pthread_exit(NULL);
}
