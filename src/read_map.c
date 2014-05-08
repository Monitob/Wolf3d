/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/05 23:53:42 by jbernabe          #+#    #+#             */
/*   Updated: 2014/05/08 02:47:35 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "wolf3d.h"

static int 		*str_new_int(int size)
{
	int	*line;

	if (!size)
		return (NULL);
	if (!(line = (int *)ft_memalloc(sizeof(int) * size + 1)))
		return (NULL);
	ft_memset(line, 0, size);
	line[size + 1] = -1;
	return (line);
}

static int 		**fct_line_tab(char *line, int **tab_int, int count)
{
	int			len;
	int			i;

	len = (int)ft_fast_strlen(line);
	i = 0;
	if (!tab_int)
		return (0);
	if (!(tab_int[count] = str_new_int(len)))
		exit(-1);
	while (i < len)
	{
		tab_int[count][i] = line[i] + 0 - 48;
		i++;
	}
	tab_int[count][i] = -1;
	return (tab_int);
}

static t_wf		*init_data(t_wf *game, char *file)
{
	if (!(game = (t_wf *)malloc(sizeof(t_wf))))
		exit(-1);
	if ((game->fd = ft_open(file)) == -1)
		exit(-1);
	game->origin.x = 5;
	game->origin.y = 5;
	game->dir.x = -1;
	game->dir.y = 0;
	game->len_m = 512;
	game->height_m = 384;
	game->map_h = 24;
	game->plane.x = 0;
	game->plane.y = 0.66;
	game->speed = 0.2;
	game->rotation_sp = 0.1;
	if (!(game->map = (int **)ft_memalloc(sizeof(int *) * game->map_h)))
	{
		free(game);
		exit(-1);
	}
	return (game);
}

t_wf			*get_map(char *file)
{
	char		*line;
	t_wf		*game;
	int			count;
	
	line = NULL;
	game = NULL;
	count = 0;
	if (!file)
		exit(-1);
	game = init_data(game, file);
	while (get_next_line(game->fd, &line))
	{
		game->map =	fct_line_tab(line,game->map, count);
		count++;
		free(line);
	}
	return (game);
}
