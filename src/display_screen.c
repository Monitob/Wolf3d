/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 21:25:31 by jbernabe          #+#    #+#             */
/*   Updated: 2014/05/09 02:03:50 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"

t_wf		*get_dist(t_wf *g)
{
	if (g->ray_dir.x < 0)
	{
		g->step[0] = -1;
		g->dist_m.x = (g->ray_orig.x - g->mapx.x) * g->delta_dist.x;
	}
	else
	{
		g->step[0] = 1;
		g->dist_m.x = (g->mapx.x + 1.0 - g->ray_orig.x) * g->delta_dist.x;
	}
	if (g->ray_dir.y < 0)
	{
		g->step[1] = -1;
		g->dist_m.y = (g->ray_orig.y - g->mapx.y) * g->delta_dist.y;
	}
	else
	{
		g->step[1] = 1;
		g->dist_m.y = (g->mapx.y + 1.0 - g->ray_orig.y) * g->delta_dist.y;
	}
	return (g);
}

t_wf		*init_camera(t_wf *game, int x)
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
	game = ft_move(keycode, game);
	if (keycode == ESC)
		exit (0);
	return (0);
}

int			expose_hook(t_wf *game)
{
	draw_map(game);
	return (0);
}
