/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deltab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@tabtudent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 20:29:36 by jbernabe          #+#    #+#             */
/*   Updated: 2014/01/14 20:39:56 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_deltab(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab != NULL)
		{
			free(tab[i]);
			i++;
		}
		free (tab[i]);
		free (tab);
	}
}
