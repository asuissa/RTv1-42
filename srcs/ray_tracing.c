/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 10:28:49 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/13 10:50:25 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

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
			((int*)(env->screen->pixels))[k++] = trace_ray(pixel_center, env);
			pixel_center[0] += (env->cam.pas);
		}
		pixel_center[1] -= (env->cam.pas);
	}
	pthread_exit(NULL);
}
