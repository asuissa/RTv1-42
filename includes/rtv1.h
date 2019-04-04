/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:47:19 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/04 22:18:30 by asuissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "SDL.h"

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000



typedef struct	s_hit
{
	double			coord[3];
	double			normal[3];
	void			*obj;
	int				color;
	int				alpha;
	int				red;
	int				green;
	int				blue;
	int				hit;
}				t_hit;

typedef struct	s_camera
{
	double	cam_pos[3];		//camera pos 
	double	vp_center[3];	//view port center
	double	vf_angle;		//view field angle
	double	vp_dim;			//vp half ken

}				t_camera;

typedef struct	s_light
{
	double			pos[3];
	double			ambient;
	int				diffuse_color;
	int				diffuse_red;
	int				diffuse_green;
	int				diffuse_blue;
	double			specular;
	double			size;
	char			*type;
	struct s_light	*next;
}				t_light;

typedef struct	s_sphere
{
	char	*type;
	double	center[3];		//camera pos 
	double	radius;			//view port center
	int		color;
	int		code;
}				t_sphere;

typedef struct	s_plan
{
	char	*type;
	double	point[3];		//plan origin 
	double	normal[3];		//plan vector
	int		color;
	int		code;
}				t_plan;

typedef struct	s_cone
{
	char	*type;
	double	origin[3];		//cone origin 
	double	aperture;		//divided by 2
	double	vector[3];
	int		color;
	int		code;
}				t_cone;

typedef struct	s_cylender
{
	char	*type;
	double	origin[3];
	double	line_vector[3];
	double	radius;	
	int		color;
	int		code;
}				t_cylender;

typedef struct	s_elem
{
	void			*object;
	void			(*hit_funct)(double[3], double[3], void*, t_hit*);
	struct s_elem	*next;
}				t_elem;

typedef struct	s_env
{
	SDL_Window	*window;
	SDL_Surface	*screen;
	t_camera	cam;
	t_light		*light;
	t_elem		*elem;
}				t_env;

int				access_surface_pixels(t_env *env);

void			init_cam(t_camera *cam);
void			init_light(t_light *light);
void			init_hit_point(t_hit *hit_point);

void			init_plan(t_plan *plan);
void			init_sphere(t_sphere *sphere);
void			init_cone(t_cone *cone);
void			init_cylender(t_cylender *cylender);

void			test(int *pixels, t_env *env);

double			dot_product(double vec1[3], double vec2[3]);
void			norm_vector(double vec[3]);
double			point_distance(double coord_one[3], double coord_two[3]);

void			file_parsing(char *file, t_env *env);
double			ft_atoi_double(char *str);
int				ft_atoi_hexa(char *str);

void			camera_parsing(int fd, t_camera *cam);
t_light			*light_parsing(int fd, t_light *light);
t_sphere		*sphere_parsing(int fd);
t_plan			*plan_parsing(int fd);
t_cone			*cone_parsing(int fd);
t_cylender		*cylender_parsing(int fd);

void			hit_sphere(double ray_vector[3],
							double cam_center[3],
							void *data,
							t_hit *hit_point);

void			hit_plan(double ray_vector[3],
						double cam_center[3],
						void *data,
						t_hit *hit_point);

void			hit_cone(double ray_vector[3],
						double cam_center[3],
						void *data,
						t_hit *hit_point);

void			hit_cylender(double ray_vector[3],
							double cam_center[3],
							void *data,
							t_hit *hit_point);

void			normal_sphere(double sphere_center[3], t_hit *hit_point);
void			normal_plan(double normal_plan[3], t_hit *hit_point);
void			normal_cylender(t_cylender *cylender, t_hit *hit_point);
void			normal_cone(t_cone *cone, t_hit *hit_point);


double			point_distance(double coord_one[3], double coord_two[3]);

void			compute_color(t_light *light, t_hit *hit_point, double ray_vector[3], t_elem *elem);

#endif
