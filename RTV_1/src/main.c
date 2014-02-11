/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 17:29:10 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/11 21:44:45 by jbernabe         ###   ########.fr       */
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
	/*iniciar mi universo*/
	init_windows(v);
}

void	init_windows(t_univers *v)
{
	/*inicializar la venta donde vamos a escribir*/
	v->w = 1280;
	v->h = 800;
	v->mlx = mlx_init();
	v->win_ray = mlx_new_window(v->mlx, v->w, v->h, "Rtv");
	v->img = mlx_new_image(v->mlx, v->w, v->h);
	v->data = mlx_get_data_addr(v->img, &(v->bpp), &(v->s_line), &(v->endian));
}

int	main(void)
{
	t_univers	*v;

	v = (t_univers *)malloc(sizeof(t_univers));
	init_univers(v);
	return (0);
}

