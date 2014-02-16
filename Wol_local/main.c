/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 17:47:16 by jbernabe          #+#    #+#             */
/*   Updated: 2014/01/17 21:27:28 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		main(int ac, char **av)
{
	int		fd;
	t_data	*head;

	head = NULL;
	head = init_data(head);
	if (ac == 2)
	{
		if ((fd = ft_open(av[1], O_RDONLY)) < 0)
			return (0);
		if ((head->map = ft_filling_world(fd, head->map)) == NULL)
			return (0);
		if (ft_close(fd) < 0)
			return (0);
		mlx_expose_hook(head->win->init_win, &expose_hook, head);
		ft_display_screen(head->win);
		player_position(head->map, head->camera, head->persp);
		get_img(head);
		mlx_loop(head->win->init_mlx);
		//	ft_draw_wall(head);

	}
	else
		ft_putendl("usage wolf3d <file>");
	return (0);
}

t_map		*ft_filling_world(int fd, t_map *head)
{
	char	*line;
	int	i;

	head->map = NULL;
	if ((get_next_line(fd, &line)) <= 0)
		return (NULL);
	head->width = ft_tablen(ft_strsplit(line, ' '));
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		i++;
		head->height = i;
		head->map = ft_realloc_world(head, ft_strsplit(line, ' '), i);
		if (head->map == NULL)
			return (NULL);
	}
	return (head);
}

int		**ft_realloc_world(t_map *head, char **line, int size)
{
	int	**res;
	int	i;
	int	j;
	i = 0;
	j = 0;
	if (line == NULL || head->width != ft_tablen(line))
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
}
