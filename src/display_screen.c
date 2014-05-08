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

int			ft_color_tab(t_wf *g)
{
	int		color;

	color = 0;
	if (g->mapx.x < 5 && g->mapx.y < 5)
		color = 0x37FDFC;
	else if (g->mapx.x < 5 && g->mapx.y > 5)
		color = 0x22780F;
	else if (g->mapx.x > 5 && g->mapx.y < 5)
		color = 0xFFFF6B;
	else if (g->mapx.x > 5 && g->mapx.y > 5)
		color = 0xFF7F00;
	else if (g->mapx.x == 5 && g->mapx.y == 0)
		color = 0x00FF00;
	else if (g->mapx.x == 5 && g->mapx.y == 10)
		color = 0xFFFF00;
	else if (g->mapx.x == 10 && g->mapx.y == 5)
		color = 0xFF0000;
	else if (g->mapx.x == 0 && g->mapx.y == 5)
		color = 0x00FF00;
	return (color);
}

t_wf		*get_wall_length(t_wf *g)
{
	if (g->w_side == 0)
	{
		g->wall_length = fabs((g->mapx.x - g->ray_orig.x + (1 - g->step[0]) / 2)
							/ g->ray_dir.x);
	}
	else
	{
		g->wall_length = fabs((g->mapx.y - g->ray_orig.y + (1 - g->step[1]) / 2)
							/ g->ray_dir.y);
	}
	return (g);
}

t_wf	*detect_wall(t_wf *game)
{
	while (game->is_colition == 0)
	{
		if (game->dist_m.x < game->dist_m2.x)
		{
			game->dist_m.x += game->dist_m2.x;
			game->mapx.x += game->step[0];
			game->w_side = 0;
		}
		else
		{
			game->dist_m.y += game->dist_m2.y;
			game->mapx.y += game->step[1];
			game->w_side = 1;
		}
	}
	return (game);
}

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

static t_wf	*init_camera(t_wf *game, int x)
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

void		draw_map(t_wf *game)
{
	int		x;
	int		color;

	x = 0;
	while (x < game->len_m)
	{
		game = init_camera(game, x);
		game = get_dist(game);
		game = detect_wall(game);
		game = get_wall_length(game);
		game->height_m = fabs((int)(game->map_h / game->wall_length));
		game->draw_init = -game->height_m / 2 + game->map_h / 2;
		if (game->draw_init < 0)
		 	game->draw_init = 0;
		game->draw_end = game->height_m / 2 + game->map_h / 2;
		if (game->draw_end >= game->map_h)
			game->draw_end = game->map_h - 1;
		color = ft_color_tab(game);
		if (game->w_side == 1)
			color /= 2;
		//draw_line(x, game, color);
		x++;
	}
	return ;
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
