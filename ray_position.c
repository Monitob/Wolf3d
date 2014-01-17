/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 18:32:27 by jbernabe          #+#    #+#             */
/*   Updated: 2014/01/17 21:46:03 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		player_position(t_map *map, t_camera *camera, t_ray	*persp) 
{
	int	i;

	camera->posi_x = 1.5;
	camera->posi_y = 1.5;
	camera->direct_x = -1;
	camera->direct_y = 0;
	camera->plane_x = 0;
	camera->plane_y = 0.66;
	i = 0;
	while (i < map->width)
	{
		camera->camera_x = 2 * i / map->width - 1;
		persp->raypos_x = camera->posi_x;
		persp->raypos_y = camera->posi_y;
		persp->raydir_x = camera->direct_x + camera->plane_x * camera->camera_x;
		persp->raydir_y = camera->direct_y + camera->plane_y * camera->camera_x;
		map->map_x = (int)persp->raypos_x;
		map->map_y = (int)persp->raypos_y;
		ft_len_ray(persp, map);
		i++;
	}
	return (0);
}

void	ft_len_ray(t_ray *persp, t_map *map)
{
	persp->delta_x = sqrt(1 + (persp->raydir_y * persp->raydir_y) /
							(persp->raydir_x * persp->raydir_x));
	persp->delta_y = sqrt(1 + (persp->raydir_y * persp->raydir_y) /
							(persp->raydir_x * persp->raydir_x));
	ft_calcul_step(persp, map);
}

void	ft_calcul_step(t_ray *persp, t_map *map)
{
	persp->hit = 0;
	if (persp->raydir_x < 0)
	{
		persp->step_x = -1;
		persp->side_dist_x = (persp->raypos_x - map->map_x) * persp->delta_x;
	}
	else
	{
		persp->step_x = 1;
		persp->side_dist_x = (map->map_x + 1.0 - persp->raypos_x) *
								persp->delta_x;
	}
	if (persp->raydir_y < 0)
	{
		persp->step_y = -1;
		persp->side_dist_y = (persp->raypos_y - map->map_y) * persp->delta_y;
	}
	else
	{
		persp->step_x = 1;
		persp->side_dist_y = (map->map_y + 1.0 - persp->raypos_y) *
								persp->delta_y;
	}
	ft_dda(persp, map);
}

void	ft_dda(t_ray *persp, t_map *map)
{
	while (persp->hit == 0)
	{
		if (persp->side_dist_x < persp->side_dist_y)
		{
			persp->side_dist_x  += persp->delta_x;
			map->map_x += persp->step_x;
			persp->side = 0;
		}
		else
		{
			persp->side_dist_y  += persp->delta_y;
			map->map_y += persp->step_y;
			persp->side = 1;
		}
		if ((map->map[map->map_x][map->map_y]) > 0)
			persp->hit = 1;
	}
	ft_calc_proj_dist(map, persp);
}

void	ft_abso_num(float n)
{
	if (n < 0)
		n = -n;
	else
		return ;
}

void	ft_calc_proj_dist(t_map *map_l, t_ray *persp)
{
	if (persp->side == 0)
	{
		persp->wall_dist = (map_l->map_x - persp->raypos_x +
										(1 - persp->step_x) / 2) /
										persp->raydir_x;
		ft_abso_num(persp->wall_dist);
	}
	else
	{
		persp->wall_dist = (map_l->map_y - persp->raypos_y +
										(1 - persp->step_y) / 2) /
										persp->raydir_y;
		ft_abso_num(persp->wall_dist);
	}
	ft_caclc_height(map_l, persp);
}

void	ft_abso_int(int n)
{
	if (n < 0)
		n = -n;
	else
		return ;
}

void	ft_caclc_height(t_map *map_l, t_ray *persp)
{
	t_data	*mur_data;

	persp->line_height = (map_l->height / persp->wall_dist);
	ft_abso_int((int)persp->line_height);
	mur_data->murs->draw_star = -persp->line_height / 2 + (map_l->height / 2);
	if (mur_data->murs->draw_star < 0)
		mur_data->murs->draw_star = 0;
	mur_data->murs->draw_end = persp->line_height / 2 + (map_l->height / 2);
	if (mur_data->murs->draw_end > map_l->height)
		mur_data->murs->draw_end = map_l->height - 1;
}
