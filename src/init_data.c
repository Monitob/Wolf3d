/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 16:39:17 by jbernabe          #+#    #+#             */
/*   Updated: 2014/01/17 20:26:20 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_data	*init_data(t_data *data)
{
	data = (t_data *)malloc(sizeof(*data));
	data->map = malloc(sizeof(*(data->map)));
	data->win = malloc(sizeof(*(data->win)));
	data->imag = malloc(sizeof(*(data->imag)));
	data->floor = malloc(sizeof(*(data->floor)));
	data->murs = malloc(sizeof(*(data->murs)));
	data->persp = malloc(sizeof(*(data->persp)));
	data->camera = malloc(sizeof(*(data->camera)));
	if (data == NULL
		|| data->map == NULL
		|| data->win == NULL
		|| data->imag == NULL
		|| data->floor == NULL
		|| data->persp == NULL
		|| data->camera == NULL)
	{
		exit(0);
	}
	data->persp->presition = 0.1;
	data->persp->speed = 10;
	data->persp->angle = 0;
	return (data);
}
