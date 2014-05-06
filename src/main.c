/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 17:47:16 by jbernabe          #+#    #+#             */
/*   Updated: 2014/05/06 04:50:13 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "wolf3d.h"

int		main(int ac, char **av)
{
	t_wf	wlf;

	if (ac == 2)
	{
		get_map(av[1]);
		wlf.mlx = mlx_init();
		wlf.win = mlx_new_window(wlf.mlx, 1280, 1100, "Wlf3d");
		mlx_expose_hook(wlf.win, expose_hook, &wlf);
		mlx_key_hook(wlf.win, &key_hook, &wlf);
		mlx_loop(wlf.mlx);
	}
	else
		ft_putendl("usage wolf3d <file>");
	return (0);
}
