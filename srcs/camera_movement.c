/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 19:46:44 by ymekraou          #+#    #+#             */
/*   Updated: 2019/03/30 19:59:57 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		rotate(double coord[3], double cam_angle[3])
{
	double	tmp[3];

	tmp[0] = cos(cam_angle[1]) * (sin(cam_angle[2]) * coord[1]
			+ cos(cam_angle[2]) * coord[0]) - sin(cam_angle[1]) * coord[2];
	tmp[1] = sin(cam_angle[0]) * (cos(cam_angle[1]) * coord[2]
			+ (sin(cam_angle[1]) * (sin(cam_angle[2]) * coord[1]
			+ cos(cam_angle[2]) * coord[0]))) + cos(cam_angle[0])
			* (cos(cam_angle[2]) * coord[1] - sin(cam_angle[2]) * coord[0]);
	tmp[2] = cos(cam_angle[0]) * (cos(cam_angle[1]) * coord[2]
			+ (sin(cam_angle[1]) * (sin(cam_angle[2]) * coord[1]
			+ cos(cam_angle[2]) * coord[0]))) - sin(cam_angle[0])
			* (cos(cam_angle[2]) * coord[1] - sin(cam_angle[2]) * coord[0]);
	coord[0] = tmp[0];
	coord[1] = tmp[1];
	coord[2] = tmp[2];
}

void		translate(double coord[3], double cam_pos[3])
{
	coord[0] -= cam_pos[0];
	coord[1] -= cam_pos[1];
	coord[2] -= cam_pos[2];
}
