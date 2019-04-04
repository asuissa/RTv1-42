/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 23:59:06 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/04 17:00:40 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

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
