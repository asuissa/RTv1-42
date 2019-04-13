/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 23:59:06 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/13 10:51:13 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double			anti_aliasing(int pixel, double canal[1000000])
{
	int i;
	int	j;
	double cpt;
	double stock;

	stock = 0.0;
	cpt = 0.0;
	i = pixel - 1000;
	while (i <= (pixel + 1001))
	{
		j = i - 1;
		while (j <= i + 1)
		{
			if ((j != pixel) && (j >= 0) && (j < 1000000))
			{
				stock += canal[j];
				cpt += 1.0;
			}
			j += 1;
		}
		i += 1000;
	}
	stock /= cpt;
	stock = (stock / canal[pixel]) * canal[pixel] + canal[pixel];
	if (stock > 255.0)
		stock = 255;
	return (stock);
}


double			gamma_correction(double color)
{
	double res;

	res = color / 255.0;
/*	if (res <= 0.0031308)
		res *= 12.92;
	else*/
		res = 0.94 * pow(res, (1.0/1.2));
	return (res * 255.0);
}

int			access_surface_pixels(t_env *env)
{
	pthread_t	thread_id[8];
	t_thread	data[8];
	int			i;

	if (!(SDL_LockSurface(env->screen)))
	{
		i = -1;
		while (++i < 8)
		{
			data[i].env = env;
			data[i].pixel_end = ((i + 1) * 125000) - 1;
			data[i].pixel_start = i * 125000;
			data[i].offset = (env->cam.vp_dim / 4.0) * i;
			pthread_create(&(thread_id[i]), NULL, ray_casting, &(data[i]));
		}
		i = -1;
		while (++i < 8)
			pthread_join(thread_id[i], NULL);
		SDL_UnlockSurface(env->screen);
		return (1);
	}
	else
		return (0);
}
