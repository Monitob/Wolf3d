/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 13:40:53 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/13 22:15:42 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"
#include <stdio.h>
int		view_plane_camera(t_univers *v)
{
	t_vector	temp1;
	t_vector	temp2;
	t_vector	temp0;


	v->camera->position = ft_creat_vector((float)CAM_X, (float)CAM_Y
						, (float)CAM_Z);
	/*printf("camera x%f\n",v->camera->position.x_pos);
	printf("camera y %f\n",v->camera->position.y_pos);
	printf("camera z%f\n",v->camera->position.z_pos);*/
	v->camera->direction = ft_creat_vector((float)V_DIREX, (float)V_DIREY
							, (float)V_DIREZ);
/*	printf("vect direct x%f\n",v->camera->direction.x_pos);
	printf("vect direct y%f\n",v->camera->direction.y_pos);
	printf("vect direct z%f\n",v->camera->direction.z_pos);*/
	v->camera->upvect = ft_creat_vector((float)0, (float)1, (float)0);
	v->camera->rightvect = ft_creat_vector((float)0, (float)1,
			(float)0);
/*	printf("%f\n",v->camera->upvect.x_pos);
	printf("%f\n",v->camera->upvect.y_pos);
	printf("%f\n",v->camera->upvect.z_pos);*/
	temp0 = ft_float_by_vector((float)CAMERA_DIST_V, v->camera->direction);
	temp1 = ft_float_by_vector((float)CAMERA_HEIGHT/2.0, v->camera->upvect);
	temp2 = ft_float_by_vector((float)CAMERA_LEN/2.0, v->camera->rightvect);
	v->view_up_left  =  ft_subb_vector(ft_add_vector(ft_add_vector(v->camera->position
					, temp0), temp1), temp2);
	return (0);
}

t_vector		ft_float_by_vector(float a, t_vector v1)
{
	t_vector	new_v;

	new_v.x_pos = v1.x_pos * a;
	new_v.y_pos = v1.y_pos * a;
	new_v.z_pos = v1.z_pos * a;
	return (new_v);
}

t_vector		ft_add_vector(t_vector v1, t_vector v2)
{
	t_vector	new_v;

	new_v.x_pos = v1.x_pos + v2.x_pos;
	new_v.y_pos = v1.y_pos + v2.y_pos;
	new_v.z_pos = v1.z_pos + v2.z_pos;
	return (new_v);
}
 
t_vector		ft_subb_vector(t_vector v1, t_vector v2)
{
	t_vector	new_v;

	new_v.x_pos = v1.x_pos - v2.x_pos;
	new_v.y_pos = v1.y_pos - v2.y_pos;
	new_v.z_pos = v1.z_pos - v2.z_pos;
	return (new_v);
}

t_vector		ft_creat_vector(float x, float y, float z)
{
	t_vector	v;

	v.x_pos = x;
	v.y_pos = y;
	v.z_pos = z;
	return (v);
}
