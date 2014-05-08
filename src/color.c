
#include <math.h>
#include "wolf3d.h"

void		draw_line(int x, t_wf *g, int color)
{
	int		y;

	y = 0;
	while (y < g->draw_init)
	{
		mlx_pixel_put(g->mlx, g->win, x, y, 0x77B5FE);
		y++;
	}
	while (y < g->draw_end)
	{
		mlx_pixel_put(g->mlx, g->win, x, y, color);
		y++;
	}
	while (y < g->map_h)
	{
		mlx_pixel_put(g->mlx, g->win, x, y, 0x808080);
		y++;
	}
}

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
