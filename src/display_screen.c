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
	if (key == ESC)
		exit (0);
	(void)start;
	return (0);
}

int			expose_hook(t_data *start)
{
	get_img(head);
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

