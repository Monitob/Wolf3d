/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 21:25:31 by jbernabe          #+#    #+#             */
/*   Updated: 2014/05/08 04:01:46 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"

t_wf	*get_dist(t_wf *game)
{
	if (game->ray_dir.x < 0)
	{
		game->step[0] = -1;
		game->dist_m.x = (game->ray_orig.x - game->mapx.x) * game->dist_m2.x;
	}
	else
	{
		game->step[0] = 1;
		game->dist_m.x = (game->mapx.x + 1.0 - game->ray_orig.x) * game->dist_m2.x;
	}
	if (game->ray_dir.y < 0)
	{
		game->step[1] = -1;
		game->dist_m.y = (game->ray_orig.y - game->mapx.y) * game->dist_m2.y;
	}
	else
	{
		game->step[1] = 1;
		game->dist_m.y = (game->mapx.y + 1.0 - game->ray_orig.y) * game->dist_m2.y;
	}
	return (game);
}

t_wf	*init_camera(t_wf *game, int x)
{
	game->camera = 2 * x / (double)(game->len_m) - 1;
	game->ray_orig.x = game->origin.x;
	game->ray_orig.y = game->origin.y;
	game->ray_dir.x = game->dir.x + game->plane.x * game->camera;
	game->ray_dir.y = game->dir.y + game->plane.y * game->camera;
	game->mapx.x = (int)(game->ray_orig.x);
	game->mapx.y = (int)(game->ray_orig.y);
	game->delta_dist.x = sqrt(1 + (game->ray_dir.y *game->ray_dir.y)
							/ (game->ray_dir.x * game->ray_dir.x));
	game->delta_dist.y = sqrt(1 + (game->ray_dir.x * game->ray_dir.x)
							/ (game->ray_dir.y * game->ray_dir.y));
	game->is_colition = 0;
	return (game);
}

int			key_hook(int keycode, t_wf *game)
{
	if (keycode == ESC)
		exit (0);
	(void)game;
	return (0);
}

int			expose_hook(t_wf *game)
{
	draw_map(game);
	return (0);
}
