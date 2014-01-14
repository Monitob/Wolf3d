#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <libft.h>
# include <sys/stat.h>
# include <math.h>
# include <sys/types.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>

# define MAP_WIDTH 20
# define MAP_HEIGHT 20
# define SCR_WIDTH 640
# define SCR_HEIGHT 480

int	**map_wolf(void);

typedef struct	s_world
{
	void	*init_mlx;
	void	*init_win;
}		t_world;

typedef struct	s_camera
{
	double	posi_x;
	double	posi_y;
}		t_camera;

typedef struct	s_vect
{
	double	x;
	double	y;
}		t_vect;

#endif
