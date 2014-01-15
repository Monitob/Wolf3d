/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 18:16:44 by jbernabe          #+#    #+#             */
/*   Updated: 2014/01/15 17:42:55 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "fcntl.h"
#include <stdio.h>

int		ft_open(const char *file, int flag)
{
	int	fd;

	if ((fd = open(file, flag)) < 0)
		perror("open: ");
	return (fd);
}
