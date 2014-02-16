/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 17:46:53 by jbernabe          #+#    #+#             */
/*   Updated: 2014/01/17 21:46:04 by jbernabe         ###   ########.fr       */
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
# define PI			3.14159
# define POS_INIT_X 	22
# define POS_INIT_Y 	12
/*
 * Maccros Win
 */
# define SCR_WIDTH		640
# define SCR_HEIGHT		680
/*
 * Maccros Img
 */
# define IMG_SIZE_X		600
# define IMG_SIZE_Y		600
# define IMG_POS_X		0
# define IMG_POS_Y		0
/*
 * Maccros keys
 */
# define ESC			65307
# define LEFT			65361
# define RIGHT			65363
# define UP				65362
# define DOWN			65364
# define TO_RADIAN(x)	(x) PI / 180

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
	double		camera_x;
	double		plane_x;
	double		plane_y;
	double		direct_x;
	double		direct_y;
}				t_camera;

typedef struct	s_map
{
	int			height;
	int			width;
	int			**map;
	int			map_x;
	int			map_y;
}				t_map;

typedef struct	s_img
{
	void		*ptr_img;
	int			draw_star;
	int			draw_end;
	int			size_line;
	int			endian;
	int			bpp;
	char		*data;
	int			x;
	int			y;
}				t_img;

typedef	struct	s_ray
{
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	float		raypos_x;
	float		raypos_y;
	float		raydir_x;
	float		raydir_y;
	float		presition;
	int			angle;
	int			speed;
	float		side_dist_x;
	float		side_dist_y;
	float		delta_x;
	float		delta_y;
	float		wall_dist;
	int			line_height;
}				t_ray;

typedef struct	s_data
{
	t_map		*map;
	t_world		*win;
	t_img		*imag;
	t_img		*floor;
	t_img		*murs;
	t_ray		*persp;
	t_camera	*camera;
}				t_data;

int			expose_hook(t_data *start);
t_data		*init_data(t_data *data);
t_map		*ft_filling_world(int fd, t_map *head);
int			**ft_realloc_world(t_map *head, char **line, int size);
int			ft_open(const char *file, int flag);
int			key_hook(int keycode, t_world *start);
int			ft_display_screen(t_world *start);
void		get_img(t_data *img);
int			player_position(t_map *map, t_camera *camera, t_ray	*persp); 
void		ft_len_ray(t_ray *persp, t_map *map);
void		ft_calcul_step(t_ray *persp, t_map *map);
void		ft_dda(t_ray *persp, t_map *map);
void		ft_abso_num(float n);
void		ft_calc_proj_dist(t_map *map_l, t_ray *persp);
void		ft_abso_int(int n);
void		ft_caclc_height(t_map *map_l, t_ray *persp);
int			player_position(t_map *map, t_camera *camera, t_ray	*persp);

#endif
