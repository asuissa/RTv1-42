/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:14:49 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/19 19:41:26 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		camera_movement(t_env *env, SDL_Keycode event)
{
	if (event == SDLK_UP)
		env->cam.cam_pos[2] += 1.0;
	else if (event == SDLK_DOWN)
		env->cam.cam_pos[2] -= 1.0;
	else if (event == SDLK_RIGHT)
		env->cam.cam_pos[0] += 1.0;
	else if (event == SDLK_LEFT)
		env->cam.cam_pos[0] -= 1.0;
	else if (event == SDLK_a)
		env->cam.cam_pos[1] -= 1.0;
	else if (event == SDLK_q)
		env->cam.cam_pos[1] += 1.0;
	else
		return (0);
	return (1);
}

int		camera_rotation(t_env *env, SDL_Keycode event)
{
	if (event == SDLK_e)
		env->cam.cam_angle[0] += (M_PI / 180.0);
	else if (event == SDLK_d)
		env->cam.cam_angle[0] -= (M_PI / 180.0);
	else if (event == SDLK_r)
		env->cam.cam_angle[1] += (M_PI / 180.0);
	else if (event == SDLK_f)
		env->cam.cam_angle[1] -= (M_PI / 180.0);
	else if (event == SDLK_t)
		env->cam.cam_angle[2] += (M_PI / 180.0);
	else if (event == SDLK_g)
		env->cam.cam_angle[2] -= (M_PI / 180.0);
	else
		return (0);
	return (1);
}

void	key_event(t_env *env, SDL_Keycode event)
{
	if (camera_movement(env, event) || camera_rotation(env, event))
	{
		update_scene(env);
		access_surface_pixels(env);
		SDL_UpdateWindowSurface(env->window);
	}
}
