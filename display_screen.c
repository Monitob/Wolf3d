/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 21:25:31 by jbernabe          #+#    #+#             */
/*   Updated: 2014/01/14 23:00:30 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_display_screen(t_map *head)
{
	t_world *start;

	if (((start = (t_world *)ft_memalloc(sizeof(*start))) == NULL))
		return (0);
	start->init_mlx = mlx_init();
	if (start->init_mlx == NULL)
		return (0);
	if ((start->init_win = mlx_new_window(start->init_mlx,
				SCR_WIDTH, SCR_HEIGHT,
				"Wolf3d")) == NULL)
		return (0);
	mlx_key_hook(start->init_win, key_hook, start);
	mlx_expose_hook(start->init_win, expose_hook, start);
	mlx_loop(start->init_mlx);
	return (0);
}

int			key_hook(int keycode, t_world *start)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(start->init_mlx, start->init_win);
		mlx_destroy_image(start->init_mlx, start->mlx_data);
		exit(0);
	}
	return (0);
}

int			expose_hook(t_world *start)
{
	if ((mlx_put_image_to_window(start->init_mlx, start->init_win,
				start->imag, 0, 0)) == 0)
		exit(0);
	return (0);
}
