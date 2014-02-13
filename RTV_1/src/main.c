/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 17:29:10 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/13 20:43:19 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	error_command(char *s)
{
	ft_putstr(s);
	exit(1);
}

void	init_univers(t_univers *v)
{
	v->w = 1280;
	v->h = 800;
	v->mlx = mlx_init();
	v->win_ray = mlx_new_window(v->mlx, v->w, v->h, "Rtv");
	v->img = mlx_new_image(v->mlx, v->w, v->h);
	v->camera = malloc(sizeof(*(v->camera)));
//	v->vector = malloc(sizeof(*(v->vector)));
	view_plane_camera(v);
	v->data = mlx_get_data_addr(v->img, &(v->bpp), &(v->s_line), &(v->endian));
}

int		key_control(int key_code)
{
	if(key_code == ESCAPE)
		exit(0);
	return (0);
}

int		expose_hook(t_univers *v)
{
		mlx_put_image_to_window(v->mlx, v->win_ray, v->data, 0, 0);
		return (0);
}

int	main(void)
{
	t_univers	*v;

	v = (t_univers *)malloc(sizeof(t_univers));
	init_univers(v);
	mlx_expose_hook(v->mlx, expose_hook, &v);
	mlx_key_hook(v->win_ray, key_control, &v);
	mlx_loop(v->mlx);
	return (0);
}
