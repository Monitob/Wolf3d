/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 17:49:35 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/13 22:09:43 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef				RTV_H
# define			RTV_H

# include			<math.h>
# include			<stdio.h>
# include			<mlx.h>
# include			<libft.h>

# define ESCAPE 65307
# define CAMERA_DIST_V	1.0 /*distance entre la cameraet le vieuw plan*/
# define CAMERA_LEN 0.35 /*LARGEUR*/
# define CAMERA_HEIGHT 0.5 /*HAUTERU*/
# define MAX_ROW 1200
# define MAX_COL 700
# define CAM_X -300.0
# define CAM_Y 0.0
# define CAM_Z 0.0
# define V_DIREX 0.0
# define V_DIREY 0.0
# define V_DIREZ 1.0

typedef struct		s_vector
{
	float			x_pos;
	float			y_pos;
	float			z_pos;
}					t_vector;

typedef struct		s_camera
{
	t_vector		position;
	t_vector		direction;
	t_vector		upvect;
	t_vector		rightvect;
}					t_camera;

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_univers
{
	int				w;
	int				h;
	int				key_type;
	void			*mlx;
	void			*win_ray;
	void			*img;
	int				bpp;
	int				endian;
	int				s_line;
	char			*data;
	t_camera		*camera;
	t_rgb			*colors;
	t_vector		view_up_left;
//	t_vector		*vector;
}					t_univers;

int			view_plane_camera(t_univers *v);
t_vector	ft_mult_vector(t_vector v1, t_vector v2);
t_vector	ft_subb_vector(t_vector v1, t_vector v2);
t_vector	ft_add_vector(t_vector v1, t_vector v2);
t_vector	ft_creat_vector(float x, float y, float z);
void		error_command(char *s);
int			key_control(int key_code);
int			expose_hook(t_univers *v);
void		init_univers(t_univers *v);
void		init_windows(t_univers *v);

#endif
