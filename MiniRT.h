/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeancarlen <jeancarlen@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:41:42 by nnemeth           #+#    #+#             */
/*   Updated: 2023/03/13 17:19:18 by jeancarlen       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <ctype.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

# define BUFFER_SIZE 42
# define KEY_ESC 53
# define IMG_WIDTH 1024
# define IMG_HEIGHT 1024
# define TRUE 1
# define FALSE 0
# define KEY_ESC 53

# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define J_KEY 38
# define K_KEY 40

# define H 800
# define W 800
# define BUFSIZE 1024

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_form
{
	int				id;
	char			type;
	t_vector		coord;
	t_vector		orient;
	t_vector		color;
	float			sphere_rad;
	float			cyl_dia;
	float			cyl_height;
	struct s_form	*next;
}	t_form;

typedef struct s_cam
{
	t_vector		pos;
	t_vector		orient;
	float			fov;
	t_vector		right;
	t_vector		up;
}	t_cam;

typedef struct s_light
{
	int				id;
	char			type;
	t_vector		coord;
	t_vector		color;
	t_vector		light_dir;
	float			ratio;
	struct s_light	*next;
}	t_light;

typedef struct s_mlx
{
	int			win_i;
	int			win_y;
	void		*img;
	void		*mlx_ptr;
	void		*win_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_mlx;

typedef struct s_rays
{
	float		t;
	float		t1;
	float		t2;
	t_vector	ray_dir;
	t_vector	ray_orig;
	t_vector	p;
	t_vector	n;
	t_vector	col;
	int			hit_id;
}	t_rays;

typedef struct s_data
{
	int		element;
	t_form	*object;
	t_cam	camera;
	t_light	*light;
	t_rays	rays;
	t_mlx	mlx;
	int		test;
}	t_data;

/*init_parsing*/
t_form		*init_form(void);
t_light		*init_light(void);
void		init_cam(t_data *data);
void		init_all(t_data *data);
int			check_args(char *arg);
void		run_program(t_data *data);

/*init*/
void		ft_init_window(t_data *data);
void		set_scene(t_data *data);

/*inter*/
int			inter_sphere(t_data *data, t_form *current, t_rays *ray);
int			inter_plane(t_data *data, t_form *current, t_rays *ray);
int			inter_cylinder(t_data *data, t_form *current, t_rays *ray);
int			routine_inter(t_data *data, t_rays *ray);
int			hit_point(t_data *data, t_form *current, t_rays *ray);
int			plane_found(t_data *data, t_form *current, t_rays *ray);

/*launch*/
void		load_scene(t_data *data);
t_vector	get_light(t_data *data);
t_light		*light_details(t_data *data, t_light *c_light);

/*parsing_file_utils*/
void		print_tab(char **tab); //print a tab
int			ft_stoi(char *str); //convert str to int
float		ft_strtof(const char *str); //convert str to float
//check if there is a specified str in another str
int			ft_strinstr(const char *str, const char *substr);
int			contains_alpha(char *str);//check if there is a alpha char in str
void		free_tab(char **tab);//free a tab
int			ft_isspace(int c);
//finds the last element of the lights liked list and returns it
t_light		*last_light(t_data *data);
// finds the last element of the objects liked list and returns it
t_form		*last_obj(t_data *data);
void		*ft_realloc_rt_tab(void *ptr, size_t size);

/*parsing_file*/
//read all the file and return it as a big str
char		*readfile(char *filename);
//take a str, split the elements every <sep> and rtn all the elements as a tab
char		**split_string(const char *str, char sep);
char		**second_split(char *str);
//take a tab that contains string, split them and save them in a struct.
void		convert_tab(char **tab, t_data *data);

/*quit*/
int			close_window(t_data *data);
int			escape(int keycode, t_data *data);

/*utils*/
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			color(double r, double g, double b);
int			ray_color(int t, int r, int g, int b);
int			color2(double r, double g, double b);
void		init_t(t_rays *ray);

/*vectors*/
double		getnorm(t_vector vector);
t_vector	normalize(t_vector vector);
double		dot(t_vector ray_dir, t_vector ray_o);
t_vector	minus(t_vector origin, t_vector position);
void		reverse_vector(t_vector *vec);

/*vectors2*/
t_vector	ft_mult(double t, t_vector v1);
double		ft_mult2(t_vector v2, t_vector v1);
t_vector	ft_plus(t_vector origin, t_vector position);
double		ft_max(double clr);
t_vector	ft_divide(t_vector v1, double a);
t_vector	ft_mult_vec(t_vector v1, t_vector v2);
t_vector	add_values(double x, double y, double z);

/*free_error*/

int			does_it_segf(char *str);
int			tab_check(char **tab);
int			tab_check_rgb(char **tab);

/*forms*/

void		sphere(char *str, int x, t_data *data);
void		sphere_2(char *str, t_form *new_f, t_data *data);
void		plan(char *str, int x, t_data *data);
void		plan_2(char *str, t_form *new_f, t_data *data);
void		cylindre(char *str, int x, t_data *data);
void		cylindre_2(char *str, t_form *new_f, t_data *data);
void		cam(char *str, t_data *data);
void		put_orient_cam(char **vector, t_data *data);
void		put_coord_cam(char **vector, t_data *data);
void		ambiant(char *str, t_data *data);
void		ambiant_2(char *str, t_light *new_l, t_data *data);
void		light(char *str, int x, t_data *data);
void		light_2(char *str, t_light *new_l, t_data *data);
void		put_color_form(char **vector, t_form *new_f, t_data *data);
void		put_orient_form(char **vector, t_form *new_f, t_data *data);
void		put_coord_form(char **vector, t_form *new_f, t_data *data);
void		put_color_light(char **vector, t_light *new_l, t_data *data);
void		put_coord_light(char **vector, t_light *new_l, t_data *data);
t_vector	cross(t_vector vect_a, t_vector vect_b);
void		print_vec(char *str, t_vector v);

/*pas trouv?? dans les fichiers*/

t_vector	ft_minus(t_vector v1, t_vector v2);

t_vector	add_amb(t_data *data, t_rays *ray);
char		*ft_strncpy_rt(char *dest, const char *src, size_t n);
void		*ft_realloc_rt(void *ptr, size_t size);
void		free_struc(t_data *data);
void		free_light(t_data *data);
t_light		*get_light_type(t_light *light, char type);

#endif

/*TO DO*/
/*
shadows --ISH --Ish --ish
passer lumi??re ambiante a la place de data->light... -ISH
orientation de la camera (big step small step) --finish --ish
dividing big function remake
error
NORMINETTTTTTTTTTTTTTTTTTTTTTTTTE
*/