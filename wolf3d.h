/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 17:46:53 by jbernabe          #+#    #+#             */
/*   Updated: 2014/01/15 22:00:38 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <fcntl.h>
/*
 * Maccros Ray
 */
# define FOV		0.60
# define POS_INIT_X 22
# define POS_INIT_Y 12
/*
 * Maccros Win
 */
# define SCR_WIDTH	640
# define SCR_HEIGHT	680
/*
 * Maccros Img
 */
# define IMG_SIZE_X	600
# define IMG_SIZE_Y	600
# define IMG_POS_X	0
# define IMG_POS_Y	0
/*
 * Maccros keys
 */
# define ESC		65307
# define LEFT		65361
# define RIGHT		65363
# define UP		65362
# define DOWN		65364

typedef struct	s_world
{
	void		*init_mlx;
	char		*mlx_data;
	void		*init_win;
}				t_world;

typedef struct	s_camera
{
	double		posi_x;
	double		posi_y;
}				t_camera;

typedef struct	s_map
{
	int			height;
	int			width;
	int			**map;
}				t_map;

typedef struct	s_img
{
	void		*ptr_img;
	int			size_line;
	int			endian;
	int			bpp;
	char		*data;
	int			x;
	int			y;
}				t_img;

typedef	struct	s_fov
{
	float		x;
	float		y;
	float		presition;
	int			angle;
	int			speed;
}				t_fov;

typedef struct	s_data
{
	t_map		*map;
	t_world		*win;
	t_img		*imag;
	t_img		*floor;
	t_img		*murs;
	t_fov		*persp;
}				t_data;

t_data	*init_data(t_data *data);
t_map		*ft_filling_world(int fd, t_map *head);
int			**ft_realloc_world(t_map *head, char **line, int size);
int			ft_open(const char *file, int flag);
int			key_hook(int keycode, t_world *start);
int			ft_display_screen(t_world *start);

#endif
