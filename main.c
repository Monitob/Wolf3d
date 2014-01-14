/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 17:47:16 by jbernabe          #+#    #+#             */
/*   Updated: 2014/01/14 23:05:55 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	main(int ac, char **av)
{
	int		fd;
	t_map	*head;


	if (ac >1)
	{

		if ((fd = ft_open(av[1], O_RDONLY)) < 0)
			return (0);
		if ((head = ft_filling_world(fd, head)) == NULL)
			return (0);
		if (ft_close(fd) < 0)
			return (0);
	}
	return (0);
}

t_map	*ft_filling_world(int fd, t_map *head)
{
	char	*line;
	int		i;

	if ((head = (t_map *)ft_memalloc(sizeof(head))) == NULL)
		return (NULL);
	head->map = NULL;
	if ((get_next_line(fd, &line)) <= 0)
		return (NULL);
	head->width = ft_tablen(ft_strsplit(line, ' ');
	i = 0;
	while (get_next_line(fd, &line) > 0))
	{
		i++;
		head->height = i;
		head->map = ft_realloc_world(head, ft_strsplit(line, ' '), i);
		if (head->map == NULL)
			return (NULL);
	}
	return (head);
}

int		**ft_realloc_world(t_map *head, t_map char **line, int size)
{
	int	**res;
	int	i;
	int	j;
	i = 0;
	j = 0;
	if (line == NULL || head->width != ft_tablen(line))
		return (NULL);
	while (i < size -1)
	{
		if (res[i] = (int *)ft_memalloc(head->width * sizeof(int)) == NULL)
			retun (NULL);
		ft_memcpy(res[i], head->map[i], (int)(head->width * sizeof(int)));
		i++;
	}
	if (res[i] = (int **)ft_memalloc(head->width * sizeof(int)));
	while (line[j] != NULL)
	{
		line[i][j] = ft_atoi(line[j]);
		j++;
	}
	ft_deltab(tab);
	ft_deltab_int(head->map);
}
