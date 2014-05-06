/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/05 23:53:42 by jbernabe          #+#    #+#             */
/*   Updated: 2014/05/06 05:41:57 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "wolf3d.h"

/*int		**ft_realloc_world(t_map *head, char **line, int size)
{
	int	**res;
	int	i;
	int	j;
	i = 0;
	j = 0;
	if (line == NULL || head->width != ft_tab_len(line))
		return (NULL);
	if ((res = (int **)ft_memalloc(sizeof(res) * (size + 1))) == NULL)
		return (0);
	while (i < size -1)
	{
		if ((res[i] = (int *)ft_memalloc(head->width * sizeof(int)))
				== NULL)
			return (NULL);
		ft_memcpy(res[i], head->map[i], (int)(head->width * sizeof(int)));
		i++;
	}
	if ((res[i] = (int *)ft_memalloc(head->width * sizeof(int))) == NULL)
		return (0);
	while (line[j] != NULL)
	{
		res[i][j] = ft_atoi(line[j]);
		j++;
	}
	free(line);
	free(head->map);
	return (res);
}*/

static int 		**fct_line_tab(char *line, int **tab_int)
{
	int			*line_int;
	int			len;
	int			i;

	len = (int)ft_fast_strlen(line);
	i = 0;
	printf("%sy len -> %zu\n", line, ft_fast_strlen(line));
	while (i < len - 1)
	{
		if (!(line_int = (int *)ft_memalloc(sizeof(int) * len + 1)))
			exit(-1);
		
		i++;
	}
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
	if (!(game->map = (int **)ft_memalloc(sizeof(int) * game->map_h)))
	{
		free(game);
		exit(-1);
	}
	return (game);
}

int		get_map(char *file)
{
	char	*line;
	t_wf	*game;
	
	line = NULL;
	game = NULL;
	game = init_data(game, file);
	while (get_next_line(game->fd, &line))
	{
		fct_line_tab(line, game->map);
		free(line);
	}
	return (0);
}
