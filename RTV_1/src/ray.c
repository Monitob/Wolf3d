/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 13:40:53 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/15 20:48:19 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"
#include <stdio.h>
int		view_plane_camera(t_univers *v)
{
	t_vector	temp1;
	t_vector	temp2;
	t_vector	temp0;
	double		x;
	double		y;

	v->camera->position = ft_creat_vector((double)CAM_X, (double)CAM_Y
			, (double)CAM_Z);
	v->camera->direction = ft_creat_vector((double)V_DIREX, (double)V_DIREY
			, (double)V_DIREZ);
	v->camera->upvect = ft_creat_vector((double)0, (double)0, (double)1);
	v->camera->rightvect = ft_mult_vector(v->camera->upvect
						, v->camera->direction);
	temp0 = ft_double_by_vector((double)CAMERA_DIST_V, v->camera->direction);
	temp1 = ft_double_by_vector((double)CAMERA_HEIGHT/2.0, v->camera->upvect);
	temp2 = ft_double_by_vector((double)CAMERA_LEN/2.0, v->camera->rightvect);
	v->view_up_left  =  ft_add_vector(ft_add_vector(v->camera->position
				, temp0), temp1);
	v->view_up_left = ft_subb_vector(v->view_up_left, temp2);
	x = 0;
	y = 0;
	while (x < RESO_X)
	{
		while (y < RESO_Y)
		{
			v->pixel_pos = pixel_pos(v->view_up_left, v->camera->rightvect,
					v->camera->upvect, x , y);
			v->ray_normal = ft_normalize(ft_subb_vector(v->pixel_pos
						, v->camera->position));
			ft_draw_sphere(v->camera->position, v->ray_normal);
			y++;
		}
		x++;
	}
	return (0);
}

double		ft_draw_sphere(t_vector orig, t_vector dir)
{
	double	a;
	double	b;
	double	c;
	double	det;
	double	t;

	a = 1.0 / 4.0; /*pow(dir.x_pos, 2) + pow(dir.y_pos, 2) + pow(dir.z_pos, 2);*/
	b = 2 * (dir.x_pos * (orig.x_pos - X_SPHERE)
			+ dir.y_pos * (orig.y_pos - Y_SPHERE)
			+ dir.z_pos * (orig.z_pos - Z_SPHERE));
	c = (pow(orig.x_pos - X_SPHERE, 2) + pow(orig.y_pos - Y_SPHERE, 2)
			+ pow(orig.z_pos - Z_SPHERE, 2) - pow(R_SPHERE, 2));
	det = (b * b) - (4*a*c);
	if (det >= 0)
	{
		t = (-b - sqrt(det)) / (2.0 * a);
		return (t);
	}
	return (0);
}
