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
	t_data	wlf;

	if (ac == 2)
	{
		wlf.mlx = mlx_init();
		wlf.win = mlx_new_window(ptr.mlx, 1280, 1100, "Wlf3d");
		if ((wlf.file = ft_strdup(av[1])) == NULL)
		{
			ft_putendl("Wrong file!");
			exit(0);
		}
		mlx_expose_hook(wlf.win, expose_hook, &wlf);
		mlx_key_hook(wlf.win, &key_control, &wlf);
		mlx_loop(wlf.init_mlx);
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
	head->width = ft_tab_len(ft_strsplit(line, ' '));
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		head->height = i;
		head->map = ft_realloc_world(head, ft_strsplit(line, ' '), i);
		if (head->map == NULL)
			return (NULL);
		i++;
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
}
