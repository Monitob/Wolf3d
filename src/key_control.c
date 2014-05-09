/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/08 23:07:48 by jbernabe          #+#    #+#             */
/*   Updated: 2014/05/09 00:33:10 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include "wolf3d.h"

static t_wf		*key_left(t_wf *game)
{
	game->old_dir = game->dir.x;
	game->dir.x = game->dir.x * cos(game->rotation_sp) - game->dir.y
		* sin(game->rotation_sp);
	game->dir.y = game->old_dir * sin(game->rotation_sp) + game->dir.y
		* cos(game->rotation_sp);
	game->old_plane = game->plane.x;
	game->plane.x = game->plane.x * cos(game->rotation_sp) - game->plane.y
		* sin(game->rotation_sp);
	game->plane.y = game->old_plane * sin(game->rotation_sp) + game->plane.y
		* cos(game->rotation_sp);
	return (game);
}

static t_wf		*key_right(t_wf *game)
{
	game->old_dir = game->dir.x;
	game->dir.x = game->dir.x * cos(-game->rotation_sp) - game->dir.y
		* sin(-game->rotation_sp);
	game->dir.y = game->old_dir * sin(-game->rotation_sp) + game->dir.y
		* cos(-game->rotation_sp);
	game->old_plane = game->plane.x;
	game->plane.x = game->plane.x * cos(-game->rotation_sp) - game->plane.y
		* sin(-game->rotation_sp);
	game->plane.y = game->old_plane * sin(-game->rotation_sp) + game->plane.y
		* cos(-game->rotation_sp);
	return (game);
}

static t_wf		*go_down(t_wf *game)
{
	if (game->map[(int)(game->origin.x - game->dir.x * game->speed)][(int)(game->origin.x)] == 0)
		game->origin.x -= game->dir.x * game->speed;
	if (game->map[(int)(game->origin.x)][(int)(game->origin.y - game->dir.y * game->rotation_sp)] == 0)
		game->origin.y -= game->dir.y * game->speed;
	return (game);
}

static t_wf		*go_up(t_wf *game)
{
	if (game->map[(int)(game->origin.x + game->dir.x * game->speed)][(int)(game->origin.y)] == 0)
		game->origin.x += game->dir.x * game->speed;
	if (game->map[(int)(game->origin.x)][(int)(game->origin.y + game->dir.y * game->rotation_sp)]	== 0)
		game->origin.y += game->dir.y * game->speed;
	return (game);
}	

t_wf	*ft_move(int keycode, t_wf *game)
{
	if (keycode == UP)
	{
		game = go_up(game);
		mlx_clear_window(game->mlx, game->win);
		draw_map(game);
	}
	if (keycode == DOWN)
	{
		game = go_down(game);
		mlx_clear_window(game->mlx, game->win);
		draw_map(game);
	}
	if (keycode == RIGHT)
	{
		game = key_right(game);
		mlx_clear_window(game->mlx, game->win);
		draw_map(game);
	}
	if (keycode == LEFT)
	{
		game = key_left(game);
		mlx_clear_window(game->mlx, game->win);
		draw_map(game);
	}
	return (game);
}
