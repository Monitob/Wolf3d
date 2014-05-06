/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/05 23:59:31 by jbernabe          #+#    #+#             */
/*   Updated: 2014/05/06 04:52:29 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "wolf3d.h"

int				ft_open(char *file)
{
	int		fd;

	if ((fd = open(file, O_RDWR)) == -1)
	{
		perror("Cannot open output file\n");
		exit(0);
	}
	if (fd == O_DIRECTORY)
		exit (-1);
	return (fd);
}