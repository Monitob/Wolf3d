/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/08 16:59:29 by jbernabe          #+#    #+#             */
/*   Updated: 2014/01/14 23:13:22 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_strchr_free(char **line, char *l_buz, int ret)
{
	char		*tmp;

	tmp = *line;
	l_buz[ret] = '\0';
	*line = ft_strjoin(*line, l_buz);
	free(tmp);
}

static void		ft_strsub_free(char **line, char **p_after)
{
	char		*tmp;

	tmp = *line;
	*line = ft_strsub(*line, 0, *p_after - *line);
	*p_after = *p_after + 1;
	*p_after = ft_strdup(*p_after);
	free(tmp);
}

int				get_next_line(int const fd, char **line)
{
	static char	*p_after;
	char		*l_buz;
	int			ret;

	if ((l_buz = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)) == NULL)
		return (-1);
	if (fd < 0)
		return (-1);
	else
	{
		*line = ft_strnew(1);
		if (p_after != NULL)
		{
			*line = ft_strdup(p_after);
			free(p_after);
		}
		while (!(p_after = ft_strchr(*line, '\n'))
				&& (ret = read(fd, l_buz, BUFF_SIZE)) > 0)
		{	
			ft_strchr_free(line, l_buz, ret);
		}
		if (ret == 0 && p_after == NULL)
			return (0);
		 ret = (ret == -1) ? -1: 1;
		ft_strsub_free(line, &p_after);
		free(l_buz);
		return (1);
	}
}
