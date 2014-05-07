/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 21:25:31 by jbernabe          #+#    #+#             */
/*   Updated: 2014/05/07 04:01:53 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <math.h>
#include "wolf3d.h"

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
	//int		color;

	x = 0;
	while (x < game->len_m)
	{
		game = init_camera(game, x);
		// game = ft_get_dist(game);
		// game = ft_detect_wall(game);
		// game = ft_get_wall_length(game);
		// game->h_mur = fabs((int)(game->h / game->wall_length));
		// game->draw_start = -game->h_mur / 2 + game->h / 2;
		// if (game->draw_start < 0)
		// 	game->draw_start = 0;
		// game->draw_end = game->h_mur / 2 + game->h / 2;
		// if (game->draw_end >= game->h)
		// 	game->draw_end = game->h - 1;
		// color = ft_color_card(game);
		// if (game->murvoh == 1)
		// 	color /= 2;
		// draw_line(x, game, color);
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
