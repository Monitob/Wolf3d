/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 21:25:31 by jbernabe          #+#    #+#             */
/*   Updated: 2014/01/17 21:28:25 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_display_screen(t_world *start)
{
	start->init_mlx = mlx_init();
	if (start->init_mlx == NULL)
		return (0);
	if ((start->init_win = mlx_new_window(start->init_mlx,
					SCR_WIDTH, SCR_HEIGHT,
					"Wolf3d")) == NULL)
		return (0);
	mlx_key_hook(start->init_win, key_hook, start);
	return (0);
}

int			key_hook(int keycode, t_world *start)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(start->init_mlx, start->init_win);
		mlx_destroy_image(start->init_mlx, start->mlx_data);
		exit(0);
	}
/*
	else if (keycode,  == LEFT)
		key_left(start);
	else if (key == UP)
		key_up(start);
	else if (key == RIGHT)
		key_right(start);
	else if (key == DOWN)
		key_down(start);
*/
		return (0);
}

int			expose_hook(t_data *start)
{
	if ((mlx_put_image_to_window(start->win->init_mlx,
						start->win->init_win,
						start->imag->ptr_img, IMG_POS_X, IMG_POS_Y)) == 0)
		exit(0);
	return (0);
}

void		get_img(t_data *img)
{
	img->imag->ptr_img = mlx_new_image(img->win->init_mlx,
			img->map->height,
			img->map->width);
	if (img->imag->ptr_img == NULL)
		exit(0);
	img->win->mlx_data = mlx_get_data_addr(img->imag->ptr_img,
			&(img->imag->bpp),
			&(img->imag->size_line),
			&(img->imag->endian));
	if (img->win->mlx_data == NULL)
		exit(0);
}

