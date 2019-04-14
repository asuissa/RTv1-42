/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymekraou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:47:19 by ymekraou          #+#    #+#             */
/*   Updated: 2019/04/14 18:55:57 by ymekraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include "libft.h"
# include "SDL.h"

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000

typedef struct	s_attributes
{
	int		color;
	double	ambient_coeff;
	double	diffuse_coeff;
	double	specular_coeff;
	double	shininess;
}				t_attributes;

typedef struct	s_hit
{
	double			coord[3];
	double			normal[3];
	void			*obj;
	double			ambient_coeff;
	double			diffuse_coeff;
	double			specular_coeff;
	double			shininess;
	int				color;
	double			red;
	double			green;
	double			blue;
	int				hit;
}				t_hit;

typedef struct	s_camera
{
	double	cam_pos[3];		//camera pos
	double	cam_angle[3];
	double	cam_pos_relative[3];
	double	vp_center[3];	//view port center
	double	vf_angle;		//view field angle
	double	vp_dim;			//vp half len
	double	pas;

}				t_camera;

typedef struct		s_light
{
	double			pos[3];
	double			pos_relative[3];
	double			light_angle[3];
	double			direction[3];
	double			direction_relative[3];
	double			aperture;
	int				color;
	double			red;
	double			green;
	double			blue;
	double			power;
	struct s_light	*next;
}					t_light;

typedef struct		s_sphere
{
	char			*type;
	double			center[3];
	double			center_relative[3];
	double			rotation[3];
	double			radius;
	t_attributes	attributes;
}					t_sphere;

typedef struct		s_plan
{
	char			*type;
	double			point[3];
	double			point_relative[3];		
	double			normal[3];			
	double			normal_relative[3];
	double			rotation[3];
	t_attributes	attributes;
}					t_plan;

typedef struct		s_cone
{
	char			*type;
	double			origin[3];		//cone origin 
	double			origin_relative[3];		//cone origin 
	double			aperture;		//divided by 2
	double			vector[3];
	double			vector_relative[3];
	double			rotation[3];
	t_attributes	attributes;
}					t_cone;

typedef struct		s_cylender
{
	char			*type;
	double			origin[3];		 
	double			origin_relative[3];		 
	double			line_vector[3];
	double			line_vector_relative[3];
	double			radius;
	double			rotation[3];
	t_attributes	attributes;
}					t_cylender;

typedef struct	s_elem
{
	void			*object;
	void			(*hit_funct)(double[3], double[3], void*, t_hit*);
	void			(*update_funct)(void*, t_camera*);
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

typedef struct	s_thread
{
	t_env	*env;
	int		pixel_end;
	int		pixel_start;
	double	offset;
}				t_thread;


int				access_surface_pixels(t_env *env);

void			init_cam(t_camera *cam);
void			init_light(t_light *light);
void			init_plan(t_plan *plan);
void			init_sphere(t_sphere *sphere);
void			init_cone(t_cone *cone);
void			init_cylender(t_cylender *cylender);
void			init_hit_point(t_hit *hit_point);

void			get_rgb_hit_point(t_hit *hit_point);
int				compute_hit_point(t_hit *hit_point, double tmp[3],
									double cam_center[3],
									t_attributes attributes);
void			*ray_casting(void *arg);

double			dot_product(double vec1[3], double vec2[3]);
void			norm_vector(double vec[3]);
double			point_distance(double coord_one[3], double coord_two[3]);
double			compute_ratio(double a, double b, double c);

void			file_parsing(char *file, t_env *env);
double			ft_atoi_double(char *str);
int				ft_atoi_hexa(char *str);
void			free_split_tab(char **tab);
void			ft_error(char *msg);
void			invalid_file_error(int fd);
int				invalid_read(char *file);
char			**parse_word(char *line);

void			camera_parsing(int fd, t_camera *cam);
t_light			*light_parsing(int fd, t_light *light, t_camera *cam);
t_sphere		*sphere_parsing(int fd, t_camera *cam);
t_plan			*plan_parsing(int fd, t_camera *cam);
t_cone			*cone_parsing(int fd, t_camera *cam);
t_cylender		*cylender_parsing(int fd, t_camera *cam);

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


double			compute_light_intensity(double point[3],
					double light[3],
					double power);
void			add_diffuse(double res[3],
					double light_vector[3],
					t_light *light,
					t_hit *hit_point);
void			add_specular(double res[3],
					double angle,
					t_light *light,
					t_hit *hit_point);
void			add_ambient(double res[3], t_hit *hit_point);

int				shading(t_light *light,
					double light_ray[3],
					t_elem *elem,
					t_hit *hit_point);

void			compute_color(t_hit *hit_point, double ray_vector[3], t_env *env);

void			rotate(double coord[3], double cam_angle[3]);
void			translate(double coord[3], double cam_pos[3]);
double			point_distance(double coord_one[3], double coord_two[3]);

void			update_scene(t_env *env);
void			update_sphere(void *sphere, t_camera *cam);
void			update_plan(void *plan, t_camera *cam);
void			update_cylender(void *cylender, t_camera *cam);
void			update_cone(void *cone, t_camera *cam);
#endif
