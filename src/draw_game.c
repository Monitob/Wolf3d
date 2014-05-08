
#include <math.h>
#include "wolf3d.h"

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
		if ((game->map[(int)game->mapx.x][(int)game->mapx.y]) > 1)
			game->is_colition = 1;
	}
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
		draw_line(x, game, color);
		x++;
	}
	return ;
}
