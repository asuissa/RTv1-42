/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 23:59:06 by ymekraou          #+#    #+#             */
/*   Updated: 2019/03/16 22:56:03 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			access_surface_pixels(t_env *env)
{
	int				*pixels;
/*	SDL_PixelFormat *pf;
	Uint32			pxftenum;
	const char		*str;
*/
	pixels = NULL;
/*
	if(!(env->screen = SDL_ConvertSurfaceFormat(env->screen, SDL_PIXELFORMAT_RGBA8888, 0)))
		printf("caca\n");
	
	pf = env->screen->format;
	pxftenum = pf->format;
	str = SDL_GetPixelFormatName(pxftenum);
	SDL_Log("%s\n", str);i*/

	if (!(SDL_LockSurface(env->screen)))
	{
		pixels = env->screen->pixels;
		//move objects in camera space
		test(pixels, env);
		SDL_UnlockSurface(env->screen);
		return (1);
	}
	else
		return (0);
}
