/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 17:46:53 by jbernabe          #+#    #+#             */
/*   Updated: 2014/05/09 01:30:37 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <libft.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
/*
 * Maccros keys
 */
# define ESC			65307
# define LEFT			65361
# define RIGHT			65363
# define UP				65362
# define DOWN			65364

typedef struct	s_vect
{
	double		x;
	double		y;
}				t_vect;

typedef struct 	s_wf
{
	void		*mlx;
	void		*win;
	int			**map;
	int			len_m;
	int			height_m;
	int			fd;
	int			map_h;
	int			is_colition;
	t_vect		origin;
	t_vect		plane;
	double		old_plane;
	t_vect		dir;
	double		old_dir;
	t_vect		dist_m;
	t_vect		ray_orig;
	t_vect		delta_dist;
	t_vect		ray_dir;
	t_vect		mapx;
	int			w_side;
	int			step[2];
	int			draw_init;
	int			draw_end;
	double		speed;
	double		wall_length;
	double		rotation_sp;
	double		camera;
}				t_wf;

t_wf			*get_map(char *file);
void			draw_map(t_wf *game);
int				expose_hook(t_wf *game);
int				key_hook(int keycode, t_wf *game);
int				ft_open(char *file);
t_wf			*init_camera(t_wf *game, int x);
void			draw_line(int x, t_wf *g, int color);
void			ft_print_debug(int **tab);
t_wf			*get_dist(t_wf *game);
t_wf			*detect_wall(t_wf *game);
t_wf			*get_wall_length(t_wf *g);
int				ft_color_tab(t_wf *g);
t_wf			*ft_move(int keycode, t_wf *game);
// int			ft_display_screen(t_world *start);
// int			player_position(t_map *map, t_camera *camera, t_ray	*persp); 
// void		ft_len_ray(t_ray *persp, t_map *map);
// void		ft_calcul_step(t_ray *persp, t_map *map);
// void		ft_dda(t_ray *persp, t_map *map);
// void		ft_abso_num(float n);
// void		ft_calc_proj_dist(t_map *map_l, t_ray *persp);
// void		ft_abso_int(int n);
// void		ft_caclc_height(t_map *map_l, t_ray *persp);
// int			player_position(t_map *map, t_camera *camera, t_ray	*persp);

#endif
