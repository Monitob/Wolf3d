/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 17:46:53 by jbernabe          #+#    #+#             */
/*   Updated: 2014/01/14 23:09:37 by jbernabe         ###   ########.fr       */
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

# define SCR_WIDTH 640
# define SCR_HEIGHT 480

typedef struct	s_world
{
	void		*init_mlx;
	char		*data;
	void		*init_win;
}				t_world;

typedef struct	s_camera
{
	double		posi_x;
	double		posi_y;
}				t_camera;

typedef struct	s_vect
{
	double		x;
	double		y;
}				t_vect;

typedef struct	s_map
{
	int			height;
	int			width;
	int			**map;
}				t_map;

t_map		*ft_filling_world(int fd, t_map *head);
int			**ft_realloc_world(t_map *head, char **line, int size);
int			ft_open(const char *file, int flag);
int			key_hook(int keycode, t_world *start);
int			ft_display_screen(t_map *head);

#endif
