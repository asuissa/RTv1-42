/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 23:59:06 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/23 18:46:27 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			access_surface_pixels(t_env *env)
{
	pthread_t	thread_id[THREAD_NB];
	t_thread	data[THREAD_NB];
	int			i;
	double		offset;

	offset = (env->cam.vp_height) / (double)(THREAD_NB);
	if (!(SDL_LockSurface(env->screen)))
	{
		i = -1;
		while (++i < THREAD_NB)
		{
			data[i].env = env;
			data[i].range_y = (int)(SCREEN_HEIGHT / THREAD_NB);
			data[i].pixel_start = i * data[i].range_y * (int)(SCREEN_WIDTH);
			data[i].offset = (offset * i) - (env->cam.pixel_size / 2.0);
			pthread_create(&(thread_id[i]), NULL, ray_casting, &(data[i]));
		}
		i = -1;
		while (++i < THREAD_NB)
			pthread_join(thread_id[i], NULL);
		SDL_UnlockSurface(env->screen);
		return (1);
	}
	else
		return (0);
}
